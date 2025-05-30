/*
-------------------------------------------------------------------------------------
Tarea: #4 - Colas (Queues)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------
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

    E. El programas debe ser lo suficientemente especializado para informar al usuario cuando la cola esta
    vacía.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 30/05/2025

*/

#include <iostream>
#include <string>

using namespace std;

struct Queue {
    int dato;
    Queue* next;
};

Queue* colas[17];  // 17 colas para prioridades 0-16

#pragma region FUNCIONES AUXILIARES

void inicializar() {
    for (int i = 0; i < 17; i++) {
        colas[i] = nullptr;
    }
}

bool estaVacia() {
    for (int i = 0; i < 17; i++) {
        if (colas[i] != nullptr) return false;
    }
    return true;
}

int pedirNumero() {
    int valor;
    cout << "Ingrese un numero entero: ";

    while (!(cin >> valor)) {
        cout << "Error: Solo numeros enteros permitidos.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingrese un numero entero: ";
    }
    cin.ignore(1000, '\n');

    return valor;
}

int pedirPrioridad() {
    int prioridad;
    cout << "Prioridad (0-16): ";

    while (!(cin >> prioridad)) {
        cout << "Error: Solo numeros enteros permitidos.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Prioridad (0-16): ";
    }
    cin.ignore(1000, '\n');

    return prioridad;
}

#pragma endregion

#pragma region OPERACIONES PRINCIPALES

void enqueue() {
    Queue* nuevo = new Queue;

    cout << "Dato: ";
    nuevo->dato = pedirNumero();

    int prioridad = pedirPrioridad();

    // Si la prioridad es inválida, usar 16 (default)
    if (prioridad < 0 || prioridad > 16) {
        cout << "Prioridad invalida. Usando 16 (final).\n";
        prioridad = 16;
    }

    nuevo->next = nullptr;

    // Insertar en la cola correspondiente
    if (colas[prioridad] == nullptr) {
        colas[prioridad] = nuevo;
    }
    else {
        Queue* temp = colas[prioridad];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nuevo;
    }

    cout << "Insertado: " << nuevo->dato << " (Prioridad " << prioridad << ")\n";
}

void dequeue() {
    
    if (estaVacia()) {

        cout << "Cola vacia. No se puede eliminar.\n";
        return;
    }

    // Buscar primera cola con elementos (mayor prioridad = menor número)
    for (int i = 0; i < 17; i++) {
        if (colas[i] != nullptr) {
            Queue* temp = colas[i];
            cout << "Eliminado: " << temp->dato << " (Prioridad " << i << ")\n";
            colas[i] = colas[i]->next;
            delete temp;
            return;
        }
    }
}

#pragma endregion

#pragma region VISUALIZACION

void mostrar() {
    if (estaVacia()) {
        cout << "Cola vacia.\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA COLA ===\n";
    int contador = 1;

    for (int i = 0; i < 17; i++) {
        Queue* temp = colas[i];
        while (temp != nullptr) {
            cout << contador << ". Dato: " << temp->dato << " | Prioridad: " << i << "\n";
            temp = temp->next;
            contador++;
        }
    }
    cout << "============================\n";
}

void vaciarTodo() {
    if (estaVacia()) {
        cout << "Cola vacia.\n";
        return;
    }

    cout << "\n=== VACIANDO COLA COMPLETA ===\n";
    int contador = 1;

    while (!estaVacia()) {
        for (int i = 0; i < 17; i++) {
            if (colas[i] != nullptr) {
                cout << contador << ". Eliminando: " << colas[i]->dato << " (Prioridad " << i << ")\n";
                Queue* temp = colas[i];
                colas[i] = colas[i]->next;
                delete temp;
                contador++;
                break;
            }
        }
    }
    cout << "Cola completamente vacia.\n";
}

#pragma endregion

#pragma region MENU

void menu() {
    cout << "=================================\n";
    cout << "       Cola con Prioridad\n";
    cout << "---------------------------------\n";
    cout << "Prioridades: 0 (alta) a 16 (baja)\n";
    cout << "=================================\n";
    cout << "1. Enqueue (Insertar)\n";
    cout << "2. Dequeue (Eliminar)\n";
    cout << "3. Mostrar cola\n";
    cout << "4. Vaciar cola completa\n";
    cout << "5. Salir\n";
    cout << "=================================\n";
    cout << "Opcion: ";
}

int pedirOpcion() {

    int opcion;

    while (!(cin >> opcion)) {
        cout << "Error: Solo numeros enteros permitidos.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion: ";
    }
    cin.ignore(1000, '\n');
    return opcion;
}

#pragma endregion

int main() {

    inicializar();
    int opcion;

    do {
        menu();
        opcion = pedirOpcion();

        switch (opcion) {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            mostrar();
            break;
        case 4:
            vaciarTodo();
            break;
        case 5:

            // Limpiar memoria antes de salir

            for (int i = 0; i < 17; i++) {

                while (colas[i] != nullptr) {

                    Queue* temp = colas[i];

                    colas[i] = colas[i]->next;
                    delete temp;
                }
            }
            cout << "Programa terminado.\n";
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }

        if (opcion != 5) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (opcion != 5);

    return 0;
}