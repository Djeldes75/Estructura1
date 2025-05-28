/*
    -------------------------------------------------------------------------------------
TAREA: Coca Cola (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    aaa

INTEGRANTES:
    Dominique Jeldes - 1121623

Fecha: 23/May/2025

*/

#include <iostream>

using namespace std;

int main() {

    for (int i = 1; i <= 100; i++) {  // Iterar del 1 al 100

        if (i % 3 == 0 && i % 5 == 0) {  // Múltiplo de 3 y 5
            cout << "Coca Cola" << endl;
        }
        else if (i % 3 == 0) {         // Múltiplo de 3
            cout << "Coca" << endl;
        }
        else if (i % 5 == 0) {         // Múltiplo de 5
            cout << "Cola" << endl;
        }
        else {                         // No múltiplo de 3 ni de 5
            cout << i << endl;
        }
    }

    return 0;

    /*
    Otra forma de hacerlo:

    Con operador ternario, se pregunta "Es x mayor que 100? entonces...."

    x>100? k=1:k=13;

    for (int i=0; i<=100; i++) {

        t=3;

        x % 3?
        cout << "Coca" : t=1;

        x % 5?
        cout << "Cola" : t=2;

        if (t=3) {
            cout << i;
        }
    }

    return 0;
    */

}