/*
-------------------------------------------------------------------------------------------------------
Tarea: #6 - Tablas Hash para IDs (VERSION SIMPLE PARA PRINCIPIANTES)
Materia: IDS343-01-ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
    Asignar un indice a cada ID de la clase usando una funcion HASH simple
    que evite colisiones de manera facil de entender.

INTEGRANTES (Grupo 6):
    Samira Jaquez - 1125467
    Dominique Jeldes - 1121623
    Enmanuel Carrasco - 1124404
    Juan Castillo - 1127310
    Sebastian Ventura - 1128066
    Elianyer Gomez - 1118021

Fecha: 21/Jun/2025

COMPLEJIDAD TEMPORAL: O(1) promedio para insercion y busqueda
COMPLEJIDAD ESPACIAL: O(n) donde n es el tamaño de la tabla
*/

#include <iostream>
#include <iomanip>  // Para formatear la salida
using namespace std;

// ==================== CONFIGURACION ====================
const int NUM_ESTUDIANTES = 30;
const int TABLA_SIZE = 61; // Numero primo para mejor distribucion y menos colisiones

// Array con todos los IDs de la clase
int idsClase[NUM_ESTUDIANTES] = {
    1124396, 1126338, 1118197, 1127166, 1123657,
    1129672, 1124404, 1127310, 1120392, 1127175,
    1126027, 1124633, 1119634, 1122786, 1118021,
    1127085, 1124963, 1125467, 1121623, 1126920,
    1128966, 1126402, 1125691, 1121235, 1127227,
    1126396, 1126385, 1125701, 1126328, 1128066
};

// ==================== ESTRUCTURA DE LA TABLA HASH ====================
struct SlotTabla {
    int id;                 // ID del estudiante
    int numeroEstudiante;   // Numero de estudiante (1-30)
    bool ocupado;           // Si el slot esta ocupado
    
    // Constructor para inicializar
    SlotTabla() : id(0), numeroEstudiante(0), ocupado(false) {}
};

SlotTabla tablaHash[TABLA_SIZE];

