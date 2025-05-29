/*
-------------------------------------------------------------------------------------
Tarea: #2 - Pilas (Stacks)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------
Una pila (stack) es una estructura de datos en donde el �ltimo en entrar es el primero en salir.
Construir un programa C++ que simule una pila, utilizando una estructura de datos como la que
sigue para los nodos:

struct Pila {
 int dato;
 Pila *next;
};

RESTRICCIONES:
A. La pila debe poder realizar las operaciones de Push y Pop.
B. Tener en consideraci�n de desplegar un mensaje de �Empty Stack�, cuando se trate de
hacer un Pop cuando la pila este vac�a.
C. El programa debe tener un men� para realizar las operaciones de Push, Pop y Desplegar
toda la pila realizando Pops hasta el �ltimo nodo. Adem�s, debe tener una opci�n de
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

    int dato; //Tipo de dato y nombre

    Pila* next; //Puntero a una estructura Pila
};

// Variable global para el tope de la pila
Pila* top = nullptr;

// OPERACI�N PUSH - Agregar elemento a la pila
void push() {

    int valor;

    cout << "Ingrese el valor a agregar: ";

    cin >> valor; //Lee el valor que ingreso el usuario

    //Validacion de que el usuario no ingrese letras/simbolos ya que puede entrar en un bucle infinito

    Pila* nuevo = new Pila;

    /*
        new Pila: Reserva espacio de 12-16 bytes para el heap(un nodo de manera auxiliar para poder entrar al nuevo valor)

        Pila* nuevo  : Se crea un puntero local llamado "nuevo" y almacena la direccion devuelta por "new"

    */

    nuevo->dato = valor;

    /*
        -> : Operador de acceso a miembro(valor, etc) via el puntero.
    */

    nuevo->next = top;

    /*
        Copia lo que esta en "top" , y ahora el nodo ahora "apunta" al nodo anterior
        por ej:

        nuevo -> [50]->[60]->[70]->nullptr
        top ----> [60]->[70]->nullptr
    */

    top = nuevo;

    cout << "Elemento " << valor << " agregado a la pila." << endl;
}

<<<<<<< HEAD
/*

OPERACI�N POP - Quitar elemento de la pila
Analizar mejor en verdad
----------------------------------------------
LIFO = (Last In, First Out)
*/

=======
// OPERACI�N POP - Quitar elemento de la pila
//Analizar mejor en verdad
>>>>>>> d27c21c0d53b9e3361f569be45e8e9a44ac031f6
void pop() {

    // Verificar si la pila está vacía
    if (top == nullptr) {

        cout << "Empty Stack" << endl;

        return;
    } //Evita para acceder a memoria invalida

    Pila* temp = top;

    /*
       Guarda la referencia al nodo que sera eliminado
    */

    int valor = top->dato;

    /*
        El valor que sera para mostrarlo despues
    */

    top = top->next;

    delete temp;

    cout << "Elemento " << valor << " removido de la pila." << endl;
}

// DESPLEGAR TODA LA PILA - Hacer Pops hasta el �ltimo nodo
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

// MEN� PRINCIPAL
void mostrarMenu() {

    cout << "\n=== SIMULADOR DE PILA ===" << endl;
    cout << "1. Push (Agregar elemento)" << endl;
    cout << "2. Pop (Quitar elemento)" << endl;
    cout << "3. Desplegar toda la pila" << endl;
    cout << "4. Salir\n" << endl;
    cout << "Seleccione una opcion: ";
}

//Validacion

int main() {

    int opcion;

    cout << "PROGRAMA SIMULADOR DE PILA (STACK)" << endl;

    /*while (!(cin >> opcion) {
        
        cout << "ERROR: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }*/

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