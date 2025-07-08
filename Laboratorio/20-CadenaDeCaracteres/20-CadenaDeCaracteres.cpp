/*
-------------------------------------------------------------------------------------------------------
Tarea: Cadena de Caracteres
Materia: IDS343-01 ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   Hacer un programa en C++, que dada una cadena de caracteres la revierta de la manera
   más eficiente posible, es decir, empleando el menor número de iteraciones.

   Ejemplo:  Triangulo
             olugnairT

 Autor:
    Dominique Jeldes - 1121623


Fecha: 7/Jul/2025

*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string cadena;
    
    cout << "Ingrese una cadena: ";
    getline(cin, cadena); // Permite espacios también

    int n = cadena.length();

    // Inversión eficiente: intercambiamos caracteres desde los extremos
    for (int i = 0; i < n / 2; i++) {
        char temp = cadena[i];
        cadena[i] = cadena[n - 1 - i];
        cadena[n - 1 - i] = temp;
    }

    cout << "Cadena invertida: " << cadena << endl;

    return 0;
}