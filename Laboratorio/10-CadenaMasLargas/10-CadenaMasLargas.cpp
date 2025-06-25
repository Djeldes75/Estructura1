#include <iostream>

using namespace std;

int calcularLongitud(int numero) {

    int longitud = 0;

    while (numero != 4) {
        if (numero % 2 == 0) {
            numero /= 2;
        }
        else {
            numero = numero * 3 + 1;
        }
        longitud++;
    }
    return longitud;
}

int main() {

    int maxLongitud = 0;
    int invitadoConCadenaMasLarga = 0;

    for (int i = 1; i <= 99; i++) {
        int longitud = calcularLongitud(i);
        if (longitud > maxLongitud) {
            maxLongitud = longitud;
            invitadoConCadenaMasLarga = i;
        }
    }

    cout << "El invitado con la cadena mas larga es: " << invitadoConCadenaMasLarga << endl;
    cout << "La longitud de la cadena es: " << maxLongitud << endl;

    return 0;
}