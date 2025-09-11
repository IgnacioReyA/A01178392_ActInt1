/*
 * Detector de codigos sospechosos usando Huffman
 * Milan Guzman - A01199013
 * 2025-09-10
 */

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
using namespace std;

struct HuffmanNode {
    char character;  // El caracter (solo en hojas)
    int frequency;   // Cuantas veces aparece
    shared_ptr<HuffmanNode> left;   // Rama izquierda (0)
    shared_ptr<HuffmanNode> right;  // Rama derecha (1)

    HuffmanNode(char ch, int freq) {
        character = ch;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }

    HuffmanNode(int freq, shared_ptr<HuffmanNode> l, shared_ptr<HuffmanNode> r) {
        character = '\0';
        frequency = freq;
        left = l;
        right = r;
    }
};

struct CompareNodes {
    // Comparador para que la priority_queue sea un min-heap
    bool operator()(const shared_ptr<HuffmanNode>& a, const shared_ptr<HuffmanNode>& b) {
        return a->frequency > b->frequency;
    }
};


class HuffmanDetector {
private:
    // Constantes para detectar codigos sospechosos
    static const int RARE_THRESHOLD = 20;  // Menos de 20 = caracter raro
    static constexpr double LENGTH_THRESHOLD = 1.1;  // 110% de la longitud esperada
    static const int PENALTY_BITS = 8;  // Penalizacion para caracteres desconocidos
    static constexpr double RARE_CHAR_PERCENTAGE = 0.3;  // 30% de caracteres raros
    static constexpr double RARE_CHAR_LENGTH_THRESHOLD = 1.05;  // 105% con caracteres raros

    unordered_map<char, int> frequencyMap;  // Cuenta apariciones de cada caracter
    unordered_map<char, string> huffmanCodes;  // Codigo binario de cada caracter
    shared_ptr<HuffmanNode> root;  // Raiz del arbol de Huffman
    double expectedAvgLength;  // Longitud promedio esperada
    int totalChars;  // Total de caracteres procesados

    // Cuenta cuantas veces aparece cada caracter
    void calculateFrequencies(const string& text) {
        frequencyMap.clear();
        totalChars = 0;
        
        for (char c : text) {
            if (c != '\n' && c != '\r') {  // Ignorar saltos de linea
                frequencyMap[c]++;
                totalChars++;
            }
        }
    }

    // Construye el arbol de Huffman
    void buildHuffmanTree() {
        if (frequencyMap.empty()) {
            return;
        }

        priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, CompareNodes> minHeap;

        // Crear nodos hoja para cada caracter
        for (const auto& pair : frequencyMap) {
            minHeap.push(make_shared<HuffmanNode>(pair.first, pair.second));
        }

        // Algoritmo de Huffman: combinar nodos hasta tener solo uno
        while (minHeap.size() > 1) {
            auto left = minHeap.top();  // Menor frecuencia
            minHeap.pop();
            auto right = minHeap.top();  // Segunda menor frecuencia
            minHeap.pop();
            
            int combinedFreq = left->frequency + right->frequency;
            auto newNode = make_shared<HuffmanNode>(combinedFreq, left, right);
            minHeap.push(newNode);
        }

        root = minHeap.top();  // El ultimo nodo es la raiz
        huffmanCodes.clear();
        generateCodes(root, "");  // Generar codigos binarios
        calculateExpectedAvgLength();
    }


    // Genera los codigos binarios para cada caracter
    void generateCodes(shared_ptr<HuffmanNode> node, string code) {
        if (!node) {
            return;
        }
        
        if (!node->left && !node->right) {  // Es una hoja
            huffmanCodes[node->character] = code;  // Guardar codigo del caracter
            return;
        }
        
        generateCodes(node->left, code + "0");   // Izquierda = 0
        generateCodes(node->right, code + "1");  // Derecha = 1
    }

    // Calcula la longitud promedio de los codigos
    void calculateExpectedAvgLength() {
        expectedAvgLength = 0.0;
        if (totalChars == 0) {
            return;
        }
        
        for (const auto& pair : frequencyMap) {
            double probability = static_cast<double>(pair.second) / totalChars;  // Probabilidad del caracter
            expectedAvgLength += probability * huffmanCodes[pair.first].length();  // Peso * longitud
        }
    }

    // Convierte texto a codigo binario
    string encodeText(const string& text) {
        string encoded;
        
        for (char c : text) {
            if (c != '\n' && c != '\r') {
                if (huffmanCodes.find(c) != huffmanCodes.end()) {
                    encoded += huffmanCodes[c];  // Usar codigo Huffman
                } else {
                    // Caracter desconocido = penalizacion alta
                    string penalty = "";
                    for (int i = 0; i < PENALTY_BITS; i++) {
                        penalty += "0";
                    }
                    encoded += penalty;
                }
            }
        }
        return encoded;
    }

public:
    // Constructor
    HuffmanDetector() {
        expectedAvgLength = 0.0;
        totalChars = 0;
    }

    // Procesa la transmision y crea el arbol
    void processTransmission(const string& transmission) {
        if (transmission.empty()) {
            return;
        }
        calculateFrequencies(transmission);
        buildHuffmanTree();
    }

    // Checa si un codigo es sospechoso
    string checkSuspicious(const string& mcode) {
        if (mcode.empty()) {
            return "no-sospechoso 0";
        }
        
        string encoded = encodeText(mcode);
        int encodedLength = encoded.length();
        
        if (expectedAvgLength == 0.0) {
            return "no-sospechoso " + to_string(encodedLength);
        }
        
        // Calcular longitud esperada para este codigo
        double expectedLength = 0.0;
        int validChars = 0;
        int rareCharCount = 0;
        
        for (char c : mcode) {
            if (c != '\n' && c != '\r') {
                if (huffmanCodes.find(c) != huffmanCodes.end()) {
                    int codeLength = huffmanCodes[c].length();
                    expectedLength += codeLength;
                    
                    if (frequencyMap[c] < RARE_THRESHOLD) {  // Caracter raro
                        rareCharCount++;
                    }
                } else {
                    expectedLength += PENALTY_BITS;  // Caracter desconocido
                    rareCharCount++;
                }
                validChars++;
            }
        }
        
        if (validChars == 0) {
            return "no-sospechoso " + to_string(encodedLength);
        }
        
        double threshold = expectedLength * LENGTH_THRESHOLD;  // 110% de lo esperado
        
        // Verificar caracteres desconocidos
        bool hasUnknownChars = false;
        for (char c : mcode) {
            if (c != '\n' && c != '\r' && huffmanCodes.find(c) == huffmanCodes.end()) {
                hasUnknownChars = true;
                break;
            }
        }
        
        // Criterios para marcar como sospechoso
        bool hasManyRareChars = (double)rareCharCount / validChars > RARE_CHAR_PERCENTAGE;  // >30% raros
        bool hasRareCharsAndHighLength = rareCharCount > 0 && encodedLength > expectedLength * RARE_CHAR_LENGTH_THRESHOLD;
        
        if (hasUnknownChars || encodedLength > threshold || hasManyRareChars || hasRareCharsAndHighLength) {
            return "sospechoso " + to_string(encodedLength);
        } else {
            return "no-sospechoso " + to_string(encodedLength);
        }
    }

    // Obtiene el tamano del texto comprimido
    int getCompressedSize(const string& text) {
        if (text.empty()) {
            return 0;
        }
        return encodeText(text).length();
    }

    // Obtiene la longitud promedio esperada
    double getExpectedAvgLength() const {
        return expectedAvgLength;
    }
};

#endif // HUFFMAN_H
