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
    cout << "Hello, World!" << endl;
    return 0;
}
