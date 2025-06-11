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

    B. Tener en consideración de desplegar un mensaje de "Empty Stack", cuando se trate de
    hacer un Pop cuando la pila este vacía.

    C. El programa debe tener un menú para realizar las operaciones de Push, Pop y Desplegar
    toda la pila realizando Pops hasta el último nodo. Además, debe tener una opción de
    salir del programa.

Nota: Este programa valida correctamente las entradas del usuario y maneja escenarios de errores para garantizar su robustez.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 28/05/2025

*/

#include <iostream>

using namespace std;

//Estructura base
struct Pila {
    int dato;
    Pila* next;
};

//Variable global:
Pila* top = nullptr;

#pragma region Validacion

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
}//FIN

int leerDato() {
    return validarEntero("\nIngrese un numero: ");
}//FIN

int leerOpcionMenu() {

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
}//FIN

//Esta vacia? Si o No
bool estaVacia() {
    return top == nullptr;
}//FIN

#pragma endregion

#pragma region Push/Pop/Desplegar

void push() {
    int valor = leerDato();

    Pila* nuevo = new Pila;
    nuevo->dato = valor;
    nuevo->next = top;

    top = nuevo;

    cout << "\nElemento " << valor << " agregado a la pila.\n" << endl;
}//FIN

void pop() {

    if (estaVacia()) {
        cout << "Empty Stack\n" << endl;
        return;
    }

    int valor = top->dato;
    Pila* temp = top;

    top = top->next;
    delete temp;

    cout << "\nElemento " << valor << " removido de la pila.\n" << endl;
}//FIN

void desplegarTodaPila() {

    if (estaVacia()) {
        cout << "Empty Stack\n" << endl;
        return;
    }

    cout << "\nDesplegando toda la pila:" << endl;

    while (top != nullptr) {
        cout << "Pop: " << top->dato << endl;

        Pila* temp = top;
        top = top->next;
        delete temp;
    }

    cout << "Pila completamente vaciada.\n" << endl;
}//FIN

#pragma endregion

#pragma region Menu

void mostrarMenu() {
    cout << "=================================\n";
    cout << "       Simulador De Stack\n";
    cout << "=================================\n";
    cout << "1. Push (Agregar)" << endl;
    cout << "2. Pop (Quitar)" << endl;
    cout << "3. Desplegar toda la pila" << endl;
    cout << "4. Salir" << endl;
    cout << "=================================\n";
    cout << "Seleccione una opcion: ";
}

#pragma endregion

#pragma region Main

int main() {

    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {
        case 1:
            push();
            break;

        case 2:
            pop();
            break;

        case 3:
            desplegarTodaPila();
            break;

        case 4:
            cout << "\nSaliendo del programa..." << endl;

            while (top != nullptr) {
                Pila* temp = top;
                top = top->next;
                delete temp;
            }
            break;
        }

    } while (opcion != 4);

    return 0;
}

#pragma endregion