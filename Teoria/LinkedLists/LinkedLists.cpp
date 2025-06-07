/*
-------------------------------------------------------------------------------------------------------
Tarea: #4 - Listas Enlazadas (Linked List)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------------------------
Una Lista Enlazada (Linked List) es una estructura de datos en donde cada nodo apunta a uno siguiente y
de esta manera se mantiene un enlace entre los nodos. Para nuestro caso, haremos el problema un poco
más real exigiendo que al insertar cada nodo, este se inserte de manera ordenada (ascendente) de modo
que los nodos se indexen según su dato. La Lista Enlazada (Linked List) tiene la siguiente forma para los
nodos:

struct LinkedList {
 int dato;
 LinkedList *next;
};

RESTRICCIONES:
    A. La Lista Enlazada (Linked List) debe poder realizar las operaciones Insertar, Buscar, Eliminar y 
       Mostrar la Lista Enlazada.

    B. Al insertar un nuevo nodo el programa debe contemplar realizar la inserción del nodo donde le
       corresponda, ya que la lista debe estar ordenada en forma ascendente según su dato.

    C. El programa deberá tener un menú con las opciones para Insertar, Buscar, Eliminar y Mostrar la Lista
       Enlazada y Salir.

    D. Las entradas de datos del usuario deben ser debidamente validas.

    E. El programa debe ser lo suficientemente especializado para informar al usuario cuando la lista esta
       vacía.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 5/Diciembre/2025

*/

#include <iostream>

using namespace std;

struct LinkedList {
    int dato;
    LinkedList* next;   // Puntero al siguiente nodo en la lista
};

// Puntero al primer nodo de la lista enlazada
LinkedList* cabeza = nullptr;

#pragma region Funciones Auxiliares

//Verificar si la Lista Esta Vacia
bool estaVacia() {
    return cabeza == nullptr;
}
//Fin de Func. estaVacia

//Validar Input del Usuario - Numero Entero
int pedirNumero() {

    double numero;
    int numeroEntero;

    cout << "Ingrese un numero: ";

    while (true) {
        if (cin >> numero) {

            if (numero == (int)numero) {
                numeroEntero = (int)numero;
                break;
            }
            else {
                cout << "ERROR: No se permiten decimales. Solo numeros enteros." << endl;
            }
        }
        else {
            cout << "ERROR: Entrada invalida. Solo numeros." << endl;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nVuelva a ingresar un numero: ";
    }

    return numeroEntero;
}
//Fin de Func. pedirNumero

#pragma endregion

#pragma region OPERACIONES PRINCIPALES

//Insertar Elemento de Manera Ordenada (Ascendente)
void insertar() {

    LinkedList* nuevo = new LinkedList;
    nuevo->dato = pedirNumero();
    nuevo->next = nullptr;

    // Si la lista está vacía o el nuevo dato es menor que el primer elemento
    if (cabeza == nullptr || nuevo->dato < cabeza->dato) {
        nuevo->next = cabeza;
        cabeza = nuevo;
        cout << "\n{Dato: " << nuevo->dato << "} insertado al inicio de la lista.\n\n";
        return;
    }

    // Buscar la posición correcta para insertar
    LinkedList* actual = cabeza;
    LinkedList* anterior = nullptr;

    while (actual != nullptr && actual->dato < nuevo->dato) {
        anterior = actual;
        actual = actual->next;
    }

    // Verificar si el dato ya existe
    if (actual != nullptr && actual->dato == nuevo->dato) {
        cout << "\nERROR: El dato " << nuevo->dato << " ya existe en la lista.\n\n";
        delete nuevo;
        return;
    }

    // Insertar el nuevo nodo en la posición correcta
    anterior->next = nuevo;
    nuevo->next = actual;

    cout << "\n{Dato: " << nuevo->dato << "} insertado correctamente en la lista ordenada.\n\n";
}
//Fin de Func. insertar

//Buscar Elemento en la Lista
void buscar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    int valorBuscado = pedirNumero();
    LinkedList* temp = cabeza;
    int posicion = 1;

    while (temp != nullptr) {
        if (temp->dato == valorBuscado) {
            cout << "\nElemento ENCONTRADO: " << valorBuscado << " en la posicion " << posicion << "\n\n";
            return;
        }
        temp = temp->next;
        posicion++;
    }

    cout << "\nElemento NO ENCONTRADO: " << valorBuscado << " no existe en la lista.\n\n";
}
//Fin de Func. buscar

