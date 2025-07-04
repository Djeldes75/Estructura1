/*

*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n;
    cout << "Ingrese la cantidad de valores: ";
    cin >> n;

    // Crear arreglo dinámico
    double* datos = new double[n];
    double suma = 0.0;

    // Entrada de datos
    cout << "Ingrese los " << n << " valores:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> datos[i];
        suma += datos[i];
    }

    // Calcular la media
    double media = suma / n;

    // Calcular varianza
    double sumaCuadrados = 0.0;
    for (int i = 0; i < n; ++i) {
        sumaCuadrados += pow(datos[i] - media, 2);
    }

    double varianza = sumaCuadrados / (n - 1);
    double desviacionEstandar = sqrt(varianza);

    // Mostrar resultados
    cout << "Media: " << media << endl;
    cout << "Varianza: " << varianza << endl;
    cout << "Desviacion estandar: " << desviacionEstandar << endl;

    // Liberar memoria
    delete[] datos;

    return 0;
}