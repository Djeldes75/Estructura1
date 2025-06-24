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

    int cachePrimos[MAX_CACHE_PRIMOS];
    int totalPrimosEnCache;

    static const int wheel30[8];

    int calcularRaizCuadrada(int numero) {
        if (numero == 0) return 0;
        if (numero == 1) return 1;

        int x = numero;
        while (x > numero / x) {
            x = (x + numero / x) / 2;
        }
        return x;
    }

    void ejecutarCribaInicial() {

        bool esPrimo[LIMITE_CRIBA_INICIAL];

        for (int i = 0; i < LIMITE_CRIBA_INICIAL; i++) {

            esPrimo[i] = (i > 1);
        }

        int limiteSuperior = calcularRaizCuadrada(LIMITE_CRIBA_INICIAL);

        for (int i = 2; i <= limiteSuperior; i++) {

            if (esPrimo[i]) {

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

    bool esNumeroPrimo(int numero) {

        if (numero < 2) return false;
        if (numero == 2 || numero == 3 || numero == 5) return true;

        if (numero % 2 == 0 || numero % 3 == 0 || numero % 5 == 0) {
            return false;
        }

        if (numero < LIMITE_CRIBA_INICIAL) {

            return buscarEnCachePrimos(numero);
        }

        int limiteDivision = calcularRaizCuadrada(numero);

        for (int i = 0; i < totalPrimosEnCache; i++) {
            int primoActual = cachePrimos[i];

            if (primoActual > limiteDivision) break;
            if (numero % primoActual == 0) return false;
        }

        if (totalPrimosEnCache > 0 && cachePrimos[totalPrimosEnCache - 1] < limiteDivision) {

            int ultimoPrimoConocido = cachePrimos[totalPrimosEnCache - 1];
            int baseWheel = ((ultimoPrimoConocido / 30) + 1) * 30;

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

    void agregarPrimoAlCache(int primo) {

        if (totalPrimosEnCache < MAX_CACHE_PRIMOS) {

            cachePrimos[totalPrimosEnCache++] = primo;
        }
    }

public:
    GeneradorNPrimos() : totalPrimosEnCache(0) {
        ejecutarCribaInicial();
    }

    void generarPrimeros(int n) {
        if (n <= 0) {
            cout << "\n❌ Error: N debe ser un numero entero positivo.\n";
            return;
        }

        cout << "\nLos primeros " << n << " numeros primos son:\n";

        int contadorPrimos = 0;

        for (int i = 0; i < totalPrimosEnCache && contadorPrimos < n; i++) {
            cout << cachePrimos[i];
            contadorPrimos++;
            if (contadorPrimos < n) cout << " ";
        }

        if (contadorPrimos >= n) {
            cout << endl;
            return;
        }

        int ultimoPrimoEncontrado = (totalPrimosEnCache > 0) ? cachePrimos[totalPrimosEnCache - 1] : 5;
        int baseActualWheel = ((ultimoPrimoEncontrado / 30) + 1) * 30;

        while (contadorPrimos < n) {

            for (int i = 0; i < 8 && contadorPrimos < n; i++) {

                int candidatoPrimo = baseActualWheel + wheel30[i];

                if (candidatoPrimo <= ultimoPrimoEncontrado) continue;

                if (esNumeroPrimo(candidatoPrimo)) {

                    cout << " " << candidatoPrimo;
                    contadorPrimos++;
                    agregarPrimoAlCache(candidatoPrimo);
                    ultimoPrimoEncontrado = candidatoPrimo;
                }
            }
            baseActualWheel += 30;
        }

        cout << endl;
    }
};

const int GeneradorNPrimos::wheel30[8] = {1, 7, 11, 13, 17, 19, 23, 29};

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

            } else {
                cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        } else {
            cout << "ERROR: Entrada invalida.\nIntente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return valor;
}

int main() {
    cout << "=============================================================\n";
    cout <<   "               Generacion de N Numeros Primos               \n";
    cout << "=============================================================";

    GeneradorNPrimos generador;
    int n = validarEntero("\nIngrese la cantidad de numeros primos que desea generar: ");

    cout << endl;
    generador.generarPrimeros(n);

    cout << "\nPrograma ejecutado exitosamente.\n";
    return 0;
}
