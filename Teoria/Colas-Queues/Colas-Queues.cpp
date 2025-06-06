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

    E. El programas debe ser lo suficientemente especializado para informar al usuario cuando la cola esta
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
    Queue* next;   // Puntero al siguiente nodo en la cola
};

// Array de 17 punteros a Queue que representa las colas de diferentes prioridades.
Queue* colas[17];



#pragma region Func. Auxi.

//Recorre e inicializa las 17(16) colas, y las inicia vacias
void inicializar() {
    for (int i = 0; i < 17; i++) {
        colas[i] = nullptr;
    }
}

// Verifica si todas las colas de prioridad están vacías. Agarra y recorre todas las colas, y retorna false si encuentra alguna con elementos.
bool estaVacia() {
    for (int i = 0; i < 17; i++) {
        if (colas[i] != nullptr) return false;
    }
    return true;
}

//Numero que el usuario ingresa
int pedirNumero() {

    double numero;
    int numeroEntero;

    cout << "Ingrese un numero: ";

    while (true) {
        if (cin >> numero) {

            //Compara el numero(double) con su parte entera, si mismo
            if (numero == (int)numero) {
                //Si el numero no tiene decimales, lo convierte en ENTERO y lo guarda
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

//PRIORIDAD
int pedirPrioridad() {

    double prioridad;
    int numeroPrioridad;

    cout << "Ingrese la prioridad [ 0 (Alta) - 16 (Baja) ]: ";

    while (true) {

        if (cin >> prioridad) {

            if (prioridad == (int)prioridad) {
                numeroPrioridad = (int)prioridad;

                // Validar rango
                if (numeroPrioridad >= 0 && numeroPrioridad <= 16) {
                    break;
                }
                else {
                    cout << "ERROR: La prioridad debe estar entre 0 y 16." << endl;
                }
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
        cout << "\nVuelva a ingresar la prioridad: ";
    }

    return numeroPrioridad;
}

#pragma endregion

#pragma region OPERACIONES PRINCIPALES

//Función enqueue() simplificada
void enqueue() {

    Queue* nuevo = new Queue;

    nuevo->dato = pedirNumero();
    int prioridad = pedirPrioridad();

    nuevo->next = nullptr;

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

    cout << "\n{Dato: " << nuevo->dato << "} - " << "{Prioridad: " << prioridad << "}\n\n";
}


/// Busca la primera cola no vacía (menor índice = mayor prioridad) y elimina su primer elemento.
void dequeue() {

    if (estaVacia()) {
        cout << "Cola vacia.\n\n";
        return;
    }

    // Buscar la primera cola con elementos (mayor prioridad)
    for (int i = 0; i < 17; i++) {

        if (colas[i] != nullptr) {

            Queue* temp = colas[i];

            cout << "\nEliminado: " << temp->dato << " (Prioridad " << i << ")\n";

            //Next
            colas[i] = colas[i]->next;

            delete temp;
            return;
        }
    }
}

#pragma endregion

#pragma region Mostrar y Vaciar Queues(Colas)

/// Muestra todos los elementos de todas las colas organizados por prioridad.
void mostrar() {

    // Verificar si hay elementos que mostrar
    if (estaVacia()) {
        cout << "Cola vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA COLA ===\n";
    int contador = 1;  // Numeración secuencial de elementos

    // Recorrer todas las colas de prioridad
    for (int i = 0; i < 17; i++) {

        Queue* temp = colas[i];  // Puntero temporal para recorrer la cola

        // Recorrer todos los nodos de esta cola específica
        while (temp != nullptr) {

            cout << contador << ". Dato: " << temp->dato << " | Prioridad: " << i << "\n";
            temp = temp->next;  // Avanzar al siguiente nodo
            contador++;
        }
    }
    cout << "============================\n\n";
}

/// Vacía completamente todas las colas eliminando todos los elementos en orden de prioridad.
void vaciarTodo() {
    // Verificar si hay elementos que eliminar
    if (estaVacia()) {
        cout << "Cola vacia.\n\n";
        return;
    }

    cout << "\n=== VACIANDO COLA COMPLETA ===\n";
    int contador = 1;

    // Continuar eliminando hasta que todas las colas estén vacías
    while (!estaVacia()) {

        // Buscar la primera cola con elementos (mayor prioridad)
        for (int i = 0; i < 17; i++) {

            if (colas[i] != nullptr) {

                cout << contador << ". Eliminando: " << colas[i]->dato << " (Prioridad " << i << ")\n";

                // Guardar referencia al nodo a eliminar
                Queue* temp = colas[i];

                // Actualizar puntero de la cola
                colas[i] = colas[i]->next;

                delete temp;

                contador++;
                break;       // Salir del for para buscar el siguiente elemento de mayor prioridad
            }
        }
    }
    cout << "\nCola completamente vacia.\n\n";
}

#pragma endregion

#pragma region MENU

void menu() {
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

//Función pedirOpcion() corregida (quitar cin.ignore extra)
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

#pragma endregion

#pragma region MAIN

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

            //Limpia la memory por que no esta de grati'
            for (int i = 0; i < 17; i++) {

                while (colas[i] != nullptr) {

                    Queue* temp = colas[i];

                    colas[i] = colas[i]->next;

                    delete temp;
                }
            }
            break;

        default:
            cout << "ERROR: Opcion invalida. Intente de nuevamente.\n\n";
        }

    } while (opcion != 5);

    return 0;
}

#pragma endregion