//Eliminar Elemento de la Lista
void eliminar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    int valorEliminar = pedirNumero();

    // Si el elemento a eliminar es el primero
    if (cabeza->dato == valorEliminar) {
        LinkedList* temp = cabeza;
        cabeza = cabeza->next;
        cout << "\nEliminado: " << temp->dato << " (era el primer elemento)\n\n";
        delete temp;
        return;
    }

    // Buscar el elemento a eliminar
    LinkedList* actual = cabeza;
    LinkedList* anterior = nullptr;

    while (actual != nullptr && actual->dato != valorEliminar) {
        anterior = actual;
        actual = actual->next;
    }

    // Si no se encontró el elemento
    if (actual == nullptr) {
        cout << "\nERROR: El elemento " << valorEliminar << " no existe en la lista.\n\n";
        return;
    }

    // Eliminar el nodo
    anterior->next = actual->next;
    cout << "\nEliminado: " << actual->dato << " correctamente de la lista.\n\n";
    delete actual;
}
//Fin de Func. eliminar

#pragma endregion

#pragma region Mostrar Lista

//Mostrar Todos los Elementos de la Lista
void mostrar() {

    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA LISTA ENLAZADA ===\n";
    LinkedList* temp = cabeza;
    int contador = 1;

    while (temp != nullptr) {
        cout << contador << ". Dato: " << temp->dato << "\n";
        temp = temp->next;
        contador++;
    }
    cout << "=====================================\n\n";
}
//Fin de Func. mostrar

//Vaciar Completamente la Lista
void vaciarLista() {
    if (estaVacia()) {
        cout << "Lista vacia.\n\n";
        return;
    }

    cout << "\n=== VACIANDO LISTA COMPLETA ===\n";
    int contador = 1;

    while (cabeza != nullptr) {
        cout << contador << ". Eliminando: " << cabeza->dato << "\n";
        
        LinkedList* temp = cabeza;
        cabeza = cabeza->next;
        delete temp;
        
        contador++;
    }
    cout << "\nLista completamente vacia.\n\n";
}
//Fin de Func. vaciarLista

#pragma endregion

#pragma region MENU

//Mostrar Menu Principal
void menu() {
    cout << "=================================\n";
    cout << "      Lista Enlazada Ordenada\n";
    cout << "=================================\n";
    cout << "1. Insertar (Ordenado)\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Eliminar elemento\n";
    cout << "4. Mostrar lista\n";
    cout << "5. Vaciar lista completa\n";
    cout << "6. Salir\n";
    cout << "=================================\n";
    cout << "Opcion: ";
}
//Fin de Func. Menu

//Validar Input del Usuario - Opcion de Menu
int pedirOpcion() {

    double opcion;
    int opcionEntera;

    while (true) {

        if (cin >> opcion) {

            if (opcion == (int)opcion) {
                opcionEntera = (int)opcion;
                break;
            }
            else {
                cout << "Error: Solo numeros enteros permitidos.\n";
            }
        }
        else {
            cout << "Error: Entrada invalida. Solo numeros.\n";
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nVuelva a ingresar una opcion: ";

    }
    return opcionEntera;
}
//Fin de Func. pedirOpcion

#pragma endregion

#pragma region MAIN

int main() {

    int opcion;

    do {

        menu();
        opcion = pedirOpcion();

        switch (opcion) {

        case 1:
            insertar();
            break;

        case 2:
            buscar();
            break;

        case 3:
            eliminar();
            break;

        case 4:
            mostrar();
            break;

        case 5:
            vaciarLista();
            break;

        case 6:

            while (cabeza != nullptr) {
                LinkedList* temp = cabeza;
                cabeza = cabeza->next;
                delete temp;
            }
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "ERROR: Opcion invalida. Intente de nuevamente.\n\n";
        }

    } while (opcion != 6);

    return 0;
}

#pragma endregion