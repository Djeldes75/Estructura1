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

#pragma region Funciones Auxiliares

//Inicializar Array de Colas
void inicializar() {
    for (int i = 0; i < 17; i++) {
        colas[i] = nullptr;
    }
}
//Fin de Func. inicializar

//Verificar si Todas las Colas Estan Vacias
bool estaVacia() {
    for (int i = 0; i < 17; i++) {
        if (colas[i] != nullptr) return false;
    }
    return true;
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

//Validar Input del Usuario - Prioridad
int pedirPrioridad() {

    double prioridad;
    int numeroPrioridad;

    cout << "Ingrese la prioridad [ 0 (Alta) - 16 (Baja) ]: ";

    while (true) {

        if (cin >> prioridad) {

            if (prioridad == (int)prioridad) {
                numeroPrioridad = (int)prioridad;

                //Validar que la prioridad este en el rango correcto
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
//Fin de Func. pedirPrioridad

#pragma endregion

#pragma region Engueue y Dequeue

//Insertar Elemento en Cola con Prioridad
void enqueue() {

    Queue* nuevo = new Queue;

    nuevo->dato = pedirNumero();

    int prioridad = pedirPrioridad();

    nuevo->next = nullptr;

    //Si la cola de esta prioridad esta vacia
    if (colas[prioridad] == nullptr) {
        colas[prioridad] = nuevo;
    }
    else {
        //Buscar el final de la cola para insertar (FIFO)
        Queue* temp = colas[prioridad];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nuevo;
    }

    cout << "\n{Dato: " << nuevo->dato << "} - " << "{Prioridad: " << prioridad << "}\n\n";
}
//Fin de Func. Enqueue

//Eliminar Elemento de Mayor Prioridad
void dequeue() {

    if (estaVacia()) {

        cout << "Cola vacia.\n\n";
        return;
    }

    //Buscar la primera cola con elementos (indice menor = mayor prioridad)
    for (int i = 0; i < 17; i++) {

        if (colas[i] != nullptr) {

            Queue* temp = colas[i];

            cout << "\nEliminado: " << temp->dato << " (Prioridad " << i << ")\n";

            //Actualizar puntero de la cola
            colas[i] = colas[i]->next;

            delete temp;
            return;
        }
    }
}
//Fin de Func. dequeue

#pragma endregion

#pragma region Mostrar y Vaciar Queues(Colas)

//Mostrar Todos los Elementos por Prioridad
void mostrar() {

    if (estaVacia()) {

        cout << "Cola vacia.\n\n";
        return;
    }

    cout << "\n=== CONTENIDO DE LA COLA ===\n";
    int contador = 1;

    //Recorrer todas las colas desde la mayor prioridad (0) hasta la menor (16)
    for (int i = 0; i < 17; i++) {

        Queue* temp = colas[i];

        //Recorrer todos los nodos de esta cola especifica
        while (temp != nullptr) {

            cout << contador << ". Dato: " << temp->dato << " | Prioridad: " << i << "\n";
            temp = temp->next;
            contador++;
        }
    }
    cout << "============================\n\n";
}
//Fin de Func. mostrar

//Vaciar Completamente Todas las Colas
void vaciarTodo() {

    if (estaVacia()) {
        cout << "Cola vacia.\n\n";
        return;
    }

    cout << "\n=== VACIANDO COLA COMPLETA ===\n";
    int contador = 1;

    //Eliminar elementos respetando prioridad hasta que todo este vacio
    while (!estaVacia()) {

        //Buscar la primera cola con elementos (mayor prioridad)
        for (int i = 0; i < 17; i++) {

            if (colas[i] != nullptr) {

                cout << contador << ". Eliminando: " << colas[i]->dato << " (Prioridad " << i << ")\n";

                Queue* temp = colas[i];
                colas[i] = colas[i]->next;

                delete temp;

                contador++;
                break;       // Salir del for para buscar el siguiente elemento de mayor prioridad
            }
        }
    }
    cout << "\nCola completamente vacia.\n\n";
}
//Fin de Func. vaciarTodo

#pragma endregion

#pragma region MENU

//Mostrar Menu Principal
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