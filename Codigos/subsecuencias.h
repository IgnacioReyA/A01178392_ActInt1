#ifndef SUBSECUENCIAS_H
#define SUBSECUENCIAS_H

#include <string>
using namespace std;

string subsecuencias(string transmission, string mcode)
{
    int sizeT = transmission.size();
    int sizeM = mcode.size();
    
    int j = 0; //indice para mcode
    int startPos = -1; // Posición donde inicia la subsecuencia
    
    for (int i = 0; i < sizeT && j < sizeM; i++) {
        if (transmission[i] == mcode[j]) {
            if (j == 0) {
                startPos = i + 1; // Guardar posición del primer carácter (base 1)
            }
            j++;
        }
    }
    
    // Si encontramos todos los caracteres de mcode en orden
    if (j == sizeM) {
        return "true " + to_string(startPos);
    }
    
    return "false";
}

#endif

