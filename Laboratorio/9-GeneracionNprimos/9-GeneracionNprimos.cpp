/*
-----------------------------------------------------------------------------------------
TAREA: Generacion de N primos  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    texto

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 20/Jun/2025

*/

#include <iostream>

using namespace std;

int main() {

    int n, c = 0, i = 2;

    cout << "Cuantos primos: ";
    cin >> n;

    while (c < n) {

        bool p = 1;

        for (int j = 2; j * j <= i && p; j++) {
            p = i % j;
        }

        if (p) {

            cout << i << " ", c++;
        }

        i++;
    }
}