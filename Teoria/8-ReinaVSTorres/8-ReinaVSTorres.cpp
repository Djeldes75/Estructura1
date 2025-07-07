/*
=====================================================================================================
Tarea: #8 - Reina VS Torres Enemigas
Materia: Estructura de Datos y Agoritmos 1; IDS343-01; 6-8pm; Trimestre May-Julio 2025
=====================================================================================================
Descripcion:
	Realizar un programa C++ que genere los movimientos posibles (según las reglas del ajedrez) de
	una Reina amenazada por dos Torres enemigas. El programa debe desplegar el tablero con las
	jugadas posibles de la Reina, colocando una V donde la reina pueda moverse sin ser eliminada y
	una X donde pueda moverse, pero ser eliminada por una o las dos torres enemigas.

RESTRICCIONES:
	A. El programa debe solicitar al usuario las posiciones de las dos torres enemigas y la de la
	reina.

	B. Las posiciones de las torres no deben solaparse, es decir, no deben estar en la misma
	posición. Las Torres deben estar en casillas distintas.

	C. La posición de la reina no debe coincidir con las de las torres.

	D. Debe desplegar el cuadro del ajedrez indicando a la reina con una R, las torres como T y
	las jugadas según se establece en el enunciado.

	A B C D E F G H
	1 X V V
	2 X R V V X V V V
	3 X V V
	4 X X T
	5 V X
	6 V V
	7 T X X
	8 V V

Ejemplo de la salida del programa:
	Si la reina se ubica en la fila 2 columna 2 y las torres enemigas
	en las filas 4 y 7 y columnas 1 y 5 respectivamente.
=====================================================================================================
Integrantes:
	Dominique Jeldes, 1121623
    Enmanuel Carrasco, 1124404
	Samira Jaquez, 1125467
    Juan Castillo, 1127310
    Sebastian Ventura, 1128066
    Elianyer Gomez, 1118021

Fecha de Entrega:
	8/Julio/2025

*/

#include <iostream>
#include <iomanip>

using namespace std;

// Variables globales siguiendo el enfoque del profesor
char tablero[8][8];
int t[2][2]; // t[0] = torre1 {fila, columna}, t[1] = torre2 {fila, columna}
int limifx = 1, limsx = 8, limify = 1, limsy = 8;
int reina_x, reina_y;

// Función recursiva para generar movimientos en una dirección específica
void Movimiento(int x, int y, int dir_x, int dir_y) {
    int mx = x + dir_x;
    int my = y + dir_y;

    // Verificar límites del tablero
    if (mx < limifx || mx > limsx || my < limify || my > limsy) {
        return; // Fuera del tablero
    }

    // Verificar si hay una torre en esta posición (bloquea el movimiento)
    if ((mx == t[0][0] && my == t[0][1]) || (mx == t[1][0] && my == t[1][1])) {
        return; // Torre bloquea el camino
    }

    // Verificar si esta posición está bajo ataque de alguna torre
    bool bajo_ataque = false;

    // Verificar ataque de torre 1
    if (mx == t[0][0] || my == t[0][1]) {
        bajo_ataque = true;
    }

    // Verificar ataque de torre 2
    if (mx == t[1][0] || my == t[1][1]) {
        bajo_ataque = true;
    }

    // Establecer la jugada en el tablero
    if (bajo_ataque) {
        tablero[mx - 1][my - 1] = 'X'; // Posición peligrosa
    }
    else {
        tablero[mx - 1][my - 1] = 'V'; // Posición segura
    }

    // Continuar recursivamente en la misma dirección
    Movimiento(mx, my, dir_x, dir_y);
}

void inicializarTablero() {
    // Limpiar tablero
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = ' ';
        }
    }

    // Colocar piezas
    tablero[reina_x - 1][reina_y - 1] = 'R';
    tablero[t[0][0] - 1][t[0][1] - 1] = 'T';
    tablero[t[1][0] - 1][t[1][1] - 1] = 'T';
}

