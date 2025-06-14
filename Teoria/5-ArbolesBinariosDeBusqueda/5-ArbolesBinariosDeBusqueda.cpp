/*
-------------------------------------------------------------------------------------------------------
Tarea: #7 - Gestión de un Árbol Binario de Búsqueda
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Un Árbol Binario de Búsqueda (BST) es una estructura de datos jerárquica donde cada nodo tiene
como máximo dos hijos (izquierdo y derecho). Los valores menores van al subárbol izquierdo y
los valores mayores van al subárbol derecho.

Estructura del nodo:
struct ArbolBST {
    int dato;
    ArbolBST *izquierdo;
    ArbolBST *derecho;
};

RESTRICCIONES:
    A. El primer nodo siempre será el root.
    B. Presentar el árbol de modo intuitivo mostrando la topología.
    C. Utilizar recorridos InOrden, PreOrden o PostOrden.
    D. Al eliminar observar las reglas de sustitución del nodo.
    E. Al insertar observar las reglas del BST (menores izquierda, mayores derecha).

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

struct ArbolBST {
    int dato;
    ArbolBST* izquierdo;
    ArbolBST* derecho;
};

// Puntero al nodo raíz del árbol
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

//Verificar si el Árbol Esta Vacío
bool estaVacio() {
    return root == nullptr;
}//FIN

//Crear un nuevo nodo
ArbolBST* crearNodo(int valor) {
    ArbolBST* nuevo = new ArbolBST;
    nuevo->dato = valor;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}//FIN

//Encontrar el nodo con valor mínimo (más a la izquierda)
ArbolBST* encontrarMinimo(ArbolBST* nodo) {
    while (nodo && nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}//FIN

int calcularAltura(ArbolBST* nodo) {
    if (nodo == nullptr) {
        return -1; // Convención: árbol vacío tiene altura -1
    }

    int alturaIzq = calcularAltura(nodo->izquierdo);
    int alturaDer = calcularAltura(nodo->derecho);

    // Función max manual para evitar usar <algorithm>
    int alturaMaxima = (alturaIzq > alturaDer) ? alturaIzq : alturaDer;

    return 1 + alturaMaxima;
}//FIN

#pragma endregion

#pragma region Insertar/Buscar/Eliminar

//Insertar Elemento (Función Recursiva)
ArbolBST* insertarRecursivo(ArbolBST* nodo, int valor) {
    // Caso base: si el nodo es nulo, crear nuevo nodo
    if (nodo == nullptr) {
        return crearNodo(valor);
    }

    // Si el valor ya existe, retornar el nodo sin modificar
    if (valor == nodo->dato) {
        return nodo;
    }

    // Insertar en el subárbol correspondiente según reglas BST
    if (valor < nodo->dato) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
    }
    else {
        nodo->derecho = insertarRecursivo(nodo->derecho, valor);
    }

    return nodo;
}//FIN

//Buscar Elemento (Función Recursiva)
ArbolBST* buscarRecursivo(ArbolBST* nodo, int valor) {
    // Caso base: nodo nulo o valor encontrado
    if (nodo == nullptr || nodo->dato == valor) {
        return nodo;
    }

    // Buscar en el subárbol correspondiente según reglas BST
    if (valor < nodo->dato) {
        return buscarRecursivo(nodo->izquierdo, valor);
    }
    else {
        return buscarRecursivo(nodo->derecho, valor);
    }
}//FIN

//Insertar Elemento
void insertar() {
    int valor = leerDato();

    if (estaVacio()) {
        root = crearNodo(valor);
        cout << "\nElemento " << valor << " insertado como root del arbol.\n\n";
    }
    else {
        // Verificar si el elemento ya existe antes de intentar insertar
        if (buscarRecursivo(root, valor) != nullptr) {
            cout << "\nERROR: El elemento " << valor << " ya existe en el arbol.\n\n";
        }
        else {
            root = insertarRecursivo(root, valor);
            cout << "\nElemento " << valor << " insertado correctamente en el arbol.\n\n";
        }
    }
}//FIN

//Buscar Elemento
void buscar() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    int valorABuscar = leerDato();
    ArbolBST* resultado = buscarRecursivo(root, valorABuscar);

    if (resultado != nullptr) {
        cout << "\nElemento " << valorABuscar << " encontrado en el arbol.\n\n";
    }
    else {
        cout << "\nElemento " << valorABuscar << " no encontrado en el arbol.\n\n";
    }
}//FIN

//Eliminar Elemento (Función Recursiva)
ArbolBST* eliminarRecursivo(ArbolBST* nodo, int valor) {

    // Caso base: nodo no encontrado
    if (nodo == nullptr) {
        return nodo;
    }

    // Buscar el nodo a eliminar
    if (valor < nodo->dato) {
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor);
    }
    else if (valor > nodo->dato) {
        nodo->derecho = eliminarRecursivo(nodo->derecho, valor);
    }
    else {
        // Nodo encontrado, aplicar reglas de sustitución

        // Caso 1: Nodo sin hijos (hoja)
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            delete nodo;
            return nullptr;
        }

        // Caso 2: Nodo con un solo hijo
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

        // Caso 3: Nodo con dos hijos - usar sucesor inorden
        ArbolBST* sucesor = encontrarMinimo(nodo->derecho);
        nodo->dato = sucesor->dato;
        nodo->derecho = eliminarRecursivo(nodo->derecho, sucesor->dato);
    }

    return nodo;
}//FIN

//Eliminar Elemento
void eliminar() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    int valorAEliminar = leerDato();

    // Verificar si el elemento existe antes de eliminar
    if (buscarRecursivo(root, valorAEliminar) == nullptr) {
        cout << "\nElemento " << valorAEliminar << " no encontrado en el arbol.\n\n";
        return;
    }

    root = eliminarRecursivo(root, valorAEliminar);
    cout << "\nElemento " << valorAEliminar << " eliminado del arbol.\n\n";
}//FIN

#pragma endregion

#pragma region Mostrar Arbol

//Mostrar Árbol con Topología
void mostrarArbol(ArbolBST* nodo, int nivel) {
    if (nodo != nullptr) {
        // Mostrar subárbol derecho primero (arriba)
        mostrarArbol(nodo->derecho, nivel + 1);

        // Mostrar nodo actual con indentación
        for (int i = 0; i < nivel; i++) {
            cout << "    ";
        }
        cout << nodo->dato << "\n";

        // Mostrar subárbol izquierdo (abajo)
        mostrarArbol(nodo->izquierdo, nivel + 1);
    }
}//FIN

//Recorrido InOrden: Izquierdo -> Root -> Derecho. Ascendente
void inOrden(ArbolBST* nodo) {
    if (nodo != nullptr) {
        inOrden(nodo->izquierdo);
        cout << nodo->dato << " ";
        inOrden(nodo->derecho);
    }
}//FIN

//Recorrido PreOrden: Root -> Izquierdo -> Derecho
void preOrden(ArbolBST* nodo) {
    if (nodo != nullptr) {
        cout << nodo->dato << " ";
        preOrden(nodo->izquierdo);
        preOrden(nodo->derecho);
    }
}//FIN

//Recorrido PostOrden: Izquierdo -> Derecho -> Root
void postOrden(ArbolBST* nodo) {
    if (nodo != nullptr) {
        postOrden(nodo->izquierdo);
        postOrden(nodo->derecho);
        cout << nodo->dato << " ";
    }
}//FIN

//Presentar Árbol con todos los recorridos
void presentarArbol() {

    if (estaVacio()) {
        cout << "Arbol vacio.\n\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "           ARBOL BINARIO DE BUSQUEDA\n";
    cout << "============================================\n\n";

    // Mostrar todos los tipos de recorridos
    cout << "=== RECORRIDOS DEL ARBOL ===\n";

    cout << "InOrden  (Izq->Root->Der): ";
    inOrden(root);
    cout << "\n";

    cout << "PreOrden (Root->Izq->Der): ";
    preOrden(root);
    cout << "\n";

    cout << "PostOrden(Izq->Der->Root): ";
    postOrden(root);
    cout << "\n\n";

    // Mostrar información adicional del árbol
    cout << "=== INFORMACION DEL ARBOL ===\n";
    cout << "Altura del arbol: " << calcularAltura(root) << "\n";
    cout << "Nodo raiz: " << root->dato << "\n\n";

    // Mostrar la topología visual del árbol
    cout << "=== TOPOLOGIA VISUAL DEL ARBOL ===\n";
    mostrarArbol(root, 0);

    cout << "\n============================================\n\n";
}//FIN

#pragma endregion

#pragma region Menu

void mostrarMenu() {
    cout << "=========================================\n";
    cout << "        Arbol Binario de Busqueda\n";
    cout << "=========================================\n";
    cout << "1. Insertar elemento\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Eliminar elemento\n";
    cout << "4. Presentar arbol\n";
    cout << "5. Salir\n";
    cout << "=========================================\n";
    cout << "Opcion: ";
}//FIN

#pragma endregion

#pragma region Funciones de Limpieza

//Limpiar Árbol (Función Recursiva)
void limpiarArbol(ArbolBST* nodo) {
    if (nodo != nullptr) {
        limpiarArbol(nodo->izquierdo);
        limpiarArbol(nodo->derecho);
        delete nodo;
    }
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
            presentarArbol();
            break;

        case 5:
            limpiarArbol(root);
            cout << "\nFin del programa.\n";
            break;
        }

    } while (opcion != 5);

    return 0;
}//FIN

#pragma endregion