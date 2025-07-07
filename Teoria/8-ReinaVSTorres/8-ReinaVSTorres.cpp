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

// Estructura para representar una posición
struct Posicion {
    int fila, columna;
    Posicion(int f = 0, int c = 0) : fila(f), columna(c) {}
};

// Variables globales siguiendo el enfoque del profesor
char tablero[8][8];
int t[2][2]; // t[0] = torre1, t[1] = torre2
int limifx = 1, limsx = 8, limify = 1, limsy = 8;
Posicion reina;
Posicion torre1, torre2;

// Helper to validate range 1-8
bool validarRango(int v) {
    return v >= 1 && v <= 8;
}

// Helper to clear input buffer
void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Overload posicionesValidas to accept Posicion for torres
bool posicionesValidas(const Posicion& r, const Posicion& t1, const Posicion& t2) {
    if ((r.fila == t1.fila && r.columna == t1.columna) ||
        (r.fila == t2.fila && r.columna == t2.columna) ||
        (t1.fila == t2.fila && t1.columna == t2.columna)) {
        return false;
    }
    return true;
}

#pragma region Validaciones

int validarEntero(const char* mensaje) {

    int valor;
    char caracterSiguiente;
    bool entradaValida = false;
    cout << mensaje;
    while (!entradaValida) {
        if (cin >> valor) {
            caracterSiguiente = cin.peek();
            if (caracterSiguiente == '\n' || caracterSiguiente == ' ') {
                cin.ignore(10000, '\n');
                entradaValida = true;
            }
            else {
                cout << "ERROR: Entrada invalida. Intente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            // Error al leer el entero
            cout << "ERROR: Debe ingresar un numero valido. Intente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return valor;
}

int leerOpcionMenu() {

    int opcion;
    bool opcionValida = false;
    while (!opcionValida) {
        opcion = validarEntero("");
        if (opcion >= 1 && opcion <= 3) {
            opcionValida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Seleccione una opcion valida (1-3): ";
        }
    }
    return opcion;
}

int leerCoordenada(const char* mensaje) {

    int coordenada;
    bool coordenadaValida = false;
    while (!coordenadaValida) {
        coordenada = validarEntero(mensaje);
        if (coordenada >= 1 && coordenada <= 8) {
            coordenadaValida = true;
        }
        else {
            cout << "ERROR: La coordenada debe estar entre 1 y 8. Intente nuevamente: ";
        }
    }
    return coordenada;
}


Posicion leerPosicion(const char* pieza) {

    cout << "\n--- Ingresando posicion de " << pieza << " ---\n";
    int fila = leerCoordenada("Ingrese la fila (1-8): ");
    int columna = leerCoordenada("Ingrese la columna (1-8): ");
    return Posicion(fila, columna);
}
#pragma endregion

// Función para verificar si las posiciones no se solapen
bool posicionesValidas(const Posicion& r, int torre1_fila, int torre1_col, int torre2_fila, int torre2_col) {

    if ((r.fila == torre1_fila && r.columna == torre1_col) ||
        (r.fila == torre2_fila && r.columna == torre2_col) ||
        (torre1_fila == torre2_fila && torre1_col == torre2_col)) {
        return false;
    }
    return true;
}

// Función para solicitar posición con validación
Posicion solicitarPosicion(const string& pieza) {

    int f, c;
    while (true) {
        cout << "Ingrese la posicion de " << pieza << " (fila columna): ";
        if (cin >> f >> c) {
            if (validarRango(f) && validarRango(c)) {
                return Posicion(f, c);
            }
            else {
                cout << "Error: Las posiciones deben estar entre 1 y 8.\n";
            }
        }
        else {
            cout << "Error: Ingrese solo numeros enteros.\n";
            limpiarBuffer();
        }
    }
}

// Función para verificar si una posición está bajo ataque de una torre
bool estaAtacadaPorTorre(const Posicion& pos, const Posicion& torre) {
    // Una torre ataca en la misma fila o columna
    return (pos.fila == torre.fila || pos.columna == torre.columna);
}

// Función para verificar si una posición está bajo ataque de cualquier torre
bool estaAtacada(const Posicion& pos) {
    return estaAtacadaPorTorre(pos, torre1) || estaAtacadaPorTorre(pos, torre2);
}

// Función para verificar si una posición está dentro del tablero
bool dentroDelTablero(int fila, int columna) {
    return fila >= 1 && fila <= 8 && columna >= 1 && columna <= 8;
}

// Función para inicializar el tablero siguiendo el enfoque del profesor
void inicializarTablero() {
    // Limpiar tablero
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = ' ';
        }
    }

    // Colocar piezas (usando índices basados en 1)
    tablero[reina.fila - 1][reina.columna - 1] = 'R';
    tablero[t[0][0] - 1][t[0][1] - 1] = 'T';  // Torre 1
    tablero[t[1][0] - 1][t[1][1] - 1] = 'T';  // Torre 2
}

// Función para generar movimientos de la reina
void generarMovimientos() {
    // Direcciones: horizontal, vertical y diagonal
    int direcciones[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Arriba-izq, arriba, arriba-der
        { 0, -1},          { 0, 1},  // Izquierda, derecha
        { 1, -1}, { 1, 0}, { 1, 1}   // Abajo-izq, abajo, abajo-der
    };

    // Para cada dirección
    for (int d = 0; d < 8; d++) {
        int df = direcciones[d][0];
        int dc = direcciones[d][1];

        // Moverse en esa dirección hasta encontrar límite
        int nuevaFila = reina.fila + df;
        int nuevaColumna = reina.columna + dc;

        while (dentroDelTablero(nuevaFila, nuevaColumna)) {
            // Si hay una torre en esta posición, parar
            if ((nuevaFila == torre1.fila && nuevaColumna == torre1.columna) ||
                (nuevaFila == torre2.fila && nuevaColumna == torre2.columna)) {
                break;
            }

            // Determinar si el movimiento es seguro o peligroso
            Posicion nuevaPos(nuevaFila, nuevaColumna);
            if (estaAtacada(nuevaPos)) {
                tablero[nuevaFila - 1][nuevaColumna - 1] = 'X';
            }
            else {
                tablero[nuevaFila - 1][nuevaColumna - 1] = 'V';
            }

            // Continuar en la misma dirección
            nuevaFila += df;
            nuevaColumna += dc;
        }
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

// Función para solicitar datos de entrada
void solicitarDatos() {
    cout << "=== CONFIGURACIÓN DEL JUEGO ===\n";

    while (true) {
        reina = solicitarPosicion("la Reina");
        torre1 = solicitarPosicion("la Torre 1");
        torre2 = solicitarPosicion("la Torre 2");

        if (posicionesValidas(reina, torre1, torre2)) {
            break;
        }
        else {
            cout << "Error: Las posiciones no pueden coincidir. Intente de nuevo.\n\n";
        }
    }
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
        opcion = leerOpcionMenu();

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
                cout << "\nERROR: Debe configurar el juego primero (opcion 1).\n";
            }
            else {
                mostrarTablero();
            }
            break;
        }

        case 3: {
            cout << "\n¡Gracias por jugar!\n";
            return 0;
        }
        }
    }

    return 0;
}