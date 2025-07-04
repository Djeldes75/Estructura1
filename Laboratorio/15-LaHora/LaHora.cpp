/*
-------------------------------------------------------------------------------------------------------
Tarea: La Hora
Materia: IDS343-01-L LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   La hora es un número de cuatro dígitos, donde los dos primeros representan la hora y los dos últimos los minutos.

 Autor:
    Dominique Jeldes - 1121623

Fecha: 25/Jun/2025

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    for (int h = 1; h < 24; h++) { // desde 1 para evitar 00:00
        for (int m = 0; m < 60; m++) {
            int hhmm = h * 100 + m;
            if (h * h + m * m == hhmm) {
                cout << "La hora es: ";
                cout << setfill('0') << setw(2) << h << ":"
                    << setfill('0') << setw(2) << m << endl;
                return 0;
            }
        }
    }
    return 0;
}