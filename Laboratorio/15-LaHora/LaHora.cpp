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
using namespace std;

int main() {
    for (int hora = 0; hora < 24; hora++) {
        for (int minuto = 0; minuto < 60; minuto++) {
            int h1 = hora / 10;
            int h2 = hora % 10;
            int m1 = minuto / 10;
            int m2 = minuto % 10;

            int suma = h1 * h1 + h2 * h2 + m1 * m1 + m2 * m2;
            int hhmm = hora * 100 + minuto;

            if (suma == hhmm) {
                cout << "La hora es: ";
                if (hora < 10) cout << "0";
                cout << hora << ":";
                if (minuto < 10) cout << "0";
                cout << minuto << endl;
            }
        }
    }

    return 0;
}