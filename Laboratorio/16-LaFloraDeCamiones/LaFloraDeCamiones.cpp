/*
-------------------------------------------------------------------------------------------------------
Tarea: La Flota de Camiones
Materia: IDS343-01-L LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   La flota de camiones "La Tortuga" se encarga de transportar mercancías por todo el país.

 Autor:
    Dominique Jeldes - 1121623


Fecha: 25/Jun/2025

*/

#include <iostream>
using namespace std;

int main() {
    cout << "=== FLOTA DE CAMIONES 'LA TORTUGA' ===" << endl;
    cout << "Numeros menores a 500 cuyo cuadrado termina en el mismo numero:" << endl;
    cout << endl;

    int contador = 0;

    // Recorremos todos los números menores a 500
    for (int n = 1; n < 500; n++) {
        int cuadrado = n * n;

        // Calculamos cuántos dígitos tiene n
        int temp = n;
        int digitos = 0;
        while (temp > 0) {
            digitos++;
            temp = temp / 10;
        }

        // Calculamos 10^digitos para obtener las últimas cifras
        int potencia = 1;
        for (int i = 0; i < digitos; i++) {
            potencia = potencia * 10;
        }

        // Verificamos si las últimas cifras del cuadrado coinciden con n
        int ultimas_cifras = cuadrado % potencia;

        if (ultimas_cifras == n) {
            contador++;
            cout << "Camion " << contador << ": Numero " << n;
            cout << " -> " << n << "² = " << cuadrado << endl;
        }
    }

    cout << endl;
    cout << "=== RESUMEN ===" << endl;
    cout << "Total de camiones en la flota: " << contador << endl;
    cout << endl;

    // Mostramos solo los números encontrados
    cout << "Los numeros de los camiones son: ";
    for (int n = 1; n < 500; n++) {
        int cuadrado = n * n;
        int temp = n;
        int digitos = 0;
        while (temp > 0) {
            digitos++;
            temp = temp / 10;
        }

        int potencia = 1;
        for (int i = 0; i < digitos; i++) {
            potencia = potencia * 10;
        }

        int ultimas_cifras = cuadrado % potencia;

        if (ultimas_cifras == n) {
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}