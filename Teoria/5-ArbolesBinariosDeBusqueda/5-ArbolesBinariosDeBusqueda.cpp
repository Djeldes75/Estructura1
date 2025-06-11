/*
-------------------------------------------------------------------------------------------------------
Tarea: #5 - Gestión de un Árbol Binario de Búsqueda
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------------------------
    Realizar un programa C++ que permita gestionar un Árbol Binario de Búsqueda. El programa
    debe permitir insertar, buscar y eliminar un nodo; además de presentar (utilizando cualquiera
    de los recorridos) el árbol de acuerdo a las reglas que existen para el árbol binario de búsqueda.

    RESTRICCIONES:
    A. El primer nodo siempre será el root.

    B. Al presentar el árbol debe ser de un modo intuitivo, que muestre la topología de forma
    que represente en árbol.

    C. Puede utilizar cualquiera de los recorridos para arboles (InOrden, PreOrden o
    PostOrden).

    D. Al eliminar un nodo debe observar las reglas para la sustitución del nodo, permitiendo
    así que el árbol se reconstruya.

    E. Al insertar un nodo deben observarse las reglas para arboles binarios de búsqueda, es
    decir, los nodos cuyo valor sea mayor que el nodo raíz a la derecha (en el subárbol
    derecho), en caso contrario a la izquierda (en el subárbol izquierdo). Rec

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 14/Jun/2025

*/

#include <iostream>

using namespace std;

struct ArbolBST {
    int dato;
    ArbolBST* izquierdo;
    ArbolBST* derecho;
};

// Puntero a la root del arbol
ArbolBST* root = nullptr;

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
}//FIN

int leerOpcionMenu() {

    int opcion;
    bool opcionValida = false;

    while (!opcionValida) {
        opcion = validarEntero("");
        if (opcion >= 1 && opcion <= 6) {
            opcionValida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Intente nuevamente (1-6): ";
        }
    }

    return opcion;
}//FIN

int leerDato() {
    return validarEntero("Ingrese un numero: ");
}//FIN

#pragma endregion

#pragma region Funciones Auxiliares

//Verificar si el Arbol Esta Vacio
bool estaVacio() {
    return root == nullptr;
}//FIN

//Crear Nuevo Nodo
ArbolBST* crearNodo(int valor) {

    ArbolBST* nuevo = new ArbolBST;
    nuevo->dato = valor;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}//FIN

//Buscar Valor Minimo en Subarbol
ArbolBST* encontrarMinimo(ArbolBST* nodo) {

    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}//FIN

//Limpiar memoria
void liberarArbol(ArbolBST* nodo) {
    if (nodo != nullptr) {
        liberarArbol(nodo->izquierdo);
        liberarArbol(nodo->derecho);
        delete nodo;
    }
}//FIN

#pragma endregion

#pragma region Insertar/Buscar/Eliminar/Mostrar

//Insertar Elemento en el Arbol BST (Recursivo)
ArbolBST* insertarRecursivo(ArbolBST* nodo, int valor) {

    if (nodo == nullptr) {
        return crearNodo(valor);
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->dato) {
        nodo->derecho = insertarRecursivo(nodo->derecho, valor);
    }

    return nodo;
}//FIN

//Buscar Elemento en el Arbol (Recursivo)
bool buscarRecursivo(ArbolBST* nodo, int valor) {

    if (nodo == nullptr) {
        return false;
    }

    if (valor == nodo->dato) {
        return true;
    }
    else if (valor < nodo->dato) {
        return buscarRecursivo(nodo->izquierdo, valor);
    }
    else {
        return buscarRecursivo(nodo->derecho, valor);
    }
}//FIN

//Insertar Elemento
void insertar() {

    int valor = leerDato();

    // Verificar si el elemento ya existe
    if (buscarRecursivo(root, valor)) {
        cout << "\nElemento " << valor << " ya existe. No se inserto.\n\n";
        return;
    }

    root = insertarRecursivo(root, valor);
    cout << "\nElemento " << valor << " insertado correctamente en el arbol.\n\n";
}//FIN

//Buscar Elemento
void buscar() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    int valor = leerDato();

    if (buscarRecursivo(root, valor)) {
        cout << "\nElemento " << valor << " encontrado en el arbol.\n\n";
    }
    else {
        cout << "\nElemento " << valor << " no encontrado en el arbol.\n\n";
    }
}//FIN

