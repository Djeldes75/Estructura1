/*
-------------------------------------------------------------------------------------------------------
Tarea: # Banquete de Políticos
Materia: IDS343-01-L LAB. ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
  Banquete de Políticos es un problema de programación
  que busca determinar cuántos senadores, congresistas e invitados asistieron a un banquete,
  dado que se conoce el total de personas y el costo total del banquete.


 Autor:
    Dominique Jeldes - 1121623


Fecha: 25/Jun/2025

*/


#include <iostream>
using namespace std;

int main() {
    int s, c, i;

    for (s = 0; s <= 100; s++) {

        for (c = 0; c <= 100 - s; c++) {

            i = 100 - s - c;
            int total = 75 * s + 99 * c + 40 * i;

            if (total == 7869) {
                cout << "Senadores: " << s << endl;
                cout << "Congresistas: " << c << endl;
                cout << "Invitados: " << i << endl;

                return 0;
            }
        }
    }

    cout << "No se encontró solución." << endl;
    return 0;
}
