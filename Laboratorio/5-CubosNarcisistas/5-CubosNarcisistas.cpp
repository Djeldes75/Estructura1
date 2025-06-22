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

Fecha: 16/Jun/2025
*/
#include <iostream>

using namespace std;

int main() {
    // Buscar en el rango 1-999 para cubrir todos los números de hasta 3 dígitos
    for (int n = 1; n <= 999; n++) {

        int s = 0; int t = n; // s =Acumulador para la suma de los cubos; t = Copia de n para procesar

        // Calcular la suma de los cubos de los dígitos
        while (t != 0) {
            int digito = t % 10;       // Obtener el último dígito
            s += digito * digito * digito; // Sumar el cubo del dígito
            t /= 10;                   // Eliminar el último dígito
        }

        // Si n es igual a la suma de los cubos de sus dígitos, imprimirlo
        if (n == s) {
            cout << n << endl;
        }
    }
    return 0;
}
