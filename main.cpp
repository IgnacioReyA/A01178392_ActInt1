#include <iostream>
#include <fstream>
#include <string>
#include "./Codigos/huffman.h"
#include "./Codigos/palindromo.h"
#include "./Codigos/subsecuencias.h"
#include "./Codigos/substring.h"

using namespace std;

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string contenido;
    string linea;
    
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            contenido += linea;
        }
        archivo.close();
    } else {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
    }
    
    return contenido;
}

int main() {
    
    string transmission1 = leerArchivo("transmission1.txt");
    string transmission2 = leerArchivo("transmission2.txt");
    
    // Leer códigos mcode
    string mcode1 = leerArchivo("mcode1.text");
    string mcode2 = leerArchivo("mcode2.text");
    string mcode3 = leerArchivo("mcode3.txt");
    
    // Verificar que se leyeron los archivos correctamente
    if (transmission1.empty() || transmission2.empty()) {
        cout << "Error: No se pudieron leer las transmisiones. Verifica que los archivos existan." << endl;
        return 1;  // Corregido: retornar 1 en caso de error
    }
    
    cout << "=== DETECCIÓN DE CÓDIGOS SOSPECHOSOS ===" << endl << endl;
    
    // Procesar transmisión 1
    cout << "=== TRANSMISIÓN 1 ===" << endl;
    HuffmanDetector detector1;
    detector1.processTransmission(transmission1);
    cout << "Longitud promedio esperada: " << detector1.getExpectedAvgLength() << endl;
    cout << "Tamaño comprimido transmission1: " << detector1.getCompressedSize(transmission1) << " bits" << endl;
    cout << endl;
    
    // Verificar códigos con transmisión 1
    cout << "mcode1 con transmission1: " << detector1.checkSuspicious(mcode1) << endl;
    cout << "mcode2 con transmission1: " << detector1.checkSuspicious(mcode2) << endl;
    cout << "mcode3 con transmission1: " << detector1.checkSuspicious(mcode3) << endl;
    cout << endl;
    
    // Procesar transmisión 2
    cout << "=== TRANSMISIÓN 2 ===" << endl;
    HuffmanDetector detector2;
    detector2.processTransmission(transmission2);
    cout << "Longitud promedio esperada: " << detector2.getExpectedAvgLength() << endl;
    cout << "Tamaño comprimido transmission2: " << detector2.getCompressedSize(transmission2) << " bits" << endl;
    cout << endl;
    
    // Verificar códigos con transmisión 2
    cout << "mcode1 con transmission2: " << detector2.checkSuspicious(mcode1) << endl;
    cout << "mcode2 con transmission2: " << detector2.checkSuspicious(mcode2) << endl;
    cout << "mcode3 con transmission2: " << detector2.checkSuspicious(mcode3) << endl;
    
    return 0;
}
