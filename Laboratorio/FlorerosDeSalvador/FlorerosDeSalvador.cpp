/*
-----------------------------------------------------------------------------------------
TAREA: Coca Cola (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    Los Floreros de Salvador, tenia 100 floreros, vendio 8,

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 23/May/2025

*/

#include <iostream>

using namespace std;

int main() {

    int totalInicial = 100, vendidos = 8;

    cout << "Posibles soluciones de floreros restantes:" << endl;

    for (int x = 0; x <= totalInicial; x++) {

        if ((100 - x) % 6 == 0 && (100 - x - vendidos) % 11 == 0) {

            int floreros_restantes = totalInicial - x - vendidos;

            if (floreros_restantes > 0 && floreros_restantes % 11 == 0)
                
                cout << floreros_restantes << endl;
        }
    }

    return 0;
}