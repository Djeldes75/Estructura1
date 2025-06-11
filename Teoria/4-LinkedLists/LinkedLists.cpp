/*
-------------------------------------------------------------------------------------------------------
Tarea: #4 - Lista Enlazada (Linked List)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------------------------
Una Lista Enlazada (Linked List) es una estructura de datos en donde cada nodo apunta a uno siguiente
y de esta manera se mantiene un enlace entre los nodos. Para nuestro caso, haremos el problema un poco
m�s real exigiendo que al insertar cada nodo, este se inserte de manera ordenada (ascendente) de modo
que los nodos se indexen seg�n su dato. La Lista Enlazada (Linked List) tiene la siguiente forma
para los nodos:

struct LinkedList {
 int dato;
 LinkedList *next;
};

RESTRICCIONES:
    A. La Lista Enlazada (Linked List) debe poder realizar las operaciones Insertar, Buscar,
       Eliminar y Mostrar la Lista Enlazada.

    B. Al insertar un nuevo nodo el programa debe contemplar realizar la inserci�n del nodo donde le
       corresponda, ya que la lista debe estar ordenada en forma ascendente seg�n su dato.

    C. El programa deber� tener un men� con las opciones para Insertar, Buscar, Eliminar y
       Mostrar la Lista Enlazada y Salir.

    D. Las entradas de datos del usuario deben ser debidamente validas.

    E. El programa debe ser lo suficientemente especializado para informar al usuario cuando la
       Lista Enlazada (Linked List) est� vac�a.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 11/Jun/2025

*/

#include <iostream>

using namespace std;

struct LinkedList {
    int dato;
    LinkedList* next;
};

// Puntero al primer nodo de la lista enlazada
LinkedList* cabeza = nullptr;

#pragma region Validaciones

//Validacion Universal para Enteros
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

//Validar Opcion del Menu
int leerOpcionMenu() {

    int opcion;
    bool opcionValida = false;

    while (!opcionValida) {
        opcion = validarEntero("");
        if (opcion >= 1 && opcion <= 5) {
            opcionValida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Intente nuevamente (1-5): ";
        }
    }

    return opcion;
}//FIN

//Validar Dato
int leerDato() {
    return validarEntero("Ingrese un numero: ");
}//FIN

#pragma endregion

#pragma region Funciones Auxiliares

//Verificar si la Lista Esta Vacia
bool estaVacia() {
    return cabeza == nullptr;
}//FIN

#pragma endregion

#pragma region  Insertar/Buscar/Eliminar/Mostrar

//Insertar Elemento en Orden Ascendente
void insertar() {

    LinkedList* nuevo = new LinkedList;
    nuevo->dato = leerDato();
    nuevo->next = nullptr;

    // Si la lista esta vacia o el nuevo dato es menor que el primer elemento
    if (cabeza == nullptr || nuevo->dato < cabeza->dato) {
        nuevo->next = cabeza;
        cabeza = nuevo;
        cout << "\nElemento " << nuevo->dato << " insertado al inicio de la lista.\n\n";
        return;
    }

    // Buscar la posicion correcta para insertar
    LinkedList* actual = cabeza;
    LinkedList* anterior = nullptr;

    while (actual != nullptr && actual->dato < nuevo->dato) {
        anterior = actual;
        actual = actual->next;
    }

    // Verificar si el dato ya existe
    if (actual != nullptr && actual->dato == nuevo->dato) {
        cout << "\nERROR: El elemento " << nuevo->dato << " ya existe en la lista.\n\n";
        delete nuevo;
        return;
    }

    // Insertar el nuevo nodo en la posicion correcta
    anterior->next = nuevo;
    nuevo->next = actual;

    cout << "\nElemento " << nuevo->dato << " insertado correctamente en la lista.\n\n";
}//FIN

//Buscar Elemento en la Lista
void buscar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    int datoABuscar = leerDato();
    LinkedList* actual = cabeza;
    int posicion = 1;

    while (actual != nullptr) {
        if (actual->dato == datoABuscar) {
            cout << "\nElemento " << datoABuscar << " encontrado en la posicion " << posicion << ".\n\n";
            return;
        }
        actual = actual->next;
        posicion++;
    }

    cout << "\nElemento " << datoABuscar << " no encontrado en la lista.\n\n";
}//FIN

//Eliminar Elemento de la Lista
void eliminar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    int datoAEliminar = leerDato();

    // Si el elemento a eliminar es el primero
    if (cabeza->dato == datoAEliminar) {
        LinkedList* nodoAEliminar = cabeza;
        cabeza = cabeza->next;
        delete nodoAEliminar;
        cout << "\nElemento " << datoAEliminar << " eliminado de la lista.\n\n";
        return;
    }

    // Buscar el elemento en el resto de la lista
    LinkedList* actual = cabeza;
    LinkedList* anterior = nullptr;

    while (actual != nullptr && actual->dato != datoAEliminar) {
        anterior = actual;
        actual = actual->next;
    }

    // Si no se encontro el elemento
    if (actual == nullptr) {
        cout << "\nElemento " << datoAEliminar << " no encontrado en la lista.\n\n";
        return;
    }

    // Eliminar el nodo
    anterior->next = actual->next;
    delete actual;
    cout << "\nElemento " << datoAEliminar << " eliminado de la lista.\n\n";
}//FIN

//Mostrar Todos los Elementos de la Lista
void mostrar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA LISTA ENLAZADA ===\n";
    LinkedList* actual = cabeza;
    int posicion = 1;

    while (actual != nullptr) {
        cout << posicion << ". " << actual->dato << "\n";
        actual = actual->next;
        posicion++;
    }
    cout << "=====================================\n\n";
}//FIN

#pragma endregion

#pragma region Menu

//Mostrar Menu Principal
void mostrarMenu() {
    cout << "=================================\n";
    cout << "          Lista Enlazada\n";
    cout << "=================================\n";
    cout << "1. Insertar elemento\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Eliminar elemento\n";
    cout << "4. Mostrar lista\n";
    cout << "5. Salir\n";
    cout << "=================================\n";
    cout << "Opcion: ";
}//FIN

#pragma endregion

#pragma region Main

int main() {

    int opcion;

    do {
        mostrarMenu();
        opcion = leerOpcionMenu();

        switch (opcion) {
        case 1:
            cout << "\n--- INSERTAR ELEMENTO ---\n";
            insertar();
            break;

        case 2:
            cout << "\n--- BUSCAR ELEMENTO ---\n";
            buscar();
            break;

        case 3:
            cout << "\n--- ELIMINAR ELEMENTO ---\n";
            eliminar();
            break;

        case 4:
            mostrar();
            break;

        case 5:
            // Limpiar memoria antes de salir
            while (cabeza != nullptr) {
                LinkedList* nodoAEliminar = cabeza;
                cabeza = cabeza->next;
                delete nodoAEliminar;
            }
            cout << "\nFin del programa.\n";
            break;
        }

    } while (opcion != 5);

    return 0;
}//FIN

#pragma endregion