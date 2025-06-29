/*
-------------------------------------------------------------------------------------------------------
Tarea: #7 - Las Torres de Hanoi
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Las Torres de Hanoi es un rompecabezas que consiste en tres torres (A, B, C) y n discos de
diferentes tamaños. El objetivo es trasladar todos los discos de una torre a otra, siguiendo
las reglas establecidas.

REGLAS:
1. Solo se puede mover un disco a la vez
2. Solo se puede tomar el disco superior de cada torre
3. Un disco grande NUNCA puede estar sobre uno pequeño

RESTRICCIONES:
    A. El juego tiene 3 torres, nombradas A, B y C y n anillos concéntricos
    B. Al iniciar se tiene un conjunto de al menos 3 anillos en orden descendente
    C. Nunca un anillo más grande debe estar encima de uno más pequeño
    D. Debe mostrar cada movimiento hasta completar el traslado

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 19/Dic/2022
*/

#include <iostream>


using namespace std;

struct Pila {
    int* datos;
    int tope;
    int capacidad;
};

// Variables globales para el control del juego
int numeroMovimientos = 0;

Pila torres[3]; // Torres A=0, B=1, C=2

const int MAX_DISCOS = 20;

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
                cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return valor;
}

int validarNumeroDiscos() {

    int numDiscos;
    bool numeroValido = false;

    while (!numeroValido) {
        numDiscos = validarEntero("Ingrese el numero de discos (minimo 3, maximo 15): ");
        if (numDiscos >= 3 && numDiscos <= 15) {
            numeroValido = true;
        }
        else {
            cout << "ERROR: Debe ingresar entre 3 y 15 discos.\n";
        }
    }

    return numDiscos;
}

int validarOpcionMenu() {

    int opcion;
    bool opcionValida = false;

    while (!opcionValida) {

        opcion = validarEntero("");

        if (opcion >= 1 && opcion <= 4) {
            opcionValida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Intente nuevamente (1-4): ";
        }
    }

    return opcion;
}

char validarTorre(const char* mensaje) {

    char torre;
    bool torreValida = false;

    cout << mensaje;

    while (!torreValida) {
        cin >> torre;
        cin.ignore(10000, '\n');

        if (torre >= 'a' && torre <= 'z') {
            torre = torre - 'a' + 'A';
        }

        if (torre == 'A' || torre == 'B' || torre == 'C') {
            torreValida = true;
        }
        else {
            cout << "ERROR: Torre invalida. Ingrese A, B o C: ";
        }
    }

    return torre;
}

#pragma endregion

#pragma region Funciones de Pila

// Inicializar una pila
void inicializarPila(Pila* pila) {
    pila->datos = new int[MAX_DISCOS];
    pila->tope = -1;
    pila->capacidad = MAX_DISCOS;
}

// Verificar si la pila está vacía
bool pilaVacia(Pila* pila) {
    return pila->tope == -1;
}

// Verificar si la pila está llena
bool pilaLlena(Pila* pila) {
    return pila->tope >= pila->capacidad - 1;
}

// Obtener el tamaño de la pila
int tamanioPila(Pila* pila) {
    return pila->tope + 1;
}

// Agregar elemento a la pila (push)
void apilar(Pila* pila, int valor) {
    if (!pilaLlena(pila)) {
        pila->tope++;
        pila->datos[pila->tope] = valor;
    }
}

// Quitar elemento de la pila (pop)
int desapilar(Pila* pila) {

    if (!pilaVacia(pila)) {
        int valor = pila->datos[pila->tope];
        pila->tope--;
        return valor;
    }
    return -1; // Error: pila vacía
}

// Ver el elemento superior sin quitarlo (top)
int verTope(Pila* pila) {
    if (!pilaVacia(pila)) {
        return pila->datos[pila->tope];
    }
    return -1; // Error: pila vacía
}

// Limpiar la pila
void limpiarPila(Pila* pila) {
    pila->tope = -1;
}

// Liberar memoria de la pila
void liberarPila(Pila* pila) {
    delete[] pila->datos;
    pila->datos = nullptr;
    pila->tope = -1;
    pila->capacidad = 0;
}

