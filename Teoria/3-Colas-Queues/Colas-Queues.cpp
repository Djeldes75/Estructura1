/*
-------------------------------------------------------------------------------------------------------
Tarea: #4 - Colas (Queues)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------------------------
Una Cola (Queue) es una estructura de datos en donde el primero en entrar es el primero en salir. Para
nuestro caso, haremos el problema un poco mas complejo añadiéndole lo que se conoce como
prioridad. En los casos en que una Cola tiene prioridad se considera esta al momento de insertar un
nuevo nodo a la estructura. La Cola tiene la siguiente forma para los nodos:

struct Queue {
 int dato;
 Queue *next;
};

RESTRICCIONES:
    A. La Cola debe poder realizar las operaciones Enqueue y Dequeue.

    B. Las prioridades van de 0 a 16. En los casos que el usuario decida una prioridad más alta que 16 se
    considerara la default, y se insertara el nuevo nodo al final de la estructura.

    C. El programa deberá tener un menu con las opciones para Enqueue y Dequeue, además de poder
    desplegar todos los elementos de la cola, provocando Dequeue de toda la estructura Cola.

    D. Las entradas de datos del usuario deben ser debidamente validas.

    E. El programa debe ser lo suficientemente especializado para informar al usuario cuando la cola esta
    vacía.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 31/May/2025

*/

#include <iostream>

using namespace std;

struct Queue {
    int dato;
    Queue* next;
};

// Array de 17 punteros a Queue que representa las colas de diferentes prioridades.
Queue* colas[17];

#pragma region Validaciones

//Validacion Universal para Enteros
int validarEntero(const char* mensaje) {

    int enteroValido;
    char siguienteChar;

    cout << mensaje;

    while (true) {

        if (cin >> enteroValido) {

            // Verificar que despues del numero no haya otros caracteres (excepto espacios y salto de linea)
            siguienteChar = cin.peek();

            if (siguienteChar == '\n' || siguienteChar == ' ' || siguienteChar == EOF) {

                while (cin.get() != '\n');
                return enteroValido;
            }
            else {
                //Invalido
                cout << "ERROR: Entrada invalida.\n";
                cin.clear();

                while (cin.get() != '\n');
                cout << "\nIntente nuevamente: ";
            }
        }
        else {
            cout << "ERROR: Entrada invalida.\n";
            cin.clear();
            // Limpiar el buffer - version simple
            while (cin.get() != '\n');
            cout << "\nIntente nuevamente: ";
        }
    }
}

//Validar Opcion del Menu
int leerOpcionMenu() {
    int opcion;
    opcion = validarEntero("");

    while (opcion < 1 || opcion > 5) {
        cout << "ERROR: Opcion invalida. Opciones: 1-5. \nIntente nuevamente: ";
        opcion = validarEntero("");
    }

    return opcion;
}

//Validar Prioridad
int leerPrioridad() {

    int prioridad = validarEntero("Ingrese la prioridad (0-16): ");

    if (prioridad > 16 || prioridad < 0) {
        cout << "Prioridad fuera de rango. Usando prioridad por defecto (16).\n";
        return 16;
    }

    return prioridad;
}

//Validar Dato
int leerDato() {
    return validarEntero("Ingrese un numero: ");
}

#pragma endregion

#pragma region Funciones Auxiliares

//Inicializar Array de Colas
void inicializar() {
    for (int i = 0; i < 17; i++) {
        colas[i] = nullptr;
    }
}

//Verificar si Todas las Colas Estan Vacias
bool estaVacia() {

    for (int i = 0; i < 17; i++) {
        if (colas[i] != nullptr) return false;
    }
    return true;
}

#pragma endregion

#pragma region Enqueue y Dequeue

