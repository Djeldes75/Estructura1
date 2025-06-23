/*
-----------------------------------------------------------------------------------------
Tarea: Generación de los primeros N números primos
Materia: IDS343L-01-LABORATORIO ESTRUCTURAS DE DATOS Y ALGORITMOS I
-----------------------------------------------------------------------------------------

PROBLEMA:
    Desarrollar un programa en C++ que genere e imprima los primeros N números primos
    solicitados por el usuario, donde N es un número entero positivo ingresado por 
    teclado. El programa debe ser eficiente y optimizado para manejar valores grandes de N.

REQUERIMIENTOS:
    1. Solicitar al usuario la cantidad N de números primos a generar
    2. Validar que N sea un número entero positivo
    3. Generar los primeros N números primos de manera eficiente
    4. Mostrar los números primos encontrados separados por espacios
    5. El algoritmo debe ser optimizado para ser más rápido que implementaciones básicas

ALGORITMO IMPLEMENTADO:
    Generador híbrido ultra-optimizado que combina múltiples técnicas:
    
    1. CRIBA DE ERATÓSTENES INICIAL:
       - Precalcula los primeros ~168 primos (hasta 1000) usando criba
       - Evita recalcular primos pequeños repetidamente
       
    2. WHEEL FACTORIZATION 30:
       - Usa la rueda 2×3×5 = 30 para evaluar solo candidatos válidos
       - Solo verifica números de la forma 30k + {1,7,11,13,17,19,23,29}
       - Reduce verificaciones en 73.3% (solo 8 de cada 30 números)
       
    3. CACHE INTELIGENTE:
       - Almacena primos calculados para reutilizarlos en verificaciones futuras
       - Usa búsqueda binaria para acceso rápido al cache
       
    4. DIVISIÓN TRIAL OPTIMIZADA:
       - Solo divide por primos conocidos hasta √n
       - Implementa raíz cuadrada manual (método babilónico)

COMPLEJIDAD TEMPORAL:
    - Para n < 1000: O(n log log n) [criba]
    - Para n ≥ 1000: O(n√n/log n) [wheel + cache]

INTEGRANTE:
    Dominique Jeldes - 1121623
    
Fecha: 23/Jun/2025
*/

#include <iostream>

using namespace std;

class GeneradorNPrimos {

private:
    static const int MAX_CACHE_PRIMOS = 2000;
    static const int LIMITE_CRIBA_INICIAL = 1000;
    
    int cachePrimos[MAX_CACHE_PRIMOS];    // Array para almacenar primos calculados
    int totalPrimosEnCache;
    
    // Wheel 30: residuos que pueden ser primos > 5 al dividir por 30

    static const int wheel30[8];
    
    // Implementación de raíz cuadrada usando método babilónico.
    int calcularRaizCuadrada(int numero) {
        if (numero == 0) return 0;
        if (numero == 1) return 1;
        
        int x = numero;
        // Método de Newton-Raphson (babilónico) para encontrar √n
        while (x > numero / x) {
            x = (x + numero / x) / 2;
        }
        return x;
    }
    
    // CRIBA DE ERATÓSTENES para generar primos iniciales hasta LIMITE_CRIBA_INICIAL

    void ejecutarCribaInicial() {
        bool esPrimo[LIMITE_CRIBA_INICIAL];
        
        // Inicializar: todos los números > 1 son potencialmente primos
        for (int i = 0; i < LIMITE_CRIBA_INICIAL; i++) {
            esPrimo[i] = (i > 1);
        }
        
        int limiteSuperior = calcularRaizCuadrada(LIMITE_CRIBA_INICIAL);
        
        // Algoritmo de la Criba de Eratóstenes
        for (int i = 2; i <= limiteSuperior; i++) {
            if (esPrimo[i]) {
                // Marcar todos los multiplos de i.
                for (int multiplo = i * i; multiplo < LIMITE_CRIBA_INICIAL; multiplo += i) {
                    esPrimo[multiplo] = false;
                }
            }
        }

        totalPrimosEnCache = 0;
        for (int i = 2; i < LIMITE_CRIBA_INICIAL && totalPrimosEnCache < MAX_CACHE_PRIMOS; i++) {
            if (esPrimo[i]) {
                cachePrimos[totalPrimosEnCache++] = i;
            }
        }
    }
    
    // Búsqueda binaria para verificar si un número está en el cache de primos

    bool buscarEnCachePrimos(int numero) {

        int izquierda = 0;
        int derecha = totalPrimosEnCache - 1;
        
        while (izquierda <= derecha) {
            int medio = (izquierda + derecha) / 2;
            
            if (cachePrimos[medio] == numero) return true;
            else if (cachePrimos[medio] < numero) izquierda = medio + 1;
            else derecha = medio - 1;
        }
        return false;
    }
    
