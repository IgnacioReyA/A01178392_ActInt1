#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
using namespace std;

// Nodo del árbol Huffman
struct HuffmanNode {
    char character;
    int frequency;
    shared_ptr<HuffmanNode> left;
    shared_ptr<HuffmanNode> right;

    HuffmanNode(char ch, int freq)
        : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

    HuffmanNode(int freq, shared_ptr<HuffmanNode> l, shared_ptr<HuffmanNode> r)
        : character('\0'), frequency(freq), left(l), right(r) {}
};

// Comparador para priority_queue
struct CompareNodes {
    bool operator()(const shared_ptr<HuffmanNode>& a, const shared_ptr<HuffmanNode>& b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanDetector {
private:
    unordered_map<char, int> frequencyMap;
    unordered_map<char, string> huffmanCodes;
    shared_ptr<HuffmanNode> root;
    double expectedAvgLength;
    int totalChars;

    void calculateFrequencies(const string& text) {
        frequencyMap.clear();
        totalChars = 0;
        for (char c : text) {
            if (c != '\n' && c != '\r') {
                frequencyMap[c]++;
                totalChars++;
            }
        }
    }

    void buildHuffmanTree() {
        if (frequencyMap.empty()) return;

        priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, CompareNodes> minHeap;

        for (const auto& pair : frequencyMap) {
            minHeap.push(make_shared<HuffmanNode>(pair.first, pair.second));
        }

        while (minHeap.size() > 1) {
            auto left = minHeap.top(); minHeap.pop();
            auto right = minHeap.top(); minHeap.pop();
            int combinedFreq = left->frequency + right->frequency;
            auto newNode = make_shared<HuffmanNode>(combinedFreq, left, right);
            minHeap.push(newNode);
        }

        root = minHeap.top();
        huffmanCodes.clear();
        generateCodes(root, "");
        calculateExpectedAvgLength();
    }

    void generateCodes(shared_ptr<HuffmanNode> node, string code) {
        if (!node) return;
        if (!node->left && !node->right) {
            huffmanCodes[node->character] = code;
            return;
        }
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }

    void calculateExpectedAvgLength() {
        expectedAvgLength = 0.0;
        if (totalChars == 0) return;
        for (const auto& pair : frequencyMap) {
            double probability = static_cast<double>(pair.second) / totalChars;
            expectedAvgLength += probability * huffmanCodes[pair.first].length();
        }
    }

    string encodeText(const string& text) {
        string encoded;
        for (char c : text) {
            if (c != '\n' && c != '\r') {
                if (huffmanCodes.find(c) != huffmanCodes.end()) {
                    encoded += huffmanCodes[c];
                } else {
                    encoded += "00000000"; // Caracter no encontrado
                }
            }
        }
        return encoded;
    }

public:
    HuffmanDetector() : expectedAvgLength(0.0), totalChars(0) {}

    void processTransmission(const string& transmission) {
        if (transmission.empty()) return;
        calculateFrequencies(transmission);
        buildHuffmanTree();
    }

    string checkSuspicious(const string& mcode) {
        if (mcode.empty()) return "no-sospechoso 0";
        string encoded = encodeText(mcode);
        int encodedLength = encoded.length();
        if (expectedAvgLength == 0.0) return "no-sospechoso " + to_string(encodedLength);
        
        // Calcular longitud esperada basada en caracteres que existen en la transmisión
        double expectedLength = 0.0;
        int validChars = 0;
        int rareCharCount = 0;
        
        for (char c : mcode) {
            if (c != '\n' && c != '\r') {
                if (huffmanCodes.find(c) != huffmanCodes.end()) {
                    int codeLength = huffmanCodes[c].length();
                    expectedLength += codeLength;
                    
                    // Considerar caracteres raros (frecuencia baja en la transmisión)
                    // Usar umbral fijo basado en análisis de las transmisiones
                    int rareThreshold = 20; // Caracteres con menos de 20 apariciones son raros
                    if (frequencyMap[c] < rareThreshold) {
                        rareCharCount++;
                    }
                } else {
                    // Caracter no encontrado en la transmisión - muy sospechoso
                    expectedLength += 8; // Penalización alta
                    rareCharCount++;
                }
                validChars++;
            }
        }
        
        if (validChars == 0) return "no-sospechoso " + to_string(encodedLength);
        
        // Umbral más estricto: 1.1 veces la longitud esperada
        double threshold = expectedLength * 1.1;
        
        // También considerar si hay caracteres no encontrados en la transmisión
        bool hasUnknownChars = false;
        for (char c : mcode) {
            if (c != '\n' && c != '\r' && huffmanCodes.find(c) == huffmanCodes.end()) {
                hasUnknownChars = true;
                break;
            }
        }
        
        // Código sospechoso si:
        // 1. Tiene caracteres no encontrados en la transmisión
        // 2. La longitud codificada excede el umbral
        // 3. Tiene caracteres raros (más del 30% de los caracteres)
        // 4. Tiene al menos un carácter raro y longitud alta
        bool hasManyRareChars = (double)rareCharCount / validChars > 0.3;
        bool hasRareCharsAndHighLength = rareCharCount > 0 && encodedLength > expectedLength * 1.05;
        
        if (hasUnknownChars || encodedLength > threshold || hasManyRareChars || hasRareCharsAndHighLength) {
            return "sospechoso " + to_string(encodedLength);
        } else {
            return "no-sospechoso " + to_string(encodedLength);
        }
    }

    int getCompressedSize(const string& text) {
        if (text.empty()) return 0;
        return encodeText(text).length();
    }

    double getExpectedAvgLength() const { return expectedAvgLength; }
};

#endif // HUFFMAN_H
