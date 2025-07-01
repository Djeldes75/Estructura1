/*
-------------------------------------------------------------------------------------------------------
Tarea: #7 - Las Torres de Hanoi
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Realizar un programa C++ que permita resolver el problema de las Torres de Hanoi, el cual
consiste en trasladar una cantidad x de anillos desde una torre A a una torre B.

RESTRICCIONES:
    A. El juego tiene 3 torres, nombradas A, B y C y n anillos concentricos ordenados de mayor
    diametro a menos diametro.
    B. Al iniciar se tiene un conjunto de al menos 3 anillos colocados en forma descendente,
    pues cada anillo esta a su vez encima de otro mas grande.
    C. Nunca un anillo mas grande debe estar encima de uno mas pequeno, es decir, de mayor
    diametro va encima de otro con diametro menor.
    D. Debe realizar los movimientos de los anillos hasta que haya traslado los anillos de una
    torre X a una torre Y.

La salida del programa debe indicar el movimiento de los anillos en cada etapa, es decir, debe
indicar que anillo va a moverse a que torre, hasta completar el traslado de una torre a otra.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha de entrega: 1/7/2025
*/

#include <iostream>

using namespace std;

// Estructura que representa una torre como pila
struct Torre {
    int* discos;        // Array dinamico para almacenar los discos
    int tope;          // Indice del disco superior (-1 si esta vacia)
    int capacidad;     // Capacidad maxima de la torre
};

// Variables globales del juego
Torre torres[3];        // Array de 3 torres: A=0, B=1, C=2
long long movimientos = 0;  // Contador de movimientos realizados
bool mostrarPasos = true;   // Flag para mostrar o no los pasos

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
                cin.ignore(10000, '\n');  // Limpiar buffer
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
        if (opcion >= 1 && opcion <= 4) {
            opcionValida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Seleccione una opcion valida (1-4): ";
        }
    }

    return opcion;
}

int leerNumeroDiscos() {

    int discos;
    bool numeroValido = false;

    while (!numeroValido) {

        discos = validarEntero("Ingrese numero de discos (minimo 3): ");

        if (discos < 3) {
            cout << "ERROR: Debe ingresar al menos 3 discos segun las reglas.\n";
        }
        else if (discos > 20) {

            cout << "ADVERTENCIA: Mas de 20 discos tomara mucho tiempo (2^" << discos << "-1 movimientos).\n";
            char confirmar;
            cout << "Desea continuar? (s/n): ";
            cin >> confirmar;
            cin.ignore(10000, '\n');

            if (confirmar == 's' || confirmar == 'S') {
                numeroValido = true;
            }
        }
        else {
            numeroValido = true;
        }
    }

    return discos;
}

char leerTorre(const char* mensaje) {

    char letra;
    bool torreValida = false;

    while (!torreValida) {
        cout << mensaje;
        cin >> letra;
        cin.ignore(10000, '\n');

        if (letra >= 'a' && letra <= 'z') {
            letra = letra - 'a' + 'A';
        }

        if (letra == 'A' || letra == 'B' || letra == 'C') {
            torreValida = true;
        }
        else {
            cout << "ERROR: Ingrese una torre valida (A, B o C): ";
        }
    }

    return letra;
}

#pragma endregion

#pragma region Gestion de Torres

void crearTorre(Torre* torre, int capacidadMax) {

    torre->discos = new int[capacidadMax];
    torre->tope = -1;
    torre->capacidad = capacidadMax;

    // Inicializar el array con ceros para mayor seguridad
    for (int i = 0; i < capacidadMax; i++) {
        torre->discos[i] = 0;
    }
}

bool torreVacia(Torre* torre) {
    return torre->tope == -1;
}

bool torreLlena(Torre* torre) {
    return torre->tope == torre->capacidad - 1;
}

int verTope(Torre* torre) {

    if (torreVacia(torre)) {
        return -1;
    }
    return torre->discos[torre->tope];
}

bool puedeApilar(Torre* torre, int disco) {

    if (torreLlena(torre)) {
        return false;
    }
    if (torreVacia(torre)) {
        return true;
    }
    return disco < verTope(torre);
}

bool apilar(Torre* torre, int disco) {

    if (!puedeApilar(torre, disco)) {
        return false;
    }
    torre->tope++;
    torre->discos[torre->tope] = disco;
    return true;
}

int desapilar(Torre* torre) {

    if (torreVacia(torre)) {
        return -1;
    }
    int disco = torre->discos[torre->tope];
    torre->tope--;
    return disco;
}

void limpiarTorre(Torre* torre) {

    torre->tope = -1;
    for (int i = 0; i < torre->capacidad; i++) {
        torre->discos[i] = 0;
    }
}

