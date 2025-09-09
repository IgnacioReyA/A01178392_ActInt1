#ifndef SUBSECUENCIAS_H
#define SUBSECUENCIAS_H

#include <string>
using namespace std;

string subsecuencias(string transmission, string mcode)
{
    int sizeT = transmission.size();
    int sizeM = mcode.size();
    
    // Si mcode está vacío, se considera encontrado en posición 1
    if (sizeM == 0) {
        return "true 1";
    }
    
    // Buscar la subcadena (substring) contigua
    for (int i = 0; i <= sizeT - sizeM; i++) {
        int j = 0;
        // Verificar si la subcadena coincide desde la posición i
        while (j < sizeM && transmission[i + j] == mcode[j]) {
            j++;
        }
        // Si j llegó al final de mcode, se encontró la subcadena completa
        if (j == sizeM) {
            return "true " + to_string(i + 1); // +1 para posición basada en 1
        }
    }
    
    return "false";
}

#endif

