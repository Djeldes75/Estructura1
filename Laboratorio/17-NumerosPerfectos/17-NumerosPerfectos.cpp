/*
-------------------------------------------------------------------------------------------------------
Tarea:  Números Perfectos
Materia: IDS343-01L-LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripción:

   Números perfectos son aquellos enteros que tienen la curiosa propiedad de ser 
   iguales a la suma de todos sus divisores (excluyendo a ellos mismos). Así, el 6
   y el 28 son números perfectos, puesto que:

			  6 = 1 + 2 + 3
			  28 = 1 + 2 + 4 + 7 + 14
   
   Estos números han atraído desde siempre la curiosidad de los estudiosos de las 
   matemáticas. A pesar de que ya en el siglo III a.C, el matemático griego Euclides dedujo
   una fórmula para generarlos, todavía hoy se sabe bastante poco acerca de ellos. Sólo se conocen unos
   cuantos, de los cuales ninguno es impar.

   ¿Sabrías generar todos los números perfectos con menos de cuatro cifras?

Autor:
Dominique Jeldes ID: 1121623

Fecha:
30/6/2025

*/


#include <iostream>

using namespace std;

int main() {

	cout << "Numeros perfectos menores que 1000:" << endl;

	for (int num = 2; num < 10000; num++) {

		int suma = 0;

		// Calcular la suma de los divisores propios

		for (int i = 1; i < num; i++) {
			if (num % i == 0) {
				suma += i;

			}
		}


		if (suma == num) {
			cout << num << " es un numero perfecto." << endl;
		}

	}
	  
	return 0;
}