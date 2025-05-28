/*
-----------------------------------------------------------------------------------------
TAREA: Coca Cola (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    Salvador tenía inicialmente 100 floreros. Vendió 8 floreros y quiere distribuir los floreros restantes cumpliendo las siguientes condiciones:

    Los floreros deben poder agruparse de 6 en 6 sin que sobre ninguno
    Los floreros finales restantes deben poder agruparse de 11 en 11 sin que sobre ninguno
    Encuentra todas las posibles cantidades de floreros que Salvador puede tener al final, considerando que puede regalar o perder algunos floreros adicionales.

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