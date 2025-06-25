#include <iostream>
#include <iomanip>
using namespace std;

const int NUM_ESTUDIANTES = 30;
const int TABLA_SIZE = 61;

int idsClase[NUM_ESTUDIANTES] = {
    1124396, 1126338, 1118197, 1127166, 1123657,
    1129672, 1124404, 1127310, 1120392, 1127175,
    1126027, 1124633, 1119634, 1122786, 1118021,
    1127085, 1124963, 1125467, 1121623, 1126920,
    1128966, 1126402, 1125691, 1121235, 1127227,
    1126396, 1126385, 1125701, 1126328, 1128066
};

struct SlotTabla {
    int id;
    int numeroEstudiante;
    bool ocupado;
    
    SlotTabla() : id(0), numeroEstudiante(0), ocupado(false) {}
};

SlotTabla tablaHash[TABLA_SIZE];

int funcionHashSimple(int id) {
    int ultimosDosDigitos = id % 100;
    int multiplicado = ultimosDosDigitos * 3;
    int indice = multiplicado % TABLA_SIZE;
    return indice;
}

bool insertarID(int id, int numeroEstudiante) {
    int indice = funcionHashSimple(id);
    int indiceOriginal = indice;
    int intentos = 0;
    
    while (tablaHash[indice].ocupado) {
        intentos++;
        indice = (indice + 1) % TABLA_SIZE;
        
        if (indice == indiceOriginal) {
            return false;
        }
    }
    
    tablaHash[indice].id = id;
    tablaHash[indice].numeroEstudiante = numeroEstudiante;
    tablaHash[indice].ocupado = true;
    
    return true;
}

void inicializarTabla() {
    for (int i = 0; i < TABLA_SIZE; i++) {
        tablaHash[i] = SlotTabla();
    }
}

void llenarTabla() {
    inicializarTabla();
    
    for (int i = 0; i < NUM_ESTUDIANTES; i++) {
        insertarID(idsClase[i], i + 1);
    }
}

void mostrarTablaCompleta() {
    cout << "| Indice |    ID     | Estudiante |  Estado  |" << endl;
    cout << "|--------|-----------|------------|----------|" << endl;
    
    for (int i = 0; i < TABLA_SIZE; i++) {
        cout << "| " << setw(6) << i << " | ";
        
        if (tablaHash[i].ocupado) {
            cout << setw(9) << tablaHash[i].id << " | ";
            cout << "    E-" << setw(2) << tablaHash[i].numeroEstudiante << "   | ";
            cout << " OCUPADO  |";
        } else {
            cout << "    ---   |     ---    |   LIBRE  |";
        }
        cout << endl;
    }
}

bool buscarID(int idBuscado) {
    int indice = funcionHashSimple(idBuscado);
    int indiceOriginal = indice;
    
    do {
        if (!tablaHash[indice].ocupado) {
            return false;
        }
        
        if (tablaHash[indice].id == idBuscado) {
            cout << "ID encontrado en indice: " << indice << endl;
            cout << "Estudiante numero: " << tablaHash[indice].numeroEstudiante << endl;
            return true;
        }
        
        indice = (indice + 1) % TABLA_SIZE;
        
    } while (indice != indiceOriginal);
    
    return false;
}

void mostrarEstadisticas() {
    int ocupados = 0;
    int colisiones = 0;
    
    for (int i = 0; i < TABLA_SIZE; i++) {
        if (tablaHash[i].ocupado) {
            ocupados++;
            
            int posicionOriginal = funcionHashSimple(tablaHash[i].id);
            if (i != posicionOriginal) {
                colisiones++;
            }
        }
    }
    
    double factorCarga = (double)ocupados / TABLA_SIZE;
    
    cout << "Estadisticas:" << endl;
    cout << "Total estudiantes: " << NUM_ESTUDIANTES << endl;
    cout << "Slots ocupados: " << ocupados << endl;
    cout << "Colisiones: " << colisiones << endl;
    cout << "Factor de carga: " << factorCarga << endl;
}

int main() {
    int opcion;
    bool tablaLlena = false;
    
    do {
        cout << "\n1. Llenar tabla hash" << endl;
        cout << "2. Ver tabla completa" << endl;
        cout << "3. Buscar ID" << endl;
        cout << "4. Ver estadisticas" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                llenarTabla();
                tablaLlena = true;
                cout << "Tabla llenada correctamente" << endl;
                break;
                
            case 2:
                if (tablaLlena) {
                    mostrarTablaCompleta();
                } else {
                    cout << "Primero debe llenar la tabla" << endl;
                }
                break;
                
            case 3:
                if (tablaLlena) {
                    int idBuscado;
                    cout << "Ingrese ID a buscar: ";
                    cin >> idBuscado;
                    
                    if (!buscarID(idBuscado)) {
                        cout << "ID no encontrado" << endl;
                    }
                } else {
                    cout << "Primero debe llenar la tabla" << endl;
                }
                break;
                
            case 4:
                if (tablaLlena) {
                    mostrarEstadisticas();
                } else {
                    cout << "Primero debe llenar la tabla" << endl;
                }
                break;
                
            case 5:
                cout << "Programa terminado" << endl;
                break;
                
            default:
                cout << "Opcion invalida" << endl;
        }
        
    } while (opcion != 5);
    
    return 0;
}