#pragma endregion

#pragma region Funciones Auxiliares

// Convertir letra de torre a índice numérico
int torreAIndice(char torre) {
    switch (torre) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    default: return -1;
    }
}

// Convertir índice numérico a letra de torre
char indiceATorre(int indice) {
    switch (indice) {
    case 0: return 'A';
    case 1: return 'B';
    case 2: return 'C';
    default: return '?';
    }
}

// Calcular el número mínimo de movimientos para n discos (2^n - 1)
int calcularMovimientosMinimos(int numDiscos) {

    int resultado = 1;

    for (int i = 0; i < numDiscos; i++) {
        resultado *= 2;
    }
    return resultado - 1;
}

// Limpiar todas las torres
void limpiarTorres() {
    for (int i = 0; i < 3; i++) {
        limpiarPila(&torres[i]);
    }
    numeroMovimientos = 0;
}

// Inicializar las torres con n discos en la torre A
void inicializarTorres(int numDiscos) {

    limpiarTorres();

    // Colocar los discos en la torre A (del más grande al más pequeño)
    for (int i = numDiscos; i >= 1; i--) {
        apilar(&torres[0], i);
    }

    cout << "\nTorres inicializadas con " << numDiscos << " discos en la Torre A.\n";
    cout << "Movimientos minimos necesarios: " << calcularMovimientosMinimos(numDiscos) << "\n\n";
}

// Pausar ejecución
void pausar() {
    cout << "Presione ENTER para continuar...";
    cin.get();
}

#pragma endregion

#pragma region Visualización

// Mostrar el estado actual de las torres
void mostrarEstadoTorres() {
    cout << "\n===============================================\n";
    cout << "            ESTADO ACTUAL DE LAS TORRES\n";
    cout << "===============================================\n";

    // Encontrar la altura máxima para la visualización
    int alturaMaxima = 0;
    for (int i = 0; i < 3; i++) {
        if (tamanioPila(&torres[i]) > alturaMaxima) {
            alturaMaxima = tamanioPila(&torres[i]);
        }
    }

    // Crear arrays temporales para mostrar las torres invertidas
    int torresTemp[3][MAX_DISCOS];
    int alturasTemp[3] = { 0, 0, 0 };

    // Copiar datos de las pilas a arrays temporales (invertido)
    for (int torre = 0; torre < 3; torre++) {
        for (int i = 0; i <= torres[torre].tope; i++) {
            torresTemp[torre][i] = torres[torre].datos[i];
            alturasTemp[torre]++;
        }
    }

    // Mostrar las torres nivel por nivel (de arriba hacia abajo)
    for (int nivel = alturaMaxima - 1; nivel >= 0; nivel--) {
        cout << "  ";
        for (int torre = 0; torre < 3; torre++) {
            if (nivel < alturasTemp[torre]) {
                cout << "[" << torresTemp[torre][nivel] << "]";
                if (torresTemp[torre][nivel] < 10) cout << " "; // Alineación
            }
            else {
                cout << " |  ";
            }
            cout << "   ";
        }
        cout << "\n";
    }

    // Mostrar las bases de las torres
    cout << "  ---   ---   ---\n";
    cout << "   A     B     C  \n";
    cout << "===============================================\n";
    cout << "Movimientos realizados: " << numeroMovimientos << "\n\n";
}//FIN

#pragma endregion

#pragma region Algoritmo Torres de Hanoi

// Función recursiva para resolver las Torres de Hanoi
void resolverHanoi(int numDiscos, int origen, int destino, int auxiliar) {
    if (numDiscos == 1) {
        // Caso base: mover un solo disco
        int disco = desapilar(&torres[origen]);
        apilar(&torres[destino], disco);
        numeroMovimientos++;

        cout << "Movimiento " << numeroMovimientos << ": ";
        cout << "Mover disco " << disco << " de Torre " << indiceATorre(origen);
        cout << " a Torre " << indiceATorre(destino) << "\n";

        mostrarEstadoTorres();

        // Simular espera sin usar thread o chrono
        for (volatile long long i = 0; i < 500000000; i++);

    }
    else {
        // Paso 1: Mover n-1 discos de origen a auxiliar
        resolverHanoi(numDiscos - 1, origen, auxiliar, destino);

        // Paso 2: Mover el disco más grande de origen a destino
        resolverHanoi(1, origen, destino, auxiliar);

        // Paso 3: Mover n-1 discos de auxiliar a destino
        resolverHanoi(numDiscos - 1, auxiliar, destino, origen);
    }
}

