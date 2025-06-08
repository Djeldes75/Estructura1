/*
-------------------------------------------------------------------------------------
TAREA: Implementación de una Lista Enlazada (Linked List) en C++
-------------------------------------------------------------------------------------

#include <iostream> // Biblioteca estándar para entrada y salida en C++
#include <string>   // Biblioteca estándar para manipulación de cadenas
using namespace std; // Permite el uso del espacio de nombres estándar para evitar escribir std:: antes de cada función

// Definición de la estructura de un nodo en la lista enlazada
struct LinkedList {
    int dato;           // Variable que almacena el valor del nodo
    LinkedList* next;   // Puntero que apunta al siguiente nodo en la lista
};

// Declaraciones explícitas de funciones utilizadas en el programa
bool IsEmpty(LinkedList*);        // Función que verifica si la lista está vacía
void ClearList(LinkedList*&);     // Función que elimina todos los nodos de la lista y libera memoria
void InsertNode(LinkedList*&, int); // Función que inserta un nodo en la lista enlazada de manera ordenada
void SearchNode(LinkedList*);     // Función que busca un nodo en la lista enlazada
void DeleteNode(LinkedList*&);    // Función que elimina un nodo de la lista enlazada
void DisplayList(LinkedList*);    // Función que muestra todos los nodos de la lista enlazada
void Menu();                      // Función que muestra el menú de opciones al usuario


// Función para verificar si la lista está vacía
bool IsEmpty(LinkedList* head) {
    return head == nullptr; // Retorna true si el puntero a la cabeza es nullptr, indicando que la lista está vacía
}

// Función para liberar toda la memoria de la lista
void ClearList(LinkedList*& head) {
    while (head != nullptr) { // Mientras la lista no esté vacía
        LinkedList* temp = head; // Guarda el puntero del nodo actual en una variable temporal
        head = head->next; // Mueve la cabeza de la lista al siguiente nodo
        delete temp; // Libera la memoria del nodo eliminado
    }
}

// Función para insertar un nodo en la lista enlazada de manera ordenada
void InsertNode(LinkedList*& head, int dato) {
    LinkedList* nuevo = new LinkedList(); // Se crea un nuevo nodo en memoria dinámica
    nuevo->dato = dato; // Se asigna el valor ingresado al nodo
    nuevo->next = nullptr; // Inicialmente, el nuevo nodo no apunta a ningún otro nodo

    // Si la lista está vacía o el primer nodo tiene un valor mayor o igual al nuevo nodo
    if (IsEmpty(head) || head->dato >= dato) {
        nuevo->next = head; // Se enlaza el nuevo nodo con la lista existente
        head = nuevo; // Se actualiza la cabeza para que apunte al nuevo nodo
    }
    else {
        LinkedList* temp = head; // Se declara un nodo auxiliar para recorrer la lista
        // Se avanza mientras el siguiente nodo sea menor al dato a insertar
        while (temp->next != nullptr && temp->next->dato < dato) {
            temp = temp->next; // Se mueve al siguiente nodo
        }
        nuevo->next = temp->next; // Se enlaza el nuevo nodo con el siguiente nodo en la lista
        temp->next = nuevo; // Se enlaza el nodo actual con el nuevo nodo
    }
    cout << "Nodo con valor " << dato << " insertado exitosamente.\n"; // Mensaje de confirmación
}


// Función para buscar un nodo en la lista enlazada
void SearchNode(LinkedList* head) {
    if (IsEmpty(head)) { // Verifica si la lista está vacía antes de buscar
        cout << "La lista esta vacia. No se puede buscar un nodo.\n";
        return; // Sale de la función si la lista está vacía
    }

    int dato; // Variable para almacenar el valor a buscar
    cout << "Ingrese el valor del nodo a buscar: ";

    // Validación de entrada para asegurarse de que el usuario introduce un número válido
    while (!(cin >> dato)) {
        cin.clear(); // Limpia cualquier error de entr ada
        cin.ignore(1000, '\n'); // Ignora caracteres inválidos
        cout << "Entrada no valida. Intente nuevamente: ";
    }

    LinkedList* temp = head; // Nodo auxiliar para recorrer la lista  
    int posicion = 0; // Variable para almacenar la posición del nodo
    bool encontrado = false; // Bandera para indicar si el nodo fue encontrado
    string posiciones; // Variable para almacenar todas las posiciones donde se encuentra el nodo

    // Se recorre la lista enlazada hasta llegar al final (nullptr)
    while (temp != nullptr) {
        if (temp->dato == dato) { // Si se encuentra el nodo con el valor buscado
            encontrado = true; // Se marca como encontrado
            if (posiciones.empty()) { // Si es la primera coincidencia
                posiciones += to_string(posicion); // Se almacena la posición
            }
            else {
                posiciones += ", " + to_string(posicion); // Se agregan más posiciones separadas por coma
            }
        }
        temp = temp->next; // Se avanza al siguiente nodo en la lista
        posicion++; // Se incrementa la posición actual
    }

    if (encontrado) { // Si al menos un nodo con el valor fue encontrado
        cout << "Nodos con valor " << dato << " encontrados en las posicion(es): " << posiciones << ".\n";
    }
    else { // Si no se encontró ningún nodo con el valor
        cout << "Nodo con valor " << dato << " no encontrado en la lista.\n";
    }
}
// Función para eliminar un nodo de la lista enlazada
void DeleteNode(LinkedList*& head) {
    // Verificar si la lista está vacía antes de intentar eliminar un nodo
    if (IsEmpty(head)) {
        cout << "La lista está vacía. No se puede eliminar un nodo.\n";
        return;
    }

    int dato; // Variable para almacenar el valor del nodo a eliminar
    cout << "Ingrese el valor del nodo a eliminar: ";
    while (!(cin >> dato)) { // Validar la entrada para asegurarse de que sea un número
        cin.clear(); // Limpia el estado de error del buffer de entrada
        cin.ignore(1000, '\n'); // Ignora cualquier entrada incorrecta hasta el siguiente salto de línea
        cout << "Entrada no válida. Intente nuevamente: "; // Mensaje de error
    }

    // Recorrer la lista para encontrar las posiciones del nodo a eliminar
    LinkedList* temp = head;    // Puntero auxiliar para recorrer la lista
    int posicion = 0; // Variable que almacena la posición del nodo en la lista
    bool encontrado = false; // Bandera que indica si el nodo fue encontrado
    string posiciones; // Cadena para almacenar todas las posiciones en las que se encuentra el nodo
        while (temp != nullptr) { // Se recorre la lista hasta llegar al final
            if (temp->dato == dato) { // Si se encuentra un nodo con el valor buscado
                encontrado = true; // Se marca que el nodo fue encontrado
                if (posiciones.empty()) { // Si es la primera coincidencia
                    posiciones += to_string(posicion); // Se almacena la posición
                }
                else {
                    posiciones += ", " + to_string(posicion); // Se agregan más posiciones separadas por coma
                }
            }
            temp = temp->next; // Avanza al siguiente nodo en la lista
            posicion++; // Se incrementa la posición actual
        }

    // Si el nodo no se encuentra en la lista, se muestra un mensaje y se finaliza la función
    if (!encontrado) {
        cout << "Nodo con valor " << dato << " no encontrado en la lista.\n";
        return;
    }

    // Si solo hay una ocurrencia del nodo, se elimina directamente sin preguntar
    if (posiciones.find(",") == string::npos) { // Se verifica si solo hay una ocurrencia del nodo buscando una coma en la cadena de posiciones
        cout << "Nodo con valor " << dato << " encontrado en la posición: " << posiciones << ".\n";
        cout << "Eliminando el nodo directamente...\n"; // Mensaje indicando que se procederá a eliminar el nodo

        temp = head; // Se inicializa el puntero temp en la cabeza de la lista
        LinkedList* prev = nullptr; // Puntero auxiliar para mantener la referencia al nodo anterior
        int posEliminar = stoi(posiciones); // Se convierte la posición encontrada de string a entero
        int currentPos = 0; // Contador para recorrer la lista hasta la posición deseada

        while (temp != nullptr && currentPos < posEliminar) { // Se recorre la lista hasta encontrar la posición correcta
            prev = temp; // Se guarda la referencia del nodo anterior al actual
            temp = temp->next; // Se avanza al siguiente nodo
            currentPos++; // Se incrementa el contador de posición
        }

        if (prev == nullptr) { // Si el nodo a eliminar es el primero de la lista
            head = temp->next; // Se actualiza la cabeza de la lista al siguiente nodo
        }
        else {
            prev->next = temp->next; // Se enlaza el nodo anterior con el siguiente, omitiendo el nodo a eliminar
        }

        delete temp; // Se libera la memoria del nodo eliminado
        cout << "Nodo eliminado exitosamente.\n"; // Mensaje de confirmación
        return; // Se termina la función
    }

    // Si hay múltiples ocurrencias, se presenta un menú de opciones al usuario
    cout << "Nodos con valor " << dato << " encontrados en las posiciones: " << posiciones << ".\n";
    cout << "Seleccione una opción:\n";
    cout << "1. Eliminar una ocurrencia específica (ingrese la posición)\n";
    cout << "2. Eliminar todas las ocurrencias\n";
    cout << "Opción: ";

    int opcion; // Variable que almacena la opción elegida por el usuario

    // Bucle para validar la entrada del usuario
    // Se asegura de que el usuario ingrese un número válido (1 o 2)
    while (!(cin >> opcion) || (opcion != 1 && opcion != 2)) {
        cin.clear(); // Limpia el estado de error de cin en caso de entrada inválida
        cin.ignore(1000, '\n'); // Ignora hasta 1000 caracteres o hasta encontrar un salto de línea para evitar bucles infinitos
        cout << "Opción no válida. Debe ser 1 o 2. Intente nuevamente: "; // Mensaje de error indicando que la entrada no es válida
    }


    // Opción 1: Eliminar una única ocurrencia específica
    if (opcion == 1) {
        int posEliminar; // Variable que almacena la posición ingresada por el usuario
        cout << "Ingrese la posición a eliminar: ";// Se solicita la posición del nodo a eliminar

        // Validación de entrada para asegurarse de que el usuario ingresa un número válido
        while (!(cin >> posEliminar) || posEliminar < 0) {
            cin.clear(); // Limpia errores de entrada en caso de datos no numéricos
            cin.ignore(1000, '\n'); // Ignora cualquier carácter no válido hasta la siguiente línea
            cout << "Posición no válida. Debe ser un número no negativo. Intente nuevamente: "; // Mensaje de error
        }

        temp = head; // Se reinicia el puntero temp a la cabeza de la lista
        LinkedList* prev = nullptr; // Puntero para almacenar el nodo anterior al que se eliminará
        int currentPos = 0; // Contador de posición en la lista

        // Se recorre la lista hasta encontrar la posición deseada
        while (temp != nullptr && currentPos < posEliminar) {
            prev = temp; // Se almacena el nodo anterior
            temp = temp->next; // Se avanza al siguiente nodo
            currentPos++; // Se incrementa la posición actual
        }

        // Si el nodo a eliminar no es el esperado o la posición ingresada no es válida, se muestra un mensaje de error
        if (temp == nullptr || temp->dato != dato) {
            cout << "Posición " << posEliminar << " no contiene el valor " << dato << ".\n";
            return;
        }
        // Eliminación del nodo en la posición indicada
        if (prev == nullptr) { // Si el nodo a eliminar es el primero de la lista
            head = temp->next; // Se actualiza la cabeza de la lista al siguiente nodo
        }
        else { // Si el nodo a eliminar no es el primero
            prev->next = temp->next; // Se enlaza el nodo anterior con el siguiente, omitiendo el nodo a eliminar
        }
        delete temp; // Se libera la memoria del nodo eliminado
        cout << "Nodo en la posición " << posEliminar << " eliminado correctamente.\n"; // Mensaje de confirmación
    }
    // Opción 2: Eliminar todas las ocurrencias del nodo con el valor indicado
    else if (opcion == 2) {
        temp = head; // Se reinicia temp para recorrer la lista
        LinkedList* prev = nullptr; // Puntero para almacenar el nodo anterior
        bool eliminado = false; // Bandera para indicar si se eliminó al menos un nodo

        // Se recorre la lista enlazada en busca de todas las ocurrencias del valor ingresado
        while (temp != nullptr) {
            if (temp->dato == dato) { // Si el nodo actual contiene el valor a eliminar
                if (temp == head) { // Si el nodo a eliminar es el primero
                    head = temp->next; // Se actualiza la cabeza al siguiente nodo
                    delete temp; // Se elimina el nodo actual
                    temp = head; // Se actualiza temp para continuar la búsqueda
                }
                else { // Si el nodo a eliminar no es el primero
                    prev->next = temp->next; // Se enlaza el nodo anterior con el siguiente, omitiendo el nodo actual
                    delete temp; // Se elimina el nodo actual
                    temp = prev->next; // Se actualiza temp para continuar la búsqueda
                }
                eliminado = true; // Se marca que se ha eliminado al menos un nodo
            }
            else { // Si el nodo actual no es el que se busca eliminar
                prev = temp; // Se almacena el nodo actual como nodo anterior
                temp = temp->next; // Se avanza al siguiente nodo
            }
        }

        // Mensajes de salida según si se eliminaron nodos o no
        if (eliminado) {
            cout << "Todas las ocurrencias del nodo con valor " << dato << " eliminadas.\n"; // Mensaje de éxito
        }
        else {
            cout << "No se eliminaron nodos.\n"; // Mensaje en caso de que no se haya encontrado el nodo a eliminar
        }
    }

}


// Función para mostrar todos los nodos de la lista enlazada
void DisplayList(LinkedList* head) { // Se recibe un puntero al primer nodo de la lista
    if (IsEmpty(head)) { // Verifica si la lista está vacía antes de mostrar su contenido
        cout << "La lista esta vacia.\n"; // Mensaje si la lista no contiene nodos
        return; // Sale de la función
    }
    LinkedList* temp = head; // Nodo auxiliar para recorrer la lista desde la cabeza
    cout << "Contenido de la lista enlazada: "; // Mensaje previo a la impresión de los valores
    // Se recorre la lista e imprime cada nodo
    while (temp != nullptr) { // Mientras no se llegue al final de la lista (nullptr)
        cout << temp->dato << " "; // Imprime el valor del nodo actual seguido de un espacio
        temp = temp->next; // Avanza al siguiente nodo en la lista
    }
    cout << endl; // Salto de línea después de mostrar todos los valores
}
// Función para mostrar el menú y manejar las opciones del usuario
void Menu() {
    LinkedList* head = nullptr; // Se inicializa la lista enlazada vacía
    int opcion; // Variable para almacenar la opción ingresada por el usuario
    do {
        // Imprime el menú en la consola
        cout << "\n=========================\n";
        cout << "  MENU DE OPERACIONES\n";
        cout << "=========================\n";
        cout << "1. Insertar nodo\n";
        cout << "2. Buscar nodo\n";
        cout << "3. Eliminar nodo\n";
        cout << "4. Mostrar lista enlazada\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        // Validación de entrada para asegurar que el usuario ingrese un número válido entre 1 y 5
        if (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cin.clear(); // Limpia el estado de error del buffer de entrada
            cin.ignore(1000, '\n'); // Ignora cualquier entrada incorrecta hasta el siguiente salto de línea
            cout << "Opción no válida. Debe ser un número entre 1 y 5.\n";
            continue; // Vuelve a mostrar el menú
        }
        cin.ignore(1000, '\n'); // Limpiar el buffer después de leer la opción
        // Estructura switch para manejar la opción seleccionada por el usuario
        switch (opcion) {
        case 1: { // Caso 1: Insertar un nodo en la lista
            int dato; // Variable para almacenar el valor del nodo a insertar
            bool entradaValida = false; // Bandera para validar la entrada del usuario
            while (!entradaValida) { // Ciclo para validar el dato ingresado por el usuario
                cout << "Ingrese el valor del nodo: "; // Pide el dato al usuario
                if (cin >> dato) { // Verifica si la entrada es un número válido
                    // Verificar si el número es negativo
                    if (dato < 0) {
                        cout << "Entrada no válida. Debe ser un número entero positivo sin letras ni signos.\n";
                        cin.ignore(1000, '\n'); // Limpia el buffer de entrada
                        continue;
                    }
                    // Verificar si hay caracteres no numéricos después del número
                    int nextChar = cin.peek(); // Verifica el siguiente carácter en el buffer
                    if (nextChar != '\n' && nextChar != EOF) { // Si hay caracteres adicionales no numéricos
                        cout << "Entrada no válida. Debe ser un número entero positivo sin letras ni signos.\n";
                        cin.ignore(1000, '\n'); // Limpia el buffer
                        continue;
                    }
                    cin.ignore(1000, '\n'); // Limpiar el salto de línea
                    entradaValida = true; // Marca la entrada como válida
                }
                else { // Si la entrada no es válida
                    cout << "Entrada no válida. Debe ser un número entero positivo sin letras ni signos.\n";
                    cin.clear(); // Limpia el error de cin
                    cin.ignore(1000, '\n'); // Limpia el buffer de entrada
                }
            }
            InsertNode(head, dato); // Llama a la función para insertar un nodo en la lista enlazada
            break;
        }
        case 2:
            SearchNode(head); // Llama a la función para buscar un nodo en la lista enlazada
            break;
        case 3:
            DeleteNode(head); // Llama a la función para eliminar un nodo en la lista enlazada
            break;
        case 4:
            DisplayList(head); // Llama a la función para mostrar todos los nodos de la lista enlazada
            break;
        case 5:
            cout << "Saliendo del programa...\n"; // Mensaje de salida
            ClearList(head); // Libera la memoria antes de salir para evitar fugas de memoria
            break;
        }
    } while (opcion != 5); // El menú se repetirá hasta que el usuario elija la opción de salir
}
// Función principal, punto de entrada del programa
int main() {
    Menu(); // Llama a la función del menú para que el usuario pueda interactuar con la lista enlazada
    return 0; // Indica que el programa finalizó correctamente y devuelve 0 al sistema operativo
}