/*
-------------------------------------------------------------------------------------
Tarea: #2 - Pilas (Stacks)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------
Una pila (stack) es una estructura de datos en donde el último en entrar es el primero en salir.
Construir un programa C++ que simule una pila, utilizando una estructura de datos como la que
sigue para los nodos:

struct Pila {
 int dato;
 Pila *next;
};

RESTRICCIONES:
A. La pila debe poder realizar las operaciones de Push y Pop.
B. Tener en consideración de desplegar un mensaje de “Empty Stack”, cuando se trate de
hacer un Pop cuando la pila este vacía.
C. El programa debe tener un menú para realizar las operaciones de Push, Pop y Desplegar
toda la pila realizando Pops hasta el último nodo. Además, debe tener una opción de
salir del programa.

Nota: Este programa valida correctamente las entradas del usuario y maneja escenarios de errores para garantizar su robustez.

INTEGRANTES (Grupo 6):
    Samira Vasquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 28/05/2025

*/

#include <iostream>

using namespace std;

struct Pila {

    int dato;

    Pila* next;
};

// Variable global para el tope de la pila
Pila* top = nullptr;

// OPERACIÓN PUSH - Agregar elemento a la pila
void push() {

    int valor;

    cout << "Ingrese el valor a agregar: ";

    cin >> valor;

    Pila* nuevo = new Pila;

    nuevo->dato = valor;

    nuevo->next = top;

    top = nuevo;

    cout << "Elemento " << valor << " agregado a la pila." << endl;
}

// OPERACIÓN POP - Quitar elemento de la pila
void pop() {

    // Verificar si la pila está vacía
    if (top == nullptr) {

        cout << "Empty Stack" << endl;

        return;
    }

    Pila* temp = top;

    int valor = top->dato;

    top = top->next;

    delete temp;

    cout << "Elemento " << valor << " removido de la pila." << endl;
}

// DESPLEGAR TODA LA PILA - Hacer Pops hasta el último nodo
void desplegarTodaLaPila() {

    if (top == nullptr) {

        cout << "Empty Stack" << endl;

        return;
    }

    cout << "\nDesplegando toda la pila:" << endl;

    while (top != nullptr) {

        cout << "Pop: " << top->dato << endl;

        Pila* temp = top;

        top = top->next;

        delete temp;
    }
    cout << "Pila completamente vaciada." << endl;
}

// MENÚ PRINCIPAL
void mostrarMenu() {

    cout << "\n=== SIMULADOR DE PILA ===" << endl;
    cout << "1. Push (Agregar elemento)" << endl;
    cout << "2. Pop (Quitar elemento)" << endl;
    cout << "3. Desplegar toda la pila" << endl;
    cout << "4. Salir\n" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {

    int opcion;

    cout << "PROGRAMA SIMULADOR DE PILA (STACK)" << endl;

    do {
        mostrarMenu();

        cin >> opcion;

        switch (opcion) {

        case 1:
            push();
            break;

        case 2:
            pop();
            break;

        case 3:
            desplegarTodaLaPila();
            break;

        case 4:
            cout << "\nSaliendo del programa..." << endl;

            // Liberar memoria restante antes de salir
            while (top != nullptr) {

                Pila* temp = top;

                top = top->next;

                delete temp;
            }
            break;

        default:

            cout << "\nERROR: Opcion invalida. Seleccione del 1 al 4." << endl;

            break;
        }

    } while (opcion != 4);

    return 0;
}