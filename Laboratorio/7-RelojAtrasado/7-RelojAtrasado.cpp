/*
-----------------------------------------------------------------------------------------
TAREA: El reloj que atrasa  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción: 
    Un reloj se atrasa una cantidad de tiempo distinta en cada hora, de acuerdo con el cuadro siguiente:
    Hora - Tiempo - Atrasado
      1     1/2      minuto
      2     1/4      minuto
      3     2/8      minuto
      4     3/16     minuto
      5     5/32     minuto
      6     8/64     minuto
      7     13/128   minuto
    hasta     --      --
      n     f(n)/2^n  minutos

    Donde f(n) es el termino enesimo de la serie de Fibonacci, en el cual f(1) = 1, f(2) = 1, f(3) = 2, f(4) = 3, f(5) = 5,
    f(6) = 8, f(7) = 13, ..., y, en general, f(n) = f(n-1) + f(n-2) para todo n >= 3.

    Cuantos minutos se atrasara este reloj en 24 horas?
    
INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 20/Jun/2025
*/

#include <iostream>

using namespace std;

int main() {

    long long fib1 = 1, fib2 = 1, fibActual;

    double tiempoTotal = 0.0;

    for (int hora = 1; hora <= 24; hora++) {

        if (hora == 1) {
            fibActual = 1;
        }
        else if (hora == 2) {
            fibActual = 1;
        }
        else {
            fibActual = fib1 + fib2;
            fib1 = fib2;
            fib2 = fibActual;
        }

        double atraso = (double)fibActual / (1LL << hora);

        tiempoTotal += atraso;
    }

    cout << "Total de minutos atrasados en 24 horas: " << tiempoTotal << " minutos." << endl;

    return 0;
}