// ==================== VALIDACIONES SIMPLES ====================
int pedirEntero(const string& mensaje) {
    int numero;
    cout << mensaje;
    while (!(cin >> numero)) {
        cout << "ERROR: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return numero;
}

int pedirOpcion() {
    int opcion;
    do {
        cout << "\nSeleccione una opcion (1-5): ";
        cin >> opcion;
        if (opcion < 1 || opcion > 5) {
            cout << "ERROR: Debe ser entre 1 y 5. Intente de nuevo." << endl;
        }
    } while (opcion < 1 || opcion > 5);
    return opcion;
}

// ==================== FUNCION HASH SIMPLE ====================
/* 
 * FUNCION HASH SIMPLE: 
 * 1. Toma los ultimos 2 digitos del ID
 * 2. Los multiplica por 3 (para mejor distribucion)
 * 3. Aplica modulo del tamaño de la tabla
 * 
 * COMPLEJIDAD: O(1) - Operaciones aritmeticas constantes
 */
int funcionHashSimple(int id) {
    int ultimosDosDigitos = id % 100;                          // Ej: 1124396 -> 96
    int multiplicado = ultimosDosDigitos * 3;                  // 96 * 3 = 288
    int indice = multiplicado % TABLA_SIZE;                    // 288 % 61 = 44
    return indice;
}

// Mostrar el calculo paso a paso (para fines educativos)
void mostrarCalculoPasoAPaso(int id) {
    int ultimosDosDigitos = id % 100;
    int multiplicado = ultimosDosDigitos * 3;
    int indice = multiplicado % TABLA_SIZE;
    
    cout << "\n┌─── CALCULO DE LA FUNCION HASH ───┐" << endl;
    cout << "│ ID: " << setw(34) << id << " │" << endl;
    cout << "│ Paso 1: Ultimos 2 digitos = " << setw(8) << ultimosDosDigitos << " │" << endl;
    cout << "│ Paso 2: Multiplicar por 3 = " << setw(9) << multiplicado << " │" << endl;
    cout << "│ Paso 3: Modulo " << TABLA_SIZE << " = " << setw(15) << indice << " │" << endl;
    cout << "│ RESULTADO: Indice = " << setw(16) << indice << " │" << endl;
    cout << "└──────────────────────────────────────┘" << endl;
}

// ==================== INSERCION CON LINEAR PROBING ====================
/*
 * INSERCION CON RESOLUCION DE COLISIONES (Linear Probing):
 * - Si el slot calculado esta libre, insertar ahi
 * - Si esta ocupado, buscar el siguiente slot libre secuencialmente
 * - Complejidad promedio: O(1), peor caso: O(n)
 */
bool insertarID(int id, int numeroEstudiante) {
    int indice = funcionHashSimple(id);
    int indiceOriginal = indice;
    int intentos = 0;
    
    cout << "  → Insertando ID " << id << " (Estudiante #" << numeroEstudiante << ")" << endl;
    cout << "  → Indice calculado: " << indice << endl;
    
    // Linear probing: buscar siguiente slot libre
    while (tablaHash[indice].ocupado) {
        intentos++;
        cout << "  ⚠️  COLISION en indice " << indice << " (ocupado por ID " 
             << tablaHash[indice].id << ")" << endl;
        
        indice = (indice + 1) % TABLA_SIZE;  // Circular: ir al siguiente
        
        // Verificar si la tabla esta llena (dimos la vuelta completa)
        if (indice == indiceOriginal) {
            cout << "  ❌ ERROR: Tabla llena, no se puede insertar!" << endl;
            return false;
        }
    }
    
    // Insertar en el slot libre encontrado
    tablaHash[indice].id = id;
    tablaHash[indice].numeroEstudiante = numeroEstudiante;
    tablaHash[indice].ocupado = true;
    
    if (intentos > 0) {
        cout << "  ✅ ID insertado en indice " << indice << " (tras " << intentos << " colisiones)" << endl;
    } else {
        cout << "  ✅ ID insertado en indice " << indice << " (sin colisiones)" << endl;
    }
    
    return true;
}

// ==================== INICIALIZACION Y LLENADO ====================
void inicializarTabla() {
    for (int i = 0; i < TABLA_SIZE; i++) {
        tablaHash[i] = SlotTabla(); // Usar constructor por defecto
    }
    cout << "✅ Tabla inicializada correctamente." << endl;
}

void llenarTabla() {
    cout << "\n" << string(50, '=') << endl;
    cout << "      LLENANDO LA TABLA HASH" << endl;
    cout << string(50, '=') << endl;
    
    inicializarTabla();
    
    int exitosas = 0;
    for (int i = 0; i < NUM_ESTUDIANTES; i++) {
        cout << "\n[" << (i + 1) << "/" << NUM_ESTUDIANTES << "] ";
        if (insertarID(idsClase[i], i + 1)) {
            exitosas++;
        }
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << "RESUMEN: " << exitosas << "/" << NUM_ESTUDIANTES << " IDs insertados exitosamente" << endl;
    cout << string(50, '=') << endl;
}

// ==================== VISUALIZACION DE LA TABLA ====================
void mostrarTablaCompleta() {
    cout << "\n" << string(70, '=') << endl;
    cout << "                    TABLA HASH COMPLETA" << endl;
    cout << string(70, '=') << endl;
    
    cout << "| Indice |    ID     | Estudiante |  Estado  | Hash Original |" << endl;
    cout << "|--------|-----------|------------|----------|---------------|" << endl;
    
    for (int i = 0; i < TABLA_SIZE; i++) {
        cout << "| " << setw(6) << i << " | ";
        
        if (tablaHash[i].ocupado) {
            int hashOriginal = funcionHashSimple(tablaHash[i].id);
            cout << setw(9) << tablaHash[i].id << " | ";
            cout << "    E-" << setw(2) << tablaHash[i].numeroEstudiante << "   | ";
            cout << " OCUPADO  | ";
            cout << setw(13) << hashOriginal;
            
            // Marcar si hay colision
            if (i != hashOriginal) {
                cout << " *";
            }
        } else {
            cout << "    ---   |     ---    |   LIBRE  |      ---     ";
        }
        cout << " |" << endl;
    }
    
    cout << string(70, '=') << endl;
    cout << "* = Elemento movido por colision" << endl;
}

// ==================== ESTADISTICAS DETALLADAS ====================
void mostrarEstadisticas() {
    int ocupados = 0;
    int colisiones = 0;
    int maxSondeos = 0;
    
    // Contar estadisticas
    for (int i = 0; i < TABLA_SIZE; i++) {
        if (tablaHash[i].ocupado) {
            ocupados++;
            
            int posicionOriginal = funcionHashSimple(tablaHash[i].id);
            if (i != posicionOriginal) {
                colisiones++;
                
                // Calcular cuantos sondeos fueron necesarios
                int sondeos = (i >= posicionOriginal) ? 
                             (i - posicionOriginal) : 
                             (TABLA_SIZE - posicionOriginal + i);
                maxSondeos = max(maxSondeos, sondeos);
            }
        }
    }
    
    double factorCarga = (double)ocupados / TABLA_SIZE;
    double eficiencia = ((double)(NUM_ESTUDIANTES - colisiones) / NUM_ESTUDIANTES) * 100;
    
    cout << "\n┌─── ESTADISTICAS DETALLADAS ───┐" << endl;
    cout << "│ Total estudiantes:     " << setw(7) << NUM_ESTUDIANTES << " │" << endl;
    cout << "│ Tamaño tabla:          " << setw(7) << TABLA_SIZE << " │" << endl;
    cout << "│ Slots ocupados:        " << setw(7) << ocupados << " │" << endl;
    cout << "│ Slots libres:          " << setw(7) << (TABLA_SIZE - ocupados) << " │" << endl;
    cout << "│ Colisiones:            " << setw(7) << colisiones << " │" << endl;
    cout << "│ Max sondeos:           " << setw(7) << maxSondeos << " │" << endl;
    cout << "│ Factor de carga:       " << setw(6) << fixed << setprecision(2) << factorCarga << " │" << endl;
    cout << "│ Eficiencia:            " << setw(6) << fixed << setprecision(1) << eficiencia << "% │" << endl;
    cout << "└───────────────────────────────┘" << endl;
}

// ==================== BUSQUEDA DE IDs ====================
/*
 * BUSQUEDA CON LINEAR PROBING:
 * - Calcular indice con funcion hash
 * - Si el slot esta vacio, el elemento no existe
 * - Si esta ocupado pero es otro ID, continuar sondeo
 * - Si encontramos el ID buscado, exito
 * - Complejidad promedio: O(1), peor caso: O(n)
 */
void buscarID() {
    int idBuscado = pedirEntero("\nIngrese el ID a buscar: ");
    
    cout << "\n" << string(50, '=') << endl;
    cout << "         PROCESO DE BUSQUEDA" << endl;
    cout << string(50, '=') << endl;
    
    mostrarCalculoPasoAPaso(idBuscado);
    
    int indice = funcionHashSimple(idBuscado);
    int indiceOriginal = indice;
    int pasos = 0;
    bool encontrado = false;
    
    cout << "\n🔍 Iniciando busqueda en la tabla..." << endl;
    
    do {
        pasos++;
        cout << "  Paso " << pasos << ": Revisando indice " << indice << " → ";
        
        if (!tablaHash[indice].ocupado) {
            cout << "VACIO (El ID no existe en la tabla)" << endl;
            break;
        } else if (tablaHash[indice].id == idBuscado) {
            cout << "¡ENCONTRADO!" << endl;
            encontrado = true;
            break;
        } else {
            cout << "Ocupado por ID " << tablaHash[indice].id << " (continuar...)" << endl;
            indice = (indice + 1) % TABLA_SIZE;
        }
        
    } while (indice != indiceOriginal && pasos < TABLA_SIZE);
    
    // Mostrar resultado
    cout << "\n" << string(50, '=') << endl;
    if (encontrado) {
        cout << "✅ RESULTADO: ID ENCONTRADO" << endl;
        cout << "   ID: " << idBuscado << endl;
        cout << "   Posicion: Indice " << indice << endl;
        cout << "   Estudiante: #" << tablaHash[indice].numeroEstudiante << endl;
        cout << "   Pasos necesarios: " << pasos << endl;
        
        int posicionOriginal = funcionHashSimple(idBuscado);
        if (indice != posicionOriginal) {
            cout << "   Nota: Movido por colision (posicion original: " << posicionOriginal << ")" << endl;
        }
    } else {
        cout << "❌ RESULTADO: ID NO ENCONTRADO" << endl;
        cout << "   El ID " << idBuscado << " no existe en la clase" << endl;
        cout << "   Pasos realizados: " << pasos << endl;
    }
    cout << string(50, '=') << endl;
}

// ==================== DEMOSTRAR FUNCIONAMIENTO ====================
void demostrarFuncionamiento() {
    cout << "\n" << string(60, '=') << endl;
    cout << "           DEMOSTRACION DEL FUNCIONAMIENTO" << endl;
    cout << string(60, '=') << endl;
    
    cout << "\n📚 ¿Como funciona nuestra tabla hash?" << endl;
    cout << "1. Tomamos un ID (ej: 1124396)" << endl;
    cout << "2. Aplicamos la funcion hash:" << endl;
    cout << "   - Ultimos 2 digitos: 96" << endl;
    cout << "   - Multiplicar por 3: 96 * 3 = 288" << endl;
    cout << "   - Modulo " << TABLA_SIZE << ": 288 % " << TABLA_SIZE << " = " << (288 % TABLA_SIZE) << endl;
    cout << "3. Intentamos insertar en el indice " << (288 % TABLA_SIZE) << endl;
    cout << "4. Si esta ocupado, probamos el siguiente (Linear Probing)" << endl;
    
    cout << "\n⚡ Complejidad temporal:" << endl;
    cout << "   - Insercion: O(1) promedio" << endl;
    cout << "   - Busqueda: O(1) promedio" << endl;
    cout << "   - Espacio: O(n) donde n = " << TABLA_SIZE << endl;
    
    cout << "\n🎯 Ventajas de esta implementacion:" << endl;
    cout << "   ✅ Muy rapida para busquedas" << endl;
    cout << "   ✅ Facil de entender" << endl;
    cout << "   ✅ Uso eficiente de memoria" << endl;
    cout << "   ✅ Tabla dimensionada para evitar colisiones" << endl;
}

// ==================== MENU PRINCIPAL ====================
void mostrarMenu() {
    cout << "\n" << string(45, '=') << endl;
    cout << "     TABLA HASH SIMPLE - PRINCIPIANTES" << endl;
    cout << "        Complejidad: O(1) promedio" << endl;
    cout << string(45, '=') << endl;
    cout << "1. 📥 Llenar tabla hash con todos los IDs" << endl;
    cout << "2. 📊 Ver tabla completa y estadisticas" << endl;
    cout << "3. 🔍 Buscar un ID especifico" << endl;
    cout << "4. 📚 Demostrar funcionamiento" << endl;
    cout << "5. 🚪 Salir" << endl;
    cout << string(45, '=') << endl;
}

// ==================== PROGRAMA PRINCIPAL ====================
int main() {
    int opcion;
    bool tablaLlena = false;
    
    cout << string(60, '=') << endl;
    cout << "  🎓 BIENVENIDO AL PROGRAMA DE TABLA HASH EDUCATIVO" << endl;
    cout << string(60, '=') << endl;
    cout << "\nEste programa demuestra como funciona una tabla hash simple" << endl;
    cout << "usando los IDs de estudiantes de la clase IDS343-01." << endl;
    cout << "\n🔧 Configuracion actual:" << endl;
    cout << "   - Estudiantes: " << NUM_ESTUDIANTES << endl;
    cout << "   - Tamaño tabla: " << TABLA_SIZE << " (numero primo)" << endl;
    cout << "   - Funcion hash: (ID % 100) * 3 % " << TABLA_SIZE << endl;
    cout << "   - Resolucion colisiones: Linear Probing" << endl;
    
    do {
        mostrarMenu();
        opcion = pedirOpcion();
        
        switch (opcion) {
            case 1:
                llenarTabla();
                mostrarEstadisticas();
                tablaLlena = true;
                break;
                
            case 2:
                if (tablaLlena) {
                    mostrarTablaCompleta();
                    mostrarEstadisticas();
                } else {
                    cout << "\n⚠️  Primero debe llenar la tabla (opcion 1)" << endl;
                }
                break;
                
            case 3:
                if (tablaLlena) {
                    buscarID();
                } else {
                    cout << "\n⚠️  Primero debe llenar la tabla (opcion 1)" << endl;
                }
                break;
                
            case 4:
                demostrarFuncionamiento();
                break;
                
            case 5:
                cout << "\n" << string(40, '=') << endl;
                cout << "  ¡Gracias por usar el programa!" << endl;
                cout << "     Programa terminado ✅" << endl;
                cout << string(40, '=') << endl;
                break;
        }
        
        if (opcion != 5) {
            cout << "\n📝 Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 5);
    
    return 0;
}

// ==================== FIN DEL PROGRAMA ====================