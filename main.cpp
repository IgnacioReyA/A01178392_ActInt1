#include <iostream>
#include <fstream>
#include <string>
#include "./Codigos/huffman.h"
#include "./Codigos/palindromo.h"
#include "./Codigos/subsecuencias.h"
#include "./Codigos/substring.h"

using namespace std;

string leerArchivo(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string contenido;
    string linea;

    if (archivo.is_open())
    {
        while (getline(archivo, linea))
        {
            contenido += linea;
        }
        archivo.close();
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
    }

    return contenido;
}

int main()
{
    cout << "=== Parte 1 - Búsqueda de subsecuencias ===" << endl;

    // Leer archivos de transmisión
    string transmission1 = leerArchivo("Archivos Entrada/transmission1.txt");
    string transmission2 = leerArchivo("Archivos Entrada/transmission2.txt");

    // Leer archivos de códigos maliciosos
    string mcode1 = leerArchivo("Archivos Entrada/mcode1.txt");
    string mcode2 = leerArchivo("Archivos Entrada/mcode2.txt");
    string mcode3 = leerArchivo("Archivos Entrada/mcode3.txt");

    // Buscar subsecuencias en transmission1
    cout << "\nTransmission1.txt:" << endl;
    cout << "mcode1: " << subsecuencias(transmission1, mcode1) << endl;
    cout << "mcode2: " << subsecuencias(transmission1, mcode2) << endl;
    cout << "mcode3: " << subsecuencias(transmission1, mcode3) << endl;

    // Buscar subsecuencias en transmission2
    cout << "\nTransmission2.txt:" << endl;
    cout << "mcode1: " << subsecuencias(transmission2, mcode1) << endl;
    cout << "mcode2: " << subsecuencias(transmission2, mcode2) << endl;
    cout << "mcode3: " << subsecuencias(transmission2, mcode3) << endl;

    // auto res = longest_palindrome_positions(transmission1);
    auto res = longest_palindrome_positions_ignore_whitespace(transmission1);
    cout << "\n ==== Parte 2 ====" << endl;
    cout << "\nTransmission1.txt:" << endl;
    cout << res.first << " " << res.second << "\n";
    cout << "\nTransmission2.txt:" << endl;
    res = longest_palindrome_positions_ignore_whitespace(transmission2);
    cout << res.first << " " << res.second << "\n";

    return 0;
}