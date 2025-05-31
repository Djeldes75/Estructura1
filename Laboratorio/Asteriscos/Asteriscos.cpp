/*
-----------------------------------------------------------------------------------------
TAREA: Asteriscos (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripcion:

    Hacer un programa en C++ que genere un patrón de asteriscos con 7 filas,
    donde cada fila tiene la cantidad de asteriscos correspondiente a su número de fila.

    Fila 1: 1 asterisco.
    Fila 2: 2 asteriscos.
    Fila 3: 3 asteriscos.
    Y así hasta la fila 7 con 7 asteriscos.

    Resultado:

    *
    **
    ***
    ****
    *****
    ******
    *******
    
    Restricciones:
        1. Usa bucles for anidados.
        2. Imprime un asterisco a la vez.
        3. No requiere entrada del usuario.

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 23/May/2025
*/


#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 7; i++) {
        for (int asteriscos = 1; asteriscos <= i; asteriscos++) {
            cout << "*";
            //cout.flush();
            //Si no se ve la animacion, descomentar el "cout.flush();". Se utilia para forzar que se vea el asterisco

            for (int pausa = 0; pausa < 1000000000; pausa++) {
            }//Para que se vea bonito nomas, y simplemente lo  imprima 1a1
        }
        cout << "\n";
    }
    return 0;
}