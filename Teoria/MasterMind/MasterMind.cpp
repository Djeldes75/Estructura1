/*
-------------------------------------------------------------------------------------
Tarea: MasterMind para Principiantes (C++)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------
Descripción:
    Master Mind es un juego que consiste en adivinar 4 números ocultos. Los números están en un
    rango de 1 a 6. Tendrá 10 intentos para adivinar a clave oculta de 4 números (o dígitos) entre 1
    y 6. La mejor calificación se obtendrá haciendo el mínimo de intentos para adivinar la clave.

RESTRICCIONES:
    A. El algoritmo puede generar la clave de manera aleatoria, sin embargo, no debe repetirse
    ningún número en celdas distintas, pues de ser así, el nivel no sería para beginners.

    B. El algoritmo debe validar la entrada de datos del usuario para indicar si no es válida o si
    esta fuera de rango.

    C. El programa en cada paso deberá colocar las pistas adecuadas:
        a. X si el digito no está en la clave seleccionada
        b. C si el digito está en la misma posición que la clave, es decir, frente a frente.
        c. F si el digito está en la clave seleccionada pero no en la posición correcta.

INTEGRANTES (Grupo 6):
    Samira Vasquez - 1125467        
    Dominique Jeldes - 1121623      
    Enmanuel Carrasco - 1124404     
    Juan Castillo - 1127310         
    Sebastian Ventura - 1125467     
    Elianyer Gomez - 1118021        

Fecha: 21/05/2025

*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    //VARIABLES DEL JUEGO
    int clave[4];
    int jugadas[4];
    char pista[4];
    int i, j;
    int aciertos;
    int intentosAnteriores[10][4];
    int numIntentos = 0;

    //INICIALIZACIÓN
    srand(time(0));

    cout << "===    MASTERMIND  ===\n" << endl;
    cout << "La computadora genero una clave secreta de 4 numeros del 1 al 6" << endl;
    cout << "Los numeros no se repiten" << endl;
    cout << "Tienes 10 intentos para adivinarla\n" << endl;
    cout << "===    INSTRUCCIONES   ===\n" << endl;
    cout << "C = numero correcto en lugar correcto" << endl;
    cout << "F = numero correcto pero en lugar incorrecto" << endl;
    cout << "X = numero que no esta en la clave" << endl;
    cout << endl;

    //GENERAR CLAVE SECRETA
    bool usado[7] = { false };

    for (i = 0; i < 4; i++) {

        int numero;

        do {

            numero = rand() % 6 + 1;

        } while (usado[numero]);

        clave[i] = numero;

        usado[numero] = true;
    }

    //JUEGO PRINCIPAL
    for (i = 0; i < 10; i++) {

        cout << "--- INTENTO " << (i + 1) << " DE 10 ---" << endl;

        bool entradaValida = false;

        //LEER ENTRADA HASTA QUE SEA VÁLIDA
        while (!entradaValida) {

            cout << "Escribe 4 numeros del 1 al 6 (Ej: 1234 o 1 2 3 4): ";
            string entrada;
            cin >> entrada;

            //VALIDAR ENTRADA UNIDA (1234)
            if (entrada.length() == 4) {

                bool todoNumeros = true;

                for (int k = 0; k < 4; k++) {

                    if (entrada[k] >= '1' && entrada[k] <= '6') {

                        jugadas[k] = entrada[k] - '0';

                    }
                    else {

                        cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                        todoNumeros = false;

                        break;
                    }
                }
                if (!todoNumeros) continue;
            }
            //VALIDAR ENTRADA SEPARADA (1 2 3 4)
            else {

                if (entrada.length() == 1 && entrada[0] >= '1' && entrada[0] <= '6') {

                    jugadas[0] = entrada[0] - '0';

                }
                else {

                    cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                    continue;
                }

                bool errorLectura = false;

                for (j = 1; j < 4; j++) {

                    if (!(cin >> jugadas[j]) || jugadas[j] < 1 || jugadas[j] > 6) {

                        cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                        cin.clear();

                        cin.ignore(1000, '\n');

                        errorLectura = true;

                        break;
                    }
                }
                if (errorLectura) continue;
            }

            //VALIDAR SIN DUPLICADOS
            bool sinRepetir = true;

            for (int a = 0; a < 4; a++) {

                for (int b = a + 1; b < 4; b++) {

                    if (jugadas[a] == jugadas[b]) {

                        cout << "ERROR: No se permiten duplicados.\n" << endl;

                        sinRepetir = false;

                        break;
                    }
                }
                if (!sinRepetir) break;
            }
            if (!sinRepetir) continue;

            //VALIDAR NO REPETIR INTENTOS ANTERIORES
            bool esDuplicado = false;

            for (int ant = 0; ant < numIntentos; ant++) {

                bool mismaJugada = true;

                for (int pos = 0; pos < 4; pos++) {

                    if (jugadas[pos] != intentosAnteriores[ant][pos]) {

                        mismaJugada = false;

                        break;
                    }
                }
                if (mismaJugada) {

                    cout << "ERROR: Claves duplicadas en intentos.\n" << endl;

                    esDuplicado = true;

                    break;
                }
            }
            if (esDuplicado) continue;

            //ENTRADA VÁLIDA
            entradaValida = true;
        }

        //GUARDAR INTENTO VÁLIDO
        for (int pos = 0; pos < 4; pos++) {

            intentosAnteriores[numIntentos][pos] = jugadas[pos];
        }
        numIntentos++;

        //GENERAR PISTAS
        aciertos = 0;

        for (j = 0; j < 4; j++) {

            pista[j] = 'X';
        }

        for (int pos1 = 0; pos1 < 4; pos1++) {

            for (int pos2 = 0; pos2 < 4; pos2++) {

                if (jugadas[pos1] == clave[pos2] && pos1 == pos2) {

                    pista[pos1] = 'C';

                    aciertos++;
                }
                else if (jugadas[pos1] == clave[pos2] && pos1 != pos2) {

                    if (pista[pos1] != 'C') {

                        pista[pos1] = 'F';
                    }
                }
            }
        }

        //MOSTRAR PISTAS
        cout << "Pistas:   ";

        for (j = 0; j < 4; j++) {

            cout << pista[j] << " ";
        }
        cout << endl;

        //VERIFICAR SI GANÓ
        if (aciertos == 4) {

            cout << "*** FELICIDADES GANASTE ***\n" << endl;
            cout << "Adivinaste la clave secreta!" << endl;
            cout << "Clave secreta: ";

            for (j = 0; j < 4; j++) {

                cout << clave[j] << " ";

            }
            cout << endl;
            cout << "Lo lograste en " << (i + 1) << " intentos" << endl;

            int puntuacion = 10 - (i + 1);

            cout << "Tu puntuacion es: " << puntuacion << " puntos" << endl;

            return 0;
        }

        //SI ES EL ÚLTIMO INTENTO
        if (i == 9) {

            cout << "*** SE ACABARON LOS INTENTOS ***\n" << endl;
            cout << "La clave secreta era: ";

            for (j = 0; j < 4; j++) {

                cout << clave[j] << " ";
            }
            cout << endl;
            cout << "Mejor suerte la proxima vez!\n" << endl;
        }
    }

    return 0;
}
