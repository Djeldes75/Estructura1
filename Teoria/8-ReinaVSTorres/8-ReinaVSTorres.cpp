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

char tablero[8][8];
int t[2][2]; // t[0] = torre1 {fila, columna}, t[1] = torre2 {fila, columna}
int limiFx = 1, limiCx = 8, limiFy = 1, limiCy = 8;
int reina_x, reina_y;

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

bool validarRango(int valor) {
    return valor >= 1 && valor <= 8;
}

int leerCoordenada(const char* mensaje) {

    int coordenada;
    bool coordenadaValida = false;

    while (!coordenadaValida) {
        coordenada = validarEntero(mensaje);
        if (validarRango(coordenada)) {
            coordenadaValida = true;
        }
        else {
            cout << "ERROR: La coordenada debe estar entre 1 y 8. Intente nuevamente: ";
        }
    }

    return coordenada;
}

#pragma endregion 

bool posicionesValidas() {

    // Verificar que la reina no esté en la misma posición que la torre 1
    if (reina_x == t[0][0] && reina_y == t[0][1]) {
        cout << "ERROR: La reina no puede estar en la misma posicion que la Torre 1.\n";
        return false;
    }

    // Verificar que la reina no esté en la misma posición que la torre 2
    if (reina_x == t[1][0] && reina_y == t[1][1]) {
        cout << "ERROR: La reina no puede estar en la misma posicion que la Torre 2.\n";
        return false;
    }

    // Verificar que las torres no estén en la misma posición
    if (t[0][0] == t[1][0] && t[0][1] == t[1][1]) {
        cout << "ERROR: Las torres no pueden estar en la misma posicion.\n";
        return false;
    }

    return true;
}

#pragma region Confirmacion y si no, reintentaaa

bool confirmarConfiguracion() {

    cout << "\n--- CONFIGURACION ACTUAL ---\n";
    cout << "Reina: Fila " << reina_x << ", Columna " << reina_y << "\n";
    cout << "Torre 1: Fila " << t[0][0] << ", Columna " << t[0][1] << "\n";
    cout << "Torre 2: Fila " << t[1][0] << ", Columna " << t[1][1] << "\n";

    char confirmacion;
    bool respuestaValida = false;

    while (!respuestaValida) {
        cout << "Es correcta esta configuracion? (s/n): ";
        cin >> confirmacion;
        cin.ignore(10000, '\n');

        if (confirmacion == 's' || confirmacion == 'S') {
            return true;
        }
        else if (confirmacion == 'n' || confirmacion == 'N') {
            return false;
        }
        else {
            cout << "ERROR: Responda con 's' para Si o 'n' para No.\n";
        }
    }

    return false;
}

#pragma endregion

#pragma region Funciones del Juego

// Función recursiva para generar movimientos en una dirección específica
void Movimiento(int x, int y, int dir_x, int dir_y) {
    int mx = x + dir_x;
    int my = y + dir_y;

    // Verificar límites del tablero
    if (mx < limiFx || mx > limiCx || my < limiFy || my > limiCy) {
        return;
    }

    // Verificar si hay una torre en esta posición (bloquea el movimiento)
    if ((mx == t[0][0] && my == t[0][1]) || (mx == t[1][0] && my == t[1][1])) {
        return;
    }

    bool bajo_ataque = false;

    // Torre 1: ataca si comparte fila O columna
    if (mx == t[0][0] || my == t[0][1]) {
        bajo_ataque = true;
    }
    \
    // Torre 2: ataca si comparte fila O columna
    if (mx == t[1][0] || my == t[1][1]) {
        bajo_ataque = true;
    }

    // Establecer la jugada en el tablero
    if (bajo_ataque) {
        tablero[mx - 1][my - 1] = 'X';
    }
    else {
        tablero[mx - 1][my - 1] = 'V';
    }

    Movimiento(mx, my, dir_x, dir_y);
}

