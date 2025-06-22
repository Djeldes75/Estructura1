/*
-----------------------------------------------------------------------------------------
TAREA: Serie Fibonacci  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    Las series de Fibonacci son sucesiones de numeros que reflejan una interesante relacion.
    Constan del conjunto ordenado de cifras cuyo valor se forma con la suma de los dos numeros anteriores,
    lo que da origen a otras relevantes inferencias matematicas.

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 20/Jun/2025
*/
#include <iostream>

using namespace std;

int main() {

    int x = 1;
    int y = 1;
    int siguiente;

    cout << "Serie de Fibonacci:" << endl;

    cout << x << ",\n" << y;

    for (int i = 3; i <= 30; i++) {
        siguiente = x + y;
        cout << ",\n" << siguiente;

        x = y;
        y = siguiente;
    }

    cout << endl;
    return 0;
}
