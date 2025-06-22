/*
-----------------------------------------------------------------------------------------
TAREA: Descomponer Factores Primos  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    Programa que descompone un número en sus factores primos
    Ejemplo: 60 = 2² × 3¹ × 5¹

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 17/Jun/2025
*/

#include <iostream>

using namespace std;

bool esPrimo(long long n) {

    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (long long i = 5; i * i <= n; i += 6) {

        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void factorizar(long long n) {

    cout << n << " = ";

    bool primero = true;

    // Factor 2
    if (n % 2 == 0) {

        int exp = 0;

        while (n % 2 == 0) {
            n >>= 1;
            exp++;
        }
        cout << "2";

        if (exp > 1) cout << "^" << exp;

        primero = false;
    }

    // Factor 3
    if (n % 3 == 0) {

        int exp = 0;

        while (n % 3 == 0) {
            n /= 3;
            exp++;
        }
        if (!primero) cout << " * ";

        cout << "3";

        if (exp > 1) cout << "^" << exp;

        primero = false;
    }

    // Factores 6k±1
    for (long long i = 5; i * i <= n; i += 6) {

        if (n % i == 0) {

            int exp = 0;

            while (n % i == 0) {

                n /= i;
                exp++;
            }

            if (!primero) cout << " * ";

            cout << i;

            if (exp > 1) cout << "^" << exp;

            primero = false;
        }

        // Probar 6k+1
        if (n % (i + 2) == 0) {

            int exp = 0;

            while (n % (i + 2) == 0) {

                n /= (i + 2);
                exp++;
            }
            if (!primero) cout << " * ";

            cout << (i + 2);

            if (exp > 1) cout << "^" << exp;

            primero = false;
        }
    }

    // Factor primo restante
    if (n > 1) {

        if (!primero) cout << " * ";

        cout << n;
    }
    cout << endl;
}

int main() {

    long long numero;

    cout << "Ingrese numero: ";
    cin >> numero;

    cout << "\n--- Verificacion De primalidad ---" << endl;

    if (esPrimo(numero)) {

        cout << numero << " ES primo" << endl;
    }
    else {
        cout << numero << " NO es primo" << endl;
    }

    cout << "\n--- Factorizacion prima ---" << endl;
    factorizar(numero);

    return 0;
}