void liberarTorre(Torre* torre) {

    if (torre->discos != nullptr) {
        delete[] torre->discos;
        torre->discos = nullptr;
    }
    torre->tope = -1;
    torre->capacidad = 0;
}

#pragma endregion

#pragma region Utilidades de Conversion

int torreAIndice(char letra) {
    switch (letra) {
    case 'A': case 'a': return 0;
    case 'B': case 'b': return 1;
    case 'C': case 'c': return 2;
    default: return -1;
    }
}

char indiceATorre(int indice) {
    switch (indice) {
    case 0: return 'A';
    case 1: return 'B';
    case 2: return 'C';
    default: return '?';
    }
}

#pragma endregion

#pragma region Utilidad

long long calcularMovimientos(int n) {

    if (n <= 0) return 0;
    long long resultado = 1;

    for (int i = 0; i < n; i++) {
        resultado = resultado * 2;
    }
    return resultado - 1;
}

int contarDiscos(Torre* torre) {
    return torre->tope + 1;
}

void pausa() {
    cout << "\nPresione Enter para continuar.";
    cin.get();
}

void pausaCorta() {

    cout.flush();
    for (int i = 0; i < 600000000; i++) {
    }
}

void mostrarLinea(int longitud, char caracter) {
    for (int i = 0; i < longitud; i++) {
        cout << caracter;
    }
    cout << "\n";
}

#pragma endregion

#pragma region Visualizacion

void mostrarTorres() {

    if (!mostrarPasos) return;

    // Calcular la altura maxima entre todas las torres
    int alturaMax = 0;

    for (int i = 0; i < 3; i++) {

        int discos = contarDiscos(&torres[i]);
        if (discos > alturaMax) {
            alturaMax = discos;
        }
    }

    cout << "\nEstado actual de las torres:\n\n";

    // Mostrar las torres nivel por nivel, de arriba hacia abajo
    for (int nivel = alturaMax - 1; nivel >= 0; nivel--) {

        cout << "  ";

        for (int t = 0; t < 3; t++) {

            if (nivel < contarDiscos(&torres[t])) {
                // Hay un disco en este nivel
                int disco = torres[t].discos[nivel];
                cout << "[" << disco << "]";
                if (disco < 10) cout << " ";  // Alineacion para numeros de 1 digito
            }
            else {
                cout << " |  ";
            }
            cout << "   ";
        }
        cout << "\n";
    }

    // Mostrar las bases y etiquetas de las torres
    cout << "  ---   ---   ---\n";
    cout << "   A     B     C\n";
    cout << "----------------------------------------\n";
    cout << "Movimientos realizados: " << movimientos << "\n";
}

#pragma endregion

#pragma region Resolver las Torres

void resolverHanoi(int n, int origen, int destino, int auxiliar) {

    if (n == 1) {
        // Caso base: mover un solo disco
        int disco = desapilar(&torres[origen]);
        if (disco == -1) {
            cout << "ERROR: No se pudo obtener disco de la torre " << indiceATorre(origen) << "\n";
            return;
        }

        if (!apilar(&torres[destino], disco)) {
            cout << "ERROR: No se pudo colocar disco " << disco << " en torre " << indiceATorre(destino) << "\n";
            // Restaurar el disco a la torre original
            apilar(&torres[origen], disco);
            return;
        }

        movimientos++;

        if (mostrarPasos) {
            cout << "\nMovimiento " << movimientos << ": ";
            cout << "Mover disco " << disco << " de Torre " << indiceATorre(origen);
            cout << " a Torre " << indiceATorre(destino) << "\n";
            mostrarTorres();

            // Pausa visual mas eficiente
            pausaCorta();
        }
    }
    else {
        // Caso recursivo: dividir el problema en 3 pasos

        // Paso 1: Mover n-1 discos de origen a auxiliar
        resolverHanoi(n - 1, origen, auxiliar, destino);

        // Paso 2: Mover el disco mas grande de origen a destino
        resolverHanoi(1, origen, destino, auxiliar);

        // Paso 3: Mover n-1 discos de auxiliar a destino
        resolverHanoi(n - 1, auxiliar, destino, origen);
    }
}

#pragma endregion

#pragma region Funciones de Juego

void inicializarJuego(int numDiscos) {

    for (int i = 0; i < 3; i++) {
        limpiarTorre(&torres[i]);
    }

    // Colocar discos en Torre A (grande abajo, pequeno arriba)
    for (int disco = numDiscos; disco >= 1; disco--) {
        if (!apilar(&torres[0], disco)) {
            cout << "ERROR: No se pudo inicializar correctamente el juego.\n";
            return;
        }
    }

    // Reiniciar contador de movimientos
    movimientos = 0;
    mostrarPasos = true;

    cout << "\nJuego iniciado con " << numDiscos << " discos en Torre A\n";
    cout << "Movimientos minimos necesarios: " << calcularMovimientos(numDiscos) << "\n";

    mostrarTorres();
}

