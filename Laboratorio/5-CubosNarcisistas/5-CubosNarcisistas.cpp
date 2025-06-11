/*
-----------------------------------------------------------------------------------------
TAREA: Los Cubos Narcisistas  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción: 
    Son cubos narcisistas aquellos numeros enteros positivos que son exactamente iguales a la suma de sus digitos elevados al cubo.
    Es decir, 370 y 371 son ambos cubos narcisistas, ya que:
    370 = 3^3 + 7^3 + 0^3
    371 = 3^3 + 7^3 + 1^3
    Sin embargo, 483 != 4^3 + 8^3 + 3^3
    
    Excluyendo el caso trivial del numero 1, solo existen otros tres cubos narcisistas. Cuales son los cuatro cubos narcisistas?

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 11/Jun/2025

*/
#include <iostream>
using namespace std;

int main() {

    for (int n = 1; n <= 500; n++) {

        int s = 0, t = n;

        while (t) s += (t % 10) * (t % 10) * (t % 10), t /= 10;

        if (n == s) cout << n << endl;
    }
}