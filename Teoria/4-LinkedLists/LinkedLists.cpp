/*
-------------------------------------------------------------------------------------------------------
Tarea: #4 - Lista Enlazada (Linked List)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I (6-8pm)
-------------------------------------------------------------------------------------------------------
Una Lista Enlazada (Linked List) es una estructura de datos en donde cada nodo apunta a uno siguiente
y de esta manera se mantiene un enlace entre los nodos. Para nuestro caso, haremos el problema un poco
más real exigiendo que al insertar cada nodo, este se inserte de manera ordenada (ascendente) de modo
que los nodos se indexen según su dato. La Lista Enlazada (Linked List) tiene la siguiente forma
para los nodos:

struct LinkedList {
 int dato;
 LinkedList *next;
};

RESTRICCIONES:
    A. La Lista Enlazada (Linked List) debe poder realizar las operaciones Insertar, Buscar,
       Eliminar y Mostrar la Lista Enlazada.

    B. Al insertar un nuevo nodo el programa debe contemplar realizar la inserción del nodo donde le
       corresponda, ya que la lista debe estar ordenada en forma ascendente según su dato.

    C. El programa deberá tener un menú con las opciones para Insertar, Buscar, Eliminar y
       Mostrar la Lista Enlazada y Salir.

    D. Las entradas de datos del usuario deben ser debidamente validas.

    E. El programa debe ser lo suficientemente especializado para informar al usuario cuando la
       Lista Enlazada (Linked List) está vacía.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 5/Diciembre/2022

*/

