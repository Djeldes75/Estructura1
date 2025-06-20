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

    int a = 1, b = 1, c;

    double total = 0.5 + 0.25; // Hora 1 y 2
    
    for (int i = 3; i <= 24; i++) {
        c = a + b;
        total += (double)c / (1 << i);
        a = b;
        b = c;
    }
    
    cout << "El reloj se atrasa: " << total << " minutos en 24 horas" << endl;
    
    return 0;
}