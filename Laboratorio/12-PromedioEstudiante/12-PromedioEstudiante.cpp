/*
    ENUNCIADO: Programa para calcular estadísticas de notas de estudiantes
    (desviación estándar, moda, máximo, mínimo)
    FECHA: 24/06/2025
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "Ingresa la cantidad de estudiantes: ";
    cin >> n;
    
    // Variables para los cálculos
    double suma = 0.0;
    double sumaCuadrados = 0.0;
    double maximo = -1.0;  // Inicializar con valor imposible para notas
    double minimo = 101.0; // Inicializar con valor imposible para notas
    
    // Variables para la moda
    double moda = 0.0;
    int frecuenciaMaxima = 0;
    
    cout << "Ingresa las notas de los estudiantes (0-100): " << endl;
    
    // Primer paso: leer las notas y calcular suma, máximo y mínimo
    double notas[100]; // Asumimos máximo 100 estudiantes
    for (int i = 0; i < n; i++) {
        cout << "Nota del estudiante " << (i + 1) << ": ";
        cin >> notas[i];
        
        // Sumar para la media
        suma += notas[i];
        
        // Encontrar máximo y mínimo
        if (notas[i] > maximo) {
            maximo = notas[i];
        }
        if (notas[i] < minimo) {
            minimo = notas[i];
        }
    }
    
    // Calcular la media
    double media = suma / n;
    
    // Calcular la suma de cuadrados para desviación estándar
    for (int i = 0; i < n; i++) {
        sumaCuadrados += pow(notas[i] - media, 2);
    }
    
    // Calcular desviación estándar
    double desviacionEstandar = sqrt(sumaCuadrados / n);
    
    // Calcular la moda (nota que más se repite)
    for (int i = 0; i < n; i++) {
        int frecuencia = 0;
        
        // Contar cuántas veces aparece esta nota
        for (int j = 0; j < n; j++) {
            if (notas[i] == notas[j]) {
                frecuencia++;
            }
        }
        
        // Si esta frecuencia es mayor, actualizar la moda
        if (frecuencia > frecuenciaMaxima) {
            frecuenciaMaxima = frecuencia;
            moda = notas[i];
        }
    }
    
    // Mostrar resultados
    cout << "\n=== ESTADISTICAS DE LAS NOTAS ===" << endl;
    cout << "Cantidad de estudiantes: " << n << endl;
    cout << "Nota promedio: " << media << endl;
    cout << "Nota maxima: " << maximo << endl;
    cout << "Nota minima: " << minimo << endl;
    cout << "Moda (nota mas frecuente): " << moda;
    
    if (frecuenciaMaxima > 1) {
        cout << " (aparece " << frecuenciaMaxima << " veces)" << endl;
    } else {
        cout << " (no hay moda - todas las notas son diferentes)" << endl;
    }
    
    cout << "Desviacion estandar: " << desviacionEstandar << endl;
    
    return 0;
}