void inicializarTablero() {

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

    for (int i = 0; i < 8; i++) {
        Movimiento(reina_x, reina_y, direcciones[i][0], direcciones[i][1]);
    }
}

#pragma region Visualizacion

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

void solicitarDatos() {

    cout << "=== CONFIGURACION DEL JUEGO ===\n";

    bool configuracionValida = false;

    while (!configuracionValida) {
        cout << "\n--- Posicion de la Reina ---\n";
        reina_x = leerCoordenada("Ingrese la fila de la Reina (1-8): ");
        reina_y = leerCoordenada("Ingrese la columna de la Reina (1-8): ");

        cout << "\n--- Posicion de la Torre 1 ---\n";
        t[0][0] = leerCoordenada("Ingrese la fila de la Torre 1 (1-8): ");
        t[0][1] = leerCoordenada("Ingrese la columna de la Torre 1 (1-8): ");

        cout << "\n--- Posicion de la Torre 2 ---\n";
        t[1][0] = leerCoordenada("Ingrese la fila de la Torre 2 (1-8): ");
        t[1][1] = leerCoordenada("Ingrese la columna de la Torre 2 (1-8): ");

        if (posicionesValidas()) {

            if (confirmarConfiguracion()) {

                configuracionValida = true;
                cout << "\nConfiguracion guardada exitosamente.\n";
            }
            else {
                cout << "\nReiniciando configuracion...\n";
            }
        }
        else {
            cout << "\nError en la configuracion. Intente nuevamente.\n";
        }
    }
}

#pragma endregion

#pragma region Utilidades

void pausa() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

void mostrarLinea(int longitud, char caracter) {
    for (int i = 0; i < longitud; i++) {
        cout << caracter;
    }
    cout << "\n";
}

void mostrarEstadisticas() {

    int movimientosValidos = 0;
    int movimientosPeligrosos = 0;

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            if (tablero[i][j] == 'V') {
                movimientosValidos++;
            }
            else if (tablero[i][j] == 'X') {
                movimientosPeligrosos++;
            }
        }
    }

    cout << "\n--- ESTADISTICAS ---\n";
    cout << "Movimientos seguros disponibles: " << movimientosValidos << "\n";
    cout << "Movimientos peligrosos: " << movimientosPeligrosos << "\n";
    cout << "Total de movimientos posibles: " << (movimientosValidos + movimientosPeligrosos) << "\n";

    if (movimientosValidos == 0) {
        cout << "ADVERTENCIA: La reina no tiene movimientos seguros!\n";
    }

    pausa();
}

#pragma endregion

#pragma region Menu

void mostrarMenu() {

    mostrarLinea(45, '=');
    cout << "          REINA VS TORRES ENEMIGAS\n";
    mostrarLinea(45, '=');
    cout << "1. Jugar (configurar nuevas posiciones)\n";
    cout << "2. Mostrar tablero y estadisticas\n";
    cout << "3. Salir\n";
    mostrarLinea(45, '=');
    cout << "Seleccione una opcion: ";
}

#pragma endregion

#pragma region Main

int main() {

    int opcion;
    bool primerJuego = true;

    while (true) {

        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {

        case 1: {

            try {
                solicitarDatos();
                inicializarTablero();
                generarMovimientos();
                mostrarTablero();
                mostrarEstadisticas();
                primerJuego = false;
            }
            catch (const exception& e) {
                cout << "ERROR: Ocurrio un problema durante la configuracion.\n";
                cout << "Intente nuevamente.\n";
            }
            break;
        }

        case 2: {
            if (primerJuego) {
                cout << "\nERROR: Debe configurar el juego primero (opcion 1).\n";
                pausa();
            }
            else {
                mostrarTablero();
                mostrarEstadisticas();
            }
            break;
        }

        case 3: {
            cout << "\nGracias por jugar Reina vs Torres Enemigas!\n";
            return 0;
        }

        default: {
            cout << "ERROR: Esta opcion no deberia ser alcanzable.\n";
            break;
        }
        }
    }

    return 0;
}

#pragma endregion