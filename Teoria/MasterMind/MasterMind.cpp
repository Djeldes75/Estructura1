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

    Mas abajo se muestras una partida para adivinar la clave. Se selecciona 5 3 6 y 1 como clave a
    adivinar. En el caso en donde todos los dígitos esten caliente (C) entonces el juego debe
    presentar que gano y la puntuación será 10 – (Intentos).
    En el caso que gane en el intento 3, su calificación seria 7.

INTEGRANTES (Grupo 6):
    Samira Vasquez - 1125467        4.5
    Dominique Jeldes - 1121623      5
    Enmanuel Carrasco - 1124404     4
    Juan Castillo - 1127310         4
    Sebastian Ventura - 1125467     5
    Elianyer Gomez - 1118021        4

Fecha: 21/05/2025

*/

#include <iostream> //Entrada y salida estandar
#include <cstdlib> //Funciones de utilidad
#include <ctime> //Contiene funcion Time(0), secuencia
#include <string>  // Compilador carga STD

using namespace std;

int main() {
    // Variables del juego - muy simple
    int clave[4];        //Clave
    int jugadas[4];      //Input
    char pista[4];       //Pistas c,f,x0
    int i, j;            // Para los ciclos
    int aciertos;        // Cuantos numeros correctos tiene

    // Inicializar numeros aleatorios
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

    // Generar la clave secreta automaticamente
    bool usado[7] = { false }; // Para marcar numeros del 1 al 6 (indice 0 no se usa)

    for (i = 0; i < 4; i++) {

        int numero;

        do {
            numero = rand() % 6 + 1; // Numero aleatorio entre 1 y 6
        } while (usado[numero]); // Repetir hasta encontrar uno no usado

        clave[i] = numero;

        usado[numero] = true; // Marcar como usado
    }

    // Array para guardar intentos anteriores
    int intentosAnteriores[10][4];

    int numIntentos = 0;

    // El juego principal (10 intentos)
    for (i = 0; i < 10; i++) {

        cout << "--- INTENTO " << (i + 1) << " DE 10 ---" << endl;

        cout << "Escribe 4 numeros del 1 al 6 (Ej: 1234 o 1 2 3 4): ";

        string entrada;

        cin >> entrada;

        // Si escribio todo junto (como 1234)

        if (entrada.length() == 4) {

            bool todoNumeros = true;

            for (int k = 0; k < 4; k++) {

                if (entrada[k] >= '1' && entrada[k] <= '6') {

                    jugadas[k] = entrada[k] - '0'; // Convertir char a int
                }
                else {

                    cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                    todoNumeros = false;

                    break;
                }
            }
            if (!todoNumeros) continue; // Pasar al siguiente intento
        

        }
        // Si escribio separado (como 1 2 3 4)

        else {

            // Leer el primer numero que ya tenemos
            if (entrada.length() == 1 && entrada[0] >= '1' && entrada[0] <= '6') {

                jugadas[0] = entrada[0] - '0';
            }
            else {

                cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                continue;
            }

            // Leer los otros 3 numeros
            for (j = 1; j < 4; j++) {

                if (!(cin >> jugadas[j]) || jugadas[j] < 1 || jugadas[j] > 6) {

                    cout << "ERROR: Solo numeros del 1 al 6.\n" << endl;

                    cin.clear();

                    cin.ignore(1000, '\n');

                    break;
                }
            }
            if (j < 4) continue; //Si, hubo error, continua sgt attempt
        }

        // Validar que no se repitan numeros en la jugada actual
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

        if (!sinRepetir) continue; // Pasar al siguiente intento

        // Validar que no sea igual a un intento anterior
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

        if (esDuplicado) continue; // Pasar al siguiente intento

        // Si llegamos aqui, todo bien y lo guarda

        for (int pos = 0; pos < 4; pos++) {

            intentosAnteriores[numIntentos][pos] = jugadas[pos];
        }
        numIntentos++;

        // Dar las pistas
        aciertos = 0;

        // Primero ponemos X en todas las posiciones
        for (j = 0; j < 4; j++) {

            pista[j] = 'X';
        }

        //pos1 = posicion actual del jugador
        // pos2 = posicion actual dentro de la clave xd
        
        // Ahora vemos que pistas dar
        for (int pos1 = 0; pos1 < 4; pos1++) {

            for (int pos2 = 0; pos2 < 4; pos2++) {

                // Si el numero esta en el mismo lugar = C
                if (jugadas[pos1] == clave[pos2] && pos1 == pos2) {

                    pista[pos1] = 'C';

                    aciertos++;
                }
                // Si el numero esta pero en otro lugar = F
                else if (jugadas[pos1] == clave[pos2] && pos1 != pos2) {

                    // Solo ponemos F si no es C
                    if (pista[pos1] != 'C') {

                        pista[pos1] = 'F';
                    }
                }
            }
        }

        // Mostrar las pistas
        cout << "Pistas:   ";

        for (j = 0; j < 4; j++) {

            cout << pista[j] << " ";
        }

        cout << endl;

        // Ver si gano (todos los digitos estan "caliente" = C)
        if (aciertos == 4) {

            cout << "*** FELICIDADES GANASTE ***\n" << endl;
            cout << "Adivinaste la clave secreta!" << endl;
            cout << "Clave secreta: ";

            for (j = 0; j < 4; j++) {

                cout << clave[j] << " ";
            }
            cout << endl;

            cout << "Lo lograste en " << (i + 1) << " intentos" << endl;

            // Calcular puntuacion: para los 10 intentos
            int puntuacion = 10 - (i + 1);

            cout << "Tu puntuacion es: " << puntuacion << " puntos" << endl;

            return 0; // Terminar el programa
        }

        // Si es el ultimo intento y no gano
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