// Resolver Torres de Hanoi con configuración personalizada
void resolverHanoiPersonalizado() {
    if (pilaVacia(&torres[0]) && pilaVacia(&torres[1]) && pilaVacia(&torres[2])) {
        cout << "ERROR: No hay discos en las torres. Inicialice primero.\n\n";
        return;
    }

    char torreOrigen = validarTorre("Ingrese la torre de origen (A, B, C): ");
    char torreDestino = validarTorre("Ingrese la torre de destino (A, B, C): ");

    if (torreOrigen == torreDestino) {
        cout << "ERROR: La torre de origen y destino no pueden ser la misma.\n\n";
        return;
    }

    int indiceOrigen = torreAIndice(torreOrigen);
    int indiceDestino = torreAIndice(torreDestino);

    if (pilaVacia(&torres[indiceOrigen])) {
        cout << "ERROR: La torre de origen esta vacia.\n\n";
        return;
    }

    // Determinar la torre auxiliar
    int indiceAuxiliar = 3 - indiceOrigen - indiceDestino; // 0+1+2=3

    int numDiscos = tamanioPila(&torres[indiceOrigen]);

    cout << "\n=== RESOLVIENDO TORRES DE HANOI ===\n";
    cout << "Discos a mover: " << numDiscos << "\n";
    cout << "Desde Torre " << torreOrigen << " hacia Torre " << torreDestino << "\n";
    cout << "Torre auxiliar: " << indiceATorre(indiceAuxiliar) << "\n";
    cout << "Movimientos necesarios: " << calcularMovimientosMinimos(numDiscos) << "\n\n";

    cout << "Presione ENTER para comenzar...";
    cin.get();

    numeroMovimientos = 0;
    resolverHanoi(numDiscos, indiceOrigen, indiceDestino, indiceAuxiliar);

    cout << "\nTORRES DE HANOI RESUELTAS EXITOSAMENTE!\n";
    cout << "Total de movimientos realizados: " << numeroMovimientos << "\n\n";
}

#pragma endregion

#pragma region Menú

void mostrarMenu() {
    cout << "================================================\n";
    cout << "              TORRES DE HANOI\n";
    cout << "================================================\n";
    cout << "1. Inicializar torres con n discos\n";
    cout << "2. Mostrar estado actual de las torres\n";
    cout << "3. Resolver Torres de Hanoi\n";
    cout << "4. Salir\n";
    cout << "================================================\n";
    cout << "Seleccione una opcion: ";
}//FIN

#pragma endregion

#pragma region Main

int main() {

    // Inicializar las pilas de las torres
    for (int i = 0; i < 3; i++) {
        inicializarPila(&torres[i]);
    }

    int opcion;

    do {
        mostrarMenu();
        opcion = validarOpcionMenu();

        switch (opcion) {

        case 1: {

            cout << "\n--- INICIALIZAR TORRES ---\n";
            int numDiscos = validarNumeroDiscos();
            inicializarTorres(numDiscos);
            mostrarEstadoTorres();
            break;
        }

        case 2:
            mostrarEstadoTorres();
            break;

        case 3:
            cout << "\n--- RESOLVER TORRES DE HANOI ---\n";
            resolverHanoiPersonalizado();
            break;

        case 4:
            limpiarTorres();

            for (int i = 0; i < 3; i++) {
                liberarPila(&torres[i]);
            }
            cout << "\nGracias por usar el programa Torres de Hanoi.\n";
            cout << "¡Hasta luego!\n";
            break;
        }

    } while (opcion != 4);

    return 0;
}

#pragma endregion