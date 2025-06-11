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
    int prioridad;
    Queue* next;
};

Queue* frente = nullptr;

// Validar entero
int validarEntero(const char* mensaje) {
    int valor;
    char c;
    cout << mensaje;

    while (true) { //ARREGLAR ESTE BUCLE, YA QUE ES MALA PRACTICA. - Y cambiar el nombre de la variable "char c;" a algo mas legible     
        if (cin >> valor) {
            c = cin.peek();
            if (c == '\n' || c == ' ') {
                while (cin.get() != '\n');
                return valor;
            }
            else {
                cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
                cin.clear();
                while (cin.get() != '\n');
            }
        }
        else {
            cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

int leerDato() {
    return validarEntero("Ingrese un numero: ");
}

int leerPrioridad() {
    int prioridad = validarEntero("Ingrese la prioridad (0-16): ");
    if (prioridad < 0 || prioridad > 16) {
        cout << "Prioridad fuera de rango. Se asigna prioridad por defecto (16).\n";
        return 16;
    }
    return prioridad;
}

bool estaVacia() {
    return frente == nullptr;
}

void enqueue() {
 
    int dato = leerDato();
    int prioridad = leerPrioridad();

    Queue* nuevo = new Queue{ dato, prioridad, nullptr };

    if (frente == nullptr) {
        // Primer elemento insertado
        frente = nuevo;
    }
    else if (prioridad == 0) {
        // Insertar al frente si es prioridad 0
        nuevo->next = frente;
        frente = nuevo;
    }
    else {
        // Insertar según prioridad después del front
        Queue* actual = frente;

        // Evitamos mover el front, así que empezamos desde el segundo nodo
        while (actual->next != nullptr && actual->next->prioridad <= prioridad) {
            actual = actual->next;
        }

        nuevo->next = actual->next;
        actual->next = nuevo;
    }

    cout << "\nIngresado: {Dato: " << dato << "} - {Prioridad: " << prioridad << "}\n\n";
}

void dequeue() {
 
    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }

    Queue* temp = frente;
    frente = frente->next;

    cout << "\nEliminado: " << temp->dato << " (Prioridad " << temp->prioridad << ")\n\n";
    delete temp;
}

void mostrar() {
 
    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA COLA ===\n";
    int i = 1;
    Queue* actual = frente;
    while (actual != nullptr) {
        cout << i++ << ". Dato: " << actual->dato << " | Prioridad: " << actual->prioridad << "\n";
        actual = actual->next;
    }
    cout << "============================\n\n";
}

void vaciarTodo() {
 
    if (estaVacia()) {
        cout << "\nCola vacia.\n\n";
        return;
    }
 
    int i = 1;
 
    while (frente != nullptr) {
     
        Queue* temp = frente;
        cout << i++ << ". Eliminando: " << frente->dato << " (Prioridad " << frente->prioridad << ")\n";
        frente = frente->next;
        delete temp;
    }
    cout << "\nCola completamente vacia.\n\n";
}

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

int leerOpcionMenu() {
 
    int opcion = validarEntero("");
 
    while (opcion < 1 || opcion > 5) {
        cout << "ERROR: Opcion invalida. Intente nuevamente (1-5): ";
        opcion = validarEntero("");
    }
    return opcion;
}

int main() {
 
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
            vaciarTodo();
            cout << "\nFin del programa.\n";
            break;
        }
    } while (opcion != 5);

    return 0;
}
