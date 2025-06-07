/*
-----------------------------------------------------------------------------------------
TAREA: La Piramide de Bolas  (LABORATORIO)
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------
Descripción:
    Con un grupo de 10,000 bolas se forma una pirámide de base cuadrada, con una única bola
    en su vértice superior y un número cuadrado perfecto de ellas en cada capa.
    ¿Cuántas capas pueden hacerse? Y ¿Cuántas bolas sobrarán?

INTEGRANTE:
    Dominique Jeldes - 1121623

Fecha: 29/May/2025

*/

#include <iostream>

using namespace std;

int main() {

    int totalBolas = 10000;
    int bolasUsadas = 0;
    int capas = 0;

    // Construir la pirámide capa por capa
    for (int capa = 1; ; capa++) {

        int bolasEnCapa = capa * capa;  // Capa 1: 1 bola, Capa 2: 4 bolas, etc.

        // Verificar si caben las bolas de esta capa
        if (bolasUsadas + bolasEnCapa > totalBolas) {

            break;
        }

        bolasUsadas += bolasEnCapa;

        capas++;
    }

    // Calcular bolas sobrantes
    int bolasSobrantes = totalBolas - bolasUsadas;

    //Resultados
    cout << "1. Cuantas capas pueden hacerse?: " << capas << endl;
    cout << "\n2. Cuantas bolas sobraran?: " << bolasSobrantes << endl;
    cout << "\n3. Total de bolas usadas: " << bolasUsadas << " bolas" << endl;

    return 0;

}