//Eliminar Elemento del Arbol (Recursivo)
ArbolBST* eliminarRecursivo(ArbolBST* nodo, int valor) {

    if (nodo == nullptr) {
        return nodo;
    }

    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->dato) {
        nodo->derecho = eliminarRecursivo(nodo->derecho, valor);
    }
    else {
        // Nodo encontrado
        if (nodo->izquierdo == nullptr) {
            ArbolBST* temp = nodo->derecho;
            delete nodo;
            return temp;
        }
        else if (nodo->derecho == nullptr) {
            ArbolBST* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // Nodo con dos hijos
        ArbolBST* temp = encontrarMinimo(nodo->derecho);
        nodo->dato = temp->dato;
        nodo->derecho = eliminarRecursivo(nodo->derecho, temp->dato);
    }
    return nodo;
}//FIN

//Eliminar Elemento
void eliminar() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    int valor = leerDato();

    if (!buscarRecursivo(root, valor)) {
        cout << "\nElemento " << valor << " no encontrado en el arbol.\n\n";
        return;
    }

    root = eliminarRecursivo(root, valor);
    cout << "\nElemento " << valor << " eliminado del arbol.\n\n";
}//FIN

//Recorrido InOrden (Recursivo)
void inOrdenRecursivo(ArbolBST* nodo) {
    if (nodo != nullptr) {
        inOrdenRecursivo(nodo->izquierdo);
        cout << nodo->dato << " ";
        inOrdenRecursivo(nodo->derecho);
    }
}//FIN

//Recorrido PreOrden (Recursivo)
void preOrdenRecursivo(ArbolBST* nodo) {
    if (nodo != nullptr) {
        cout << nodo->dato << " ";
        preOrdenRecursivo(nodo->izquierdo);
        preOrdenRecursivo(nodo->derecho);
    }
}//FIN

//Recorrido PostOrden (Recursivo)
void postOrdenRecursivo(ArbolBST* nodo) {
    if (nodo != nullptr) {
        postOrdenRecursivo(nodo->izquierdo);
        postOrdenRecursivo(nodo->derecho);
        cout << nodo->dato << " ";
    }
}//FIN

//Mostrar Recorridos del Arbol
void mostrarRecorridos() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    cout << "\n=== RECORRIDOS DEL ARBOL BST ===\n";

    cout << "InOrden:   ";
    inOrdenRecursivo(root);
    cout << "\n";

    cout << "PreOrden:  ";
    preOrdenRecursivo(root);
    cout << "\n";

    cout << "PostOrden: ";
    postOrdenRecursivo(root);
    cout << "\n";

    cout << "=================================\n\n";
}//FIN

// Función auxiliar para mostrar la estructura del árbol (recursiva)
void mostrarArbolRecursivo(ArbolBST* nodo, int nivel) {
    if (nodo == nullptr) {
        return;
    }
    // Recorrer subárbol derecho (arriba del nodo actual)
    mostrarArbolRecursivo(nodo->derecho, nivel + 1);

    // Indentar según el nivel
    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }
    // Mostrar dato del nodo
    cout << nodo->dato << endl;

    // Recorrer subárbol izquierdo (debajo del nodo actual)
    mostrarArbolRecursivo(nodo->izquierdo, nivel + 1);
}//FIN

//Mostrar Estructura del Arbol
void mostrarArbol() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    cout << "\n=== ESTRUCTURA DEL ARBOL BST ===\n";
    mostrarArbolRecursivo(root, 0);
    cout << "=================================\n\n";
}//FIN

#pragma endregion

#pragma region Menu

void mostrarMenu() {
    cout << "=================================\n";
    cout << "      Arbol Binario de Busqueda\n";
    cout << "=================================\n";
    cout << "1. Insertar elemento\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Eliminar elemento\n";
    cout << "4. Mostrar recorridos\n";
    cout << "5. Desplegar\n";
    cout << "6. Salir\n";
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
            mostrarRecorridos();
            break;

        case 5:
            mostrarArbol();
            break;

        case 6:
            cout << "Fin del programa.\n";
            break;
        }

    } while (opcion != 6);

    liberarArbol(root);
    root = nullptr;

    return 0;
}//FIN

#pragma endregion