void jugar() {

    // Verificar que hay discos para jugar
    bool hayDiscos = false;

    for (int i = 0; i < 3; i++) {
        if (!torreVacia(&torres[i])) {
            hayDiscos = true;
            break;
        }
    }

    if (!hayDiscos) {
        cout << "ERROR: No hay discos en el juego.\n";
        cout << "Debe inicializar el juego primero (Opcion 1).\n\n";
        return;
    }

    // Solicitar torres de origen y destino
    char origenChar = leerTorre("Torre origen (A/B/C): ");
    char destinoChar = leerTorre("Torre destino (A/B/C): ");

    // Validar que las torres sean diferentes
    if (origenChar == destinoChar) {
        cout << "ERROR: La torre origen y destino deben ser diferentes.\n\n";
        return;
    }

    int origen = torreAIndice(origenChar);
    int destino = torreAIndice(destinoChar);

    // Validar que la torre origen tenga discos
    if (torreVacia(&torres[origen])) {
        cout << "ERROR: La torre origen (" << origenChar << ") esta vacia.\n\n";
        return;
    }

    // Calcular la torre auxiliar (la tercera torre)
    int auxiliar = 3 - origen - destino;

    int numDiscos = contarDiscos(&torres[origen]);

    cout << "\n--- COMENZANDO RESOLUCION ---\n";
    cout << "Moviendo " << numDiscos << " discos de Torre " << origenChar;
    cout << " a Torre " << destinoChar << "\n";
    cout << "Torre auxiliar: " << indiceATorre(auxiliar) << "\n";
    cout << "Movimientos minimos esperados: " << calcularMovimientos(numDiscos) << "\n";

    pausa();

    // Ejecutar el algoritmo
    long long movimientosAnteriores = movimientos;
    resolverHanoi(numDiscos, origen, destino, auxiliar);

    // Mostrar resultados
    cout << "\n** RESOLUCION COMPLETADA **\n";
    cout << "Movimientos realizados: " << (movimientos - movimientosAnteriores) << "\n";
    cout << "Movimientos minimos posibles: " << calcularMovimientos(numDiscos) << "\n";

    if ((movimientos - movimientosAnteriores) == calcularMovimientos(numDiscos)) {
        cout << "PERFECTO! Resuelto con el numero minimo de movimientos.\n";
    }

    pausa();
}

void mostrarEstado() {

    cout << "\n--- ESTADO ACTUAL DEL JUEGO ---\n";

    // Mostrar informacion detallada de cada torre
    for (int i = 0; i < 3; i++) {
        cout << "Torre " << indiceATorre(i) << ": ";
        if (torreVacia(&torres[i])) {
            cout << "(vacia)";
        }
        else {
            cout << contarDiscos(&torres[i]) << " discos [";
            // Mostrar discos de abajo hacia arriba
            for (int j = 0; j <= torres[i].tope; j++) {
                cout << torres[i].discos[j];
                if (j < torres[i].tope) cout << ", ";
            }
            cout << "]";
        }
        cout << "\n";
    }

    cout << "Total de movimientos realizados: " << movimientos << "\n";

    // Mostrar representacion visual
    mostrarTorres();
    pausa();
}

#pragma endregion

#pragma region Menu

void mostrarMenu() {
    mostrarLinea(50, '=');
    cout << "                TORRES DE HANOI\n";
    mostrarLinea(50, '=');
    cout << "1. Inicializar juego (colocar discos)\n";
    cout << "2. Mostrar estado actual\n";
    cout << "3. Resolver\n";
    cout << "4. Salir\n";
    mostrarLinea(50, '=');
    cout << "Seleccione una opcion: ";
}

#pragma endregion

#pragma region Main 

int main() {

    // Crear las tres torres con capacidad suficiente
    for (int i = 0; i < 3; i++) {
        crearTorre(&torres[i], 63);  //capacidad de los disc0s
    }

    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {
        case 1: {
            cout << "\n--- INICIALIZAR JUEGO ---\n";
            int discos = leerNumeroDiscos();
            inicializarJuego(discos);
            break;
        }
        case 2:
            mostrarEstado();
            break;
        case 3:
            cout << "\n--- RESOLVER TORRES DE HANOI ---\n";
            jugar();
            break;
        case 4:
            cout << "\nGracias por jugar Torres de Hanoi!\n";
            cout << "Programa desarrollado por el Grupo 6.\n";
            break;
        }

    } while (opcion != 4);

    // Liberar memoria de las torres
    for (int i = 0; i < 3; i++) {
        liberarTorre(&torres[i]);
    }

    return 0;
}

#pragma endregion