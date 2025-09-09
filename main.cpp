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
    // Crear archivos de transmisión
    ofstream transmission1("Archivo Entrada/transmission1.txt");
    transmission1 << "AAAAAAAAAAAABBBBBBBBBBBBCCCCCCCCCCCCDDDDDDDDDDDD AAAABBBBCCCCDDDDEEEEFFFFEEEEDDDDCCCCBBBBAAAA AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEEEEFFFFFFFF 111122223333444455556666777788889999AAAABBBBCCCC 1234DEADBEEF5678CAFEBABE9876 AAAABBBBCCCCDDDDEEEEFFFFEEEEDDDDCCCCBBBBAAAA";
    transmission1.close();

    ofstream transmission2("Archivo Entrada/transmission2.txt");
    transmission2 << "BBBBBBBBBBBBCCCCCCCCCCCCDDDDAAAAEEEFFFFFFFEEEEAAAADDDDCCCCBBBB AAAA11112222333344445555666655554444333322221111AAAA 999988887777666655554444333322221111AAAABBBBCCCC 1234DEADBEEF5678CAFEBABE9876 FFFFFFFFEEEEDDDDCCCCBBBBAAAA1111222233334444";
    transmission2.close();

    // Crear archivos de códigos
    ofstream mcode1("Archivo Entrada/mcode1.txt");
    mcode1 << "DEADBEEF";
    mcode1.close();

    ofstream mcode2("Archivo Entrada/mcode2.txt");
    mcode2 << "CAFEBABE";
    mcode2.close();

    ofstream mcode3("Archivo Entrada/mcode3.txt");
    mcode3 << "ABCDEFABCDEF";
    mcode3.close();

    // Leer transmisiones
    string transmission1_content = leerArchivo("Archivos Entrada/transmission1.txt");
    string transmission2_content = leerArchivo("Archivos Entrada/transmission2.txt");

    // Leer códigos
    string mcode1_content = leerArchivo("Archivos Entrada/mcode1.txt");
    string mcode2_content = leerArchivo("Archivos Entrada/mcode2.txt");
    string mcode3_content = leerArchivo("Archivos Entrada/mcode3.txt");

    // Procesar transmisión 1
    cout << "=== TRANSMISIÓN 1 ===" << endl;
    HuffmanDetector detector1;
    detector1.processTransmission(transmission1_content);
    
    cout << "Longitud promedio esperada: " << fixed << setprecision(2) 
         << detector1.getExpectedAvgLength() << " bits por carácter" << endl;
    cout << "Tamaño comprimido real: " << detector1.getCompressedSize(transmission1_content) 
         << " bits" << endl << endl;

    // Verificar códigos con transmisión 1
    cout << "Verificando códigos con árbol de transmisión 1:" << endl;
    cout << "mcode1.txt: " << detector1.checkSuspicious(mcode1_content) << endl;
    cout << "mcode2.txt: " << detector1.checkSuspicious(mcode2_content) << endl;
    cout << "mcode3.txt: " << detector1.checkSuspicious(mcode3_content) << endl << endl;

    // Procesar transmisión 2
    cout << "=== TRANSMISIÓN 2 ===" << endl;
    HuffmanDetector detector2;
    detector2.processTransmission(transmission2_content);
    
    cout << "Longitud promedio esperada: " << fixed << setprecision(2) 
         << detector2.getExpectedAvgLength() << " bits por carácter" << endl;
    cout << "Tamaño comprimido real: " << detector2.getCompressedSize(transmission2_content) 
         << " bits" << endl << endl;

    // Verificar códigos con transmisión 2
    cout << "Verificando códigos con árbol de transmisión 2:" << endl;
    cout << "mcode1.txt: " << detector2.checkSuspicious(mcode1_content) << endl;
    cout << "mcode2.txt: " << detector2.checkSuspicious(mcode2_content) << endl;
    cout << "mcode3.txt: " << detector2.checkSuspicious(mcode3_content) << endl;

    return 0;
}

