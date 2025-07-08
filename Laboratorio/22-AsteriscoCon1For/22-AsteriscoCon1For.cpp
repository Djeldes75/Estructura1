/*
-------------------------------------------------------------------------------------------------------
Tarea: AsteriscoCon1For
Materia: IDS343-01 ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
  
  Hacer un programa C++ que genere el siguiente patrón utilizando solo un for e imprimiendo un
  * a la vez.
  
  El patrón es el siguiente:

  *
  **
  ***
  ****
  *****
  ******
  *******
  
 Autor:
    Dominique Jeldes - 1121623


Fecha: 7/Jul/2025

*/

#include <iostream>
using namespace std;

int main() {
    int total = 28; // Total de caracteres a imprimir (* y \n)
    int fila = 1;
    int cuenta = 0;

    for (int i = 1; i <= total; ++i) {
        cout << "*";
        ++cuenta;

        // Pequeño retraso (delay) usando un bucle vacío
        for (volatile int d = 0; d < 140000000; ++d);

        if (cuenta == fila) {
            cout << endl;
            ++fila;
            cuenta = 0;
        }
    }

    return 0;
}