//Insertar Elemento en Cola con Prioridad
void enqueue() {
    Queue* nuevo = new Queue;

    nuevo->dato = leerDato();

    int prioridad = leerPrioridad();

    nuevo->next = nullptr;

    //Si la cola de esta prioridad esta vacia
    if (colas[prioridad] == nullptr) {

        colas[prioridad] = nuevo;
    }
    else {
        //Buscar el final de la cola para insertar (FIFO)
        Queue* nodoActual = colas[prioridad];

        while (nodoActual->next != nullptr) {

            nodoActual = nodoActual->next;
        }
        nodoActual->next = nuevo;
    }

    cout << "\nIngresado: {Dato: " << nuevo->dato << "} - {Prioridad: " << prioridad << "}\n\n";
}

//Eliminar Elemento de Mayor Prioridad
void dequeue() {

    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }

    //Buscar la primera cola con elementos (indice menor = mayor prioridad)
    for (int i = 0; i < 17; i++) {

        if (colas[i] != nullptr) {

            Queue* nodoAEliminar = colas[i];

            cout << "\nEliminado: " << nodoAEliminar->dato << " (Prioridad " << i << ")\n\n";

            //Actualizar puntero de la cola
            colas[i] = colas[i]->next;

            delete nodoAEliminar;
            return;
        }
    }
}

#pragma endregion

#pragma region Mostrar y Vaciar

//Mostrar Todos los Elementos por Prioridad
void mostrar() {

    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA COLA ===\n";
    int contador = 1;

    //Recorrer todas las colas desde la mayor prioridad (0) hasta la menor (16)
    for (int i = 0; i < 17; i++) {
        Queue* nodoActual = colas[i];

        //Recorrer todos los nodos de esta cola especifica
        while (nodoActual != nullptr) {
            cout << contador << ". Dato: " << nodoActual->dato << " | Prioridad: " << i << "\n";
            nodoActual = nodoActual->next;
            contador++;
        }
    }
    cout << "============================\n\n";
}

//Vaciar Completamente Todas las Colas
void vaciarTodo() {

    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }

    cout << "\n=== VACIANDO COLA COMPLETA ===\n";
    int contador = 1;

    //Eliminar elementos respetando prioridad hasta que todo este vacio
    while (!estaVacia()) {

        //Buscar la primera cola con elementos (mayor prioridad)
        for (int i = 0; i < 17; i++) {

            if (colas[i] != nullptr) {
                cout << contador << ". Eliminando: " << colas[i]->dato << " (Prioridad " << i << ")\n";

                Queue* nodoAEliminar = colas[i];
                colas[i] = colas[i]->next;
                delete nodoAEliminar;

                contador++;
                break;
            }
        }
    }
    cout << "\nCola completamente vacia.\n\n";
}

#pragma endregion

#pragma region Menu

//Mostrar Menu Principal
void mostrarMenu() {
    cout << "=================================\n";
    cout << "       Cola con Prioridad\n";
    cout << "=================================\n";
    cout << "1. Enqueue (Insertar)\n";
    cout << "2. Dequeue (Eliminar)\n";
    cout << "3. Mostrar cola\n";
    cout << "4. Vaciar cola completa\n";
    cout << "5. Salir\n";
    cout << "=================================\n";
    cout << "Opcion: ";
}

#pragma endregion

#pragma region Main

int main() {

    inicializar();
    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {
        case 1:
            cout << "\n--- INSERTAR ELEMENTO ---\n";
            enqueue();
            break;

        case 2:
            cout << "\n--- ELIMINAR ELEMENTO ---\n";
            dequeue();
            break;

        case 3:
            mostrar();
            break;

        case 4:
            vaciarTodo();
            break;

        case 5:

            for (int i = 0; i < 17; i++) {
                while (colas[i] != nullptr) {
                    Queue* nodoAEliminar = colas[i];
                    colas[i] = colas[i]->next;
                    delete nodoAEliminar;
                }
            }
            cout << "\nFin del programa.\n";
            break;
        }

    } while (opcion != 5);

    return 0;
}

#pragma endregion