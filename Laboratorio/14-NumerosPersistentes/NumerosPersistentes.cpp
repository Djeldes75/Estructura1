/*
-------------------------------------------------------------------------------------------------------
Tarea: Números Persistentes
Materia: IDS343-01-L LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   Números persistentes son aquellos que al multiplicar sus dígitos repetidamente hasta que el resultado sea un solo dígito,

 Autor:
    Dominique Jeldes - 1121623


Fecha: 25/Jun/2025

*/

#include <iostream>

using namespace std;

// Función que multiplica los dígitos de un número
int multiplicarDigitos(int n) {
    int producto = 1;
    while (n > 0) {
        producto *= (n % 10);
        n /= 10;
    }
    return producto;
}

// Función que calcula la persistencia de un número
int calcularPersistencia(int n) {
    int contador = 0;
    while (n >= 10) { // mientras tenga más de un dígito
        n = multiplicarDigitos(n);
        contador++;
    }
    return contador;
}

int main() {
    int numeroMayorPersistencia = 0;
    int mayorPersistencia = 0;

    // Recorremos los números de dos dígitos
    for (int i = 10; i <= 99; i++) {
        int p = calcularPersistencia(i);
        if (p > mayorPersistencia) {
            mayorPersistencia = p;
            numeroMayorPersistencia = i;
        }
    }

    cout << "El numero de dos digitos con mayor persistencia es: " << numeroMayorPersistencia << endl;
    cout << "Su persistencia es: " << mayorPersistencia << endl;

    return 0;
}