/*
-----------------------------------------------------------------------------------------
TAREA: Generacion de N primos  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripcion:
    Programa que genera los primeros N numeros primos usando el algoritmo de Wheel
    Factorization optimizado con patron 6k±1. Complejidad temporal O(n²√n) con
    factor de optimizacion significativo al evaluar solo candidatos 6k-1 y 6k+1.
INTEGRANTE:
    Dominique Jeldes - 1121623
Fecha: 20/Jun/2025

*/
#include <iostream>

using namespace std;

bool esPrimo(int numero) {

    if (numero < 2) return false;
    if (numero == 2 || numero == 3) return true;
    if (numero % 2 == 0 || numero % 3 == 0) return false;

    // Solo revisar numeros de la forma 6k±1
    for (int i = 5; i * i <= numero; i += 6) {

        if (numero % i == 0 || numero % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {

    int n;
    cout << "Cuantos primos quieres? ";
    cin >> n;

    if (n <= 0) return 0;

    if (n >= 1) cout << "2 ";
    if (n >= 2) cout << "3 ";
    if (n <= 2) return 0;

    int contador = 2;
    int base = 6;

    // Usar rueda 6: solo revisar 6k±1
    while (contador < n) {

        // Revisar 6k-1
        if (esPrimo(base - 1)) {
            cout << (base - 1) << " ";
            contador++;
            if (contador >= n) break;
        }

        // Revisar 6k+1
        if (esPrimo(base + 1)) {
            cout << (base + 1) << " ";
            contador++;
        }

        base += 6;
    }

    cout << endl;
    return 0;
}