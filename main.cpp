#include <iostream>
#include <fstream>
#include <string>
#include "./Codigos/huffman.h"
#include "./Codigos/palindromo.h"
#include "./Codigos/subsecuencias.h"
#include "./Codigos/substring.h"
#include <iomanip>
#include <set>
#include <map>

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

    // Leer transmisiones
    string transmission1_content = leerArchivo("Archivos Entrada/transmission1.txt");
    string transmission2_content = leerArchivo("Archivos Entrada/transmission2.txt");

    // Leer códigos
    string mcode1_content = leerArchivo("Archivos Entrada/mcode1.txt");
    string mcode2_content = leerArchivo("Archivos Entrada/mcode2.txt");
    string mcode3_content = leerArchivo("Archivos Entrada/mcode3.txt");

    // Procesar transmisión 1
    HuffmanDetector detector1;
    detector1.processTransmission(transmission1_content);

    // Verificar códigos con transmisión 1
    cout << "Verificando códigos con árbol de transmisión 1:" << endl;
    cout << "mcode1.txt: " << detector1.checkSuspicious(mcode1_content) << endl;
    cout << "mcode2.txt: " << detector1.checkSuspicious(mcode2_content) << endl;
    cout << "mcode3.txt: " << detector1.checkSuspicious(mcode3_content) << endl << endl;

    // Procesar transmisión 2
    HuffmanDetector detector2;
    detector2.processTransmission(transmission2_content);

    // Verificar códigos con transmisión 2
    cout << "Verificando códigos con árbol de transmisión 2:" << endl;
    cout << "mcode1.txt: " << detector2.checkSuspicious(mcode1_content) << endl;
    cout << "mcode2.txt: " << detector2.checkSuspicious(mcode2_content) << endl;
    cout << "mcode3.txt: " << detector2.checkSuspicious(mcode3_content) << endl;

    return 0;
}

