/*
-------------------------------------------------------------------------------------------------------
Tarea: #6 - Tablas Hash para IDs
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
    Dados los IDs de la clase. asignar un indice a cada ID,
    utilizando una funcion HASH [que este en notacion Big O(1)], un Indice o Asiento a cada ID dado.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 21/Jun/2025

*/

#include <iostream>
#include <iomanip>

using namespace std;

const int NUM_ESTUDIANTES = 30;

int idsClase[NUM_ESTUDIANTES] = {
    1124396, 1126338, 1118197, 1127166, 1123657,
    1129672, 1124404, 1127310, 1120392, 1127175,
    1126027, 1124633, 1119634, 1122786, 1118021,
    1127085, 1124963, 1125467, 1121623, 1126920,
    1128966, 1126402, 1125691, 1121235, 1127227,
    1126396, 1126385, 1125701, 1126328, 1128066
};

#pragma region Validaciones

// Validar entrada de entero
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
                cout << "ERROR: Entrada invalida. Solo numeros enteros." << endl;
                cout << "Intente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else {
            cout << "ERROR: Entrada invalida. Solo numeros enteros." << endl;
            cout << "Intente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return valor;
}

// Validar opción del menú
int validarOpcionMenu() {

    int opcion;
    bool valida = false;

    while (!valida) {
        opcion = validarEntero("");
        if (opcion >= 1 && opcion <= 3) {
            valida = true;
        }
        else {
            cout << "ERROR: Opcion invalida. Debe seleccionar entre 1-3." << endl;
            cout << "Seleccione una opcion: ";
        }
    }
    return opcion;
}

// Solicitar ID sin restricciones específicas
int solicitarID() {

    return validarEntero("Ingrese el ID a buscar: ");
}

#pragma endregion

int funcionHash(int id) {

    int suma = 0;
    int temp = id;

    //Sumar todos los dígitos
    while (temp > 0) {
        suma += temp % 10;
        temp /= 10;
    }

    //Aplicar modulo
    return suma % NUM_ESTUDIANTES;
}

void mostrarCalculoDetallado(int id) {

    cout << "ID: " << id << " -> ";

    int temp = id;
    int suma = 0;

    // Mostrar cada digito sumandose
    cout << "Suma: ";

    bool primero = true;

    while (temp > 0) {

        int digito = temp % 10;
        suma += digito;

        if (!primero) {
            cout << " + ";
        }

        cout << digito;
        temp /= 10;
        primero = false;
    }

    int indice = suma % NUM_ESTUDIANTES;
    cout << " = " << suma;
    cout << " mod " << NUM_ESTUDIANTES;
    cout << " = " << indice << endl;
}

//Colisiones verif.
void verificarColisiones() {

    bool colisiones[NUM_ESTUDIANTES] = { false };
    int totalColisiones = 0;

    cout << "\n=== VERIFICACION DE COLISIONES ===" << endl;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        int indice = funcionHash(idsClase[i]);

        if (colisiones[indice]) {
            cout << "COLISION: ID " << idsClase[i]
                << " -> Indice " << indice << " (ya ocupado)" << endl;
            totalColisiones++;
        }
        else {
            colisiones[indice] = true;
        }
    }

    if (totalColisiones == 0) {
        cout << "PERFECTO! No hay colisiones - Funcion hash optima" << endl;
    }
    else {
        cout << "Total de colisiones: " << totalColisiones << endl;
        cout << "Eficiencia: " << ((NUM_ESTUDIANTES - totalColisiones) * 100 / NUM_ESTUDIANTES) << "%" << endl;
    }
}

void presentar() {

    cout << "\n=============================================================" << endl;
    cout << "              ASIGNACION DE INDICES CON FUNCION HASH        " << endl;
    cout << "=============================================================" << endl;

    cout << "\nTABLA COMPLETA DE ASIGNACIONES:" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << left << setw(12) << "Estudiante"
        << setw(12) << "ID"
        << setw(15) << "Suma Digitos"
        << setw(10) << "Indice" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        int id = idsClase[i];
        int suma = 0;
        int temp = id;

        // Calcular suma para mostrar
        while (temp > 0) {
            suma += temp % 10;
            temp /= 10;
        }

        int indice = funcionHash(id);

        cout << left << setw(12) << (i + 1)
            << setw(12) << id
            << setw(15) << suma
            << setw(10) << indice << endl;
    }

    verificarColisiones();
}

//Buscar ID especifico con validaciones
void buscarID() {

    int idBuscado = solicitarID();

    // Buscar si el ID existe en la clase
    bool encontrado = false;
    int posicion = -1;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        if (idsClase[i] == idBuscado) {
            encontrado = true;
            posicion = i + 1;
            break;
        }
    }

    cout << "\n=== RESULTADO DE BUSQUEDA ===" << endl;
    if (encontrado) {

        int indice = funcionHash(idBuscado);

        cout << "ID ENCONTRADO:" << endl;
        cout << "   Estudiante #" << posicion << endl;
        cout << "   ID: " << idBuscado << endl;
        cout << "   Indice asignado: " << indice << endl;
        cout << "   Calculo detallado: ";
        mostrarCalculoDetallado(idBuscado);
    }
    else {
        cout << "ID no encontrado en la clase actual" << endl;
        cout << "   Pero el indice seria: " << funcionHash(idBuscado) << endl;
        cout << "   Calculo detallado: ";
        mostrarCalculoDetallado(idBuscado);
    }
}

#pragma region Main

int main() {

    int opcion;

    do {
        cout << "\n=============================================================" << endl;
        cout << "              FUNCION HASH:  ASIGNACION DE INDICES            " << endl;
        cout << "=============================================================" << endl;

        cout << "\nMENU DE OPCIONES:" << endl;
        cout << "1.  Ver Indices" << endl;
        cout << "2.  Buscar ID especifico" << endl;
        cout << "3.  Salir" << endl;
        cout << "============================================================" << endl;
        cout << "+ Seleccione una opcion: ";

        opcion = validarOpcionMenu();

        switch (opcion) {

        case 1:
            presentar();
            break;

        case 2:
            buscarID();
            break;

        case 3:
            cout << "Programa terminado exitosamente." << endl;
            break;

        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }

        if (opcion != 3) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 3);

    return 0;
}

#pragma endregion
