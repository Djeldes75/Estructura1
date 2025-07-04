/*
-------------------------------------------------------------------------------------------------------
Tarea: La Hora
Materia: IDS343-01-L LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   La hora es un número de cuatro dígitos, donde los dos primeros representan la hora y los dos últimos los minutos.
   Encontrar todas las horas donde h² + m² = hhmm

 Autor:
    Dominique Jeldes - 1121623

Fecha: 25/Jun/2025

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "Buscando todas las horas donde h^2 + m^2 = hhmm" << endl;
    cout << "================================================" << endl;

    int contador = 0;

    // Buscar desde 00:00 hasta 23:59
    for (int h = 0; h < 24; h++) {
        for (int m = 0; m < 60; m++) {
            int hhmm = h * 100 + m;
            int suma_cuadrados = h * h + m * m;

            if (suma_cuadrados == hhmm) {
                contador++;
                cout << "Solucion " << contador << ": ";
                cout << setfill('0') << setw(2) << h << ":"
                    << setfill('0') << setw(2) << m;
                cout << " -> " << h << "^2 + " << m << "^2 = "
                    << h * h << " + " << m * m << " = " << hhmm << endl;
            }
        }
    }

    cout << "================================================" << endl;
    if (contador == 0) {
        cout << "No se encontraron soluciones." << endl;
    }
    else {
        cout << "Total de soluciones encontradas: " << contador << endl;
    }

    return 0;
}