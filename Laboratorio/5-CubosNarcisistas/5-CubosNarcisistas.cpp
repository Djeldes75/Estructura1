/*
-----------------------------------------------------------------------------------------
TAREA: Los Cubos Narcisistas  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    AAAAA

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 29/May/2025

*/
#include <iostream>

using namespace std;

int main()
{
    cout << "Cubos narcisistas:" << endl;

    for (int n = 1; n <= 500; n++)
    {
        int s = 0, t = n;

        while (t)
        {
            s += (t % 10) * (t % 10) * (t % 10), t /= 10;
            if (n == s)
            {
                cout << n << endl;
            }
        }
    }
}