    //Primo o No
    bool esNumeroPrimo(int numero) {
        // Casos base triviales
        if (numero < 2) return false;
        if (numero == 2 || numero == 3 || numero == 5) return true;
        
        //Filtro para quitar repetidos
        if (numero % 2 == 0 || numero % 3 == 0 || numero % 5 == 0) {
            return false;
        }
        
        // Si el número está en rango de criba busca dentro dek cache
        if (numero < LIMITE_CRIBA_INICIAL) {
            return buscarEnCachePrimos(numero);
        }
        
        // DIVISIÓN trial: solo dividir por primos hasta √numero
        int limiteDivision = calcularRaizCuadrada(numero);
        
        // Verificar divisibilidad por todos los primos conocidos hasta √numero
        for (int i = 0; i < totalPrimosEnCache; i++) {
            int primoActual = cachePrimos[i];

            if (primoActual > limiteDivision) break;  // Ya verificamos suficiente
            if (numero % primoActual == 0) return false;  // Es compuesto
        }
        
        // Si nuestro cache no cubre hasta √numero, continuar con WHEEL 30
        if (totalPrimosEnCache > 0 && cachePrimos[totalPrimosEnCache-1] < limiteDivision) {
            int ultimoPrimoConocido = cachePrimos[totalPrimosEnCache-1];
            int baseWheel = ((ultimoPrimoConocido / 30) + 1) * 30;
            
            // Verificar solo candidatos de la wheel 30
            while (baseWheel <= limiteDivision) {
                for (int j = 0; j < 8; j++) {
                    int candidatoDivisor = baseWheel + wheel30[j];
                    
                    if (candidatoDivisor <= ultimoPrimoConocido) continue;
                    if (candidatoDivisor > limiteDivision) return true;
                    if (numero % candidatoDivisor == 0) return false;
                }
                baseWheel += 30;
            }
        }
        
        return true;
    }
    
    // Agregar primo al cache si hay espacio disponible
    void agregarPrimoAlCache(int primo) {
        if (totalPrimosEnCache < MAX_CACHE_PRIMOS) {
            cachePrimos[totalPrimosEnCache++] = primo;
        }
    }

public:
    GeneradorNPrimos() : totalPrimosEnCache(0) {
        ejecutarCribaInicial();  // Preparar cache inicial con criba
    }
    
    // FUNCIÓN PRINCIPAL: Generar los primeros N números primos
    void generarPrimeros(int n) {
        if (n <= 0) {
            cout << "❌ Error: N debe ser un número entero positivo." << endl;
            return;
        }
        
        cout << "Los primeros " << n << " números primos son:" << endl;
        
        int contadorPrimos = 0;
        
        // FASE 1: Mostrar primos del cache inicial (criba)
        for (int i = 0; i < totalPrimosEnCache && contadorPrimos < n; i++) {
            cout << cachePrimos[i];
            contadorPrimos++;
            if (contadorPrimos < n) cout << " ";
        }
        
        // Si ya generamos suficientes primos, terminar
        if (contadorPrimos >= n) {
            cout << endl;
            return;
        }
        
        // FASE 2: Generar primos adicionales usando WHEEL 30
        int ultimoPrimoEncontrado = (totalPrimosEnCache > 0) ? cachePrimos[totalPrimosEnCache-1] : 5;

        int baseActualWheel = ((ultimoPrimoEncontrado / 30) + 1) * 30;
        
        while (contadorPrimos < n) {
            // Verificar solo los 8 candidatos válidos de cada grupo de 30
            for (int i = 0; i < 8 && contadorPrimos < n; i++) {
                int candidatoPrimo = baseActualWheel + wheel30[i];
                
                // Evitar duplicados
                if (candidatoPrimo <= ultimoPrimoEncontrado) continue;
                
                // Verificar si es primo usando algoritmo híbrido
                if (esNumeroPrimo(candidatoPrimo)) {
                    cout << " " << candidatoPrimo;
                    contadorPrimos++;
                    agregarPrimoAlCache(candidatoPrimo);
                    ultimoPrimoEncontrado = candidatoPrimo;
                }
            }
            baseActualWheel += 30;  // Avanzar al siguiente grupo de 30
        }
        
        cout << endl;
    }

private:
    // Función auxiliar para convertir int a string
    string to_string(int numero) {
        if (numero == 0) return "0";
        
        string resultado = "";
        bool esNegativo = numero < 0;

        if (esNegativo) numero = -numero;
        
        while (numero > 0) {
            resultado = char('0' + numero % 10) + resultado;
            numero /= 10;
        }
        
        if (esNegativo) resultado = "-" + resultado;
        return resultado;
    }
};

// Definición del wheel 30: únicos residuos mod 30 que pueden ser primos > 5
const int GeneradorNPrimos::wheel30[8] = {1, 7, 11, 13, 17, 19, 23, 29};

//Main
int main() {
    // Mostrar información del programa
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║               GENERADOR DE N NÚMEROS PRIMOS                ║" << endl;
    cout << "║          Algoritmo con Múltiples          ║" << endl;
    cout << "║                     Técnicas                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    // Crear instancia del generador (ejecuta criba inicial automáticamente)
    GeneradorNPrimos generador;
    
    // Solicitar entrada del usuario
    int n;
    cout << "\nIngrese la cantidad de números primos que desea generar: ";
    cin >> n;
    
    // Validar entrada
    if (n <= 0) {
        cout << "❌ Error: Debe ingresar un número entero positivo." << endl;
        return 1;
    }
    
    // Generar y mostrar los primeros N primos
    cout << endl;
    generador.generarPrimeros(n);
    
    // Preguntar si mostrar información técnica
    char respuesta;
    cout << "\n¿Desea ver información detallada del algoritmo utilizado? (s/n): ";
    cin >> respuesta;
    
    if (respuesta == 's' || respuesta == 'S') {
        generador.mostrarInformacionAlgoritmo();
    }
    
    cout << "\n✅ Programa ejecutado exitosamente. ¡Gracias por usar el generador!" << endl;
    
    return 0;
}