// Función para generar todos los movimientos posibles de la reina
void generarMovimientos() {

    int direcciones[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Arriba-izq, arriba, arriba-der
        { 0, -1},          { 0, 1},  // Izquierda, derecha
        { 1, -1}, { 1, 0}, { 1, 1}   // Abajo-izq, abajo, abajo-der
    };

    // Generar movimientos en cada dirección
    for (int i = 0; i < 8; i++) {
        Movimiento(reina_x, reina_y, direcciones[i][0], direcciones[i][1]);
    }
}

// Función para mostrar el tablero
void mostrarTablero() {

    cout << "\n    A B C D E F G H\n";
    for (int i = 0; i < 8; i++) {
        cout << (i + 1) << " ";
        for (int j = 0; j < 8; j++) {
            cout << " " << tablero[i][j];
        }
        cout << "\n";
    }
    cout << "\nLeyenda:\n";
    cout << "R = Reina\n";
    cout << "T = Torre enemiga\n";
    cout << "V = Movimiento valido (seguro)\n";
    cout << "X = Movimiento peligroso (bajo ataque)\n\n";
}

// Función para validar entrada
bool validarRango(int valor) {
    return valor >= 1 && valor <= 8;
}

// Función para leer coordenadas
int leerCoordenada(const string& mensaje) {

    int coordenada;
    do {
        cout << mensaje;
        cin >> coordenada;
        if (!validarRango(coordenada)) {
            cout << "Error: Debe estar entre 1 y 8.\n";
        }
    } while (!validarRango(coordenada));
    return coordenada;
}

// Función para verificar que las posiciones no se solapen
bool posicionesValidas() {

    // Verificar que la reina no esté en la misma posición que las torres
    if ((reina_x == t[0][0] && reina_y == t[0][1]) ||
        (reina_x == t[1][0] && reina_y == t[1][1])) {
        return false;
    }

    // Verificar que las torres no estén en la misma posición
    if (t[0][0] == t[1][0] && t[0][1] == t[1][1]) {
        return false;
    }

    return true;
}

// Función para solicitar datos de entrada
void solicitarDatos() {

    cout << "=== Configuración del juego ===\n";

    do {
        cout << "\n--- Posición de la Reina ---\n";
        reina_x = leerCoordenada("Ingrese la fila de la Reina (1-8): ");
        reina_y = leerCoordenada("Ingrese la columna de la Reina (1-8): ");

        cout << "\n--- Posición de la Torre 1 ---\n";
        t[0][0] = leerCoordenada("Ingrese la fila de la Torre 1 (1-8): ");
        t[0][1] = leerCoordenada("Ingrese la columna de la Torre 1 (1-8): ");

        cout << "\n--- Posición de la Torre 2 ---\n";
        t[1][0] = leerCoordenada("Ingrese la fila de la Torre 2 (1-8): ");
        t[1][1] = leerCoordenada("Ingrese la columna de la Torre 2 (1-8): ");

        if (!posicionesValidas()) {
            cout << "\nError: Las posiciones no pueden coincidir. Intente de nuevo.\n";
        }
    } while (!posicionesValidas());
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "======== REINA VS TORRES ENEMIGAS ========\n";
    cout << "1. Jugar (configurar nuevas posiciones)\n";
    cout << "2. Mostrar tablero actual\n";
    cout << "3. Salir\n";
    cout << "==========================================\n";
    cout << "Seleccione una opcion: ";
}

int main() {

    int opcion;
    bool primerJuego = true;

    while (true) {

        mostrarMenu();
        cin >> opcion;

        switch (opcion) {

        case 1: {

            solicitarDatos();
            inicializarTablero();
            generarMovimientos();
            mostrarTablero();
            primerJuego = false;
            break;
        }

        case 2: {
            if (primerJuego) {
                cout << "\nError: Debe configurar el juego primero (opcion 1).\n";
            }
            else {
                mostrarTablero();
            }
            break;
        }

        case 3: {
            cout << "\nGracias por jugar!\n";
            return 0;
        }

        default: {
            cout << "Opción invalida. Seleccione 1, 2 o 3.\n";
            break;
        }
        }
    }

    return 0;
}