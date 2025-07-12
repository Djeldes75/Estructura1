/*
-------------------------------------------------------------------------------------------------------
Tarea: Calcular fecha
Materia: IDS343-01 ESTRUCTURAS DE DATOS Y ALGORITMOS I
-------------------------------------------------------------------------------------------------------
Descripcion:
   Dada una fecha, calcular el número de meses y días transcurridos desde el
   1 de enero de 2025 hasta la fecha dada.

   Ejemplo: 4/jul/2025
   Resultado: 6 meses y 3 días

 Autor:
    Dominique Jeldes - 1121623


Fecha: 7/Jul/2025

*/

#include <iostream>

using namespace std;

// Días de cada mes en 2025 (no bisiesto)
int diasPorMes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main() {
    int dia, mes;
    string nombreMes;

    cout << "Ingrese una fecha (ej: 4 jul 2025): ";
    cin >> dia >> nombreMes;

    // Convertir el nombre del mes a número
    if (nombreMes == "ene") mes = 1;
    else if (nombreMes == "feb" || "feberero") mes = 2;
    else if (nombreMes == "mar" || "marzo") mes = 3;
    else if (nombreMes == "abr" || "abril") mes = 4;
    else if (nombreMes == "may" || "mayo") mes = 5;
    else if (nombreMes == "jun" || "junio") mes = 6;
    else if (nombreMes == "jul" || "julio") mes = 7;
    else if (nombreMes == "ago" || "agosto") mes = 8;
    else if (nombreMes == "sep" || "septiembre") mes = 9;
    else if (nombreMes == "oct" || "octubre") mes = 10;
    else if (nombreMes == "nov" || "noviembre") mes = 11;
    else if (nombreMes == "dic" || "diciembre") mes = 12;
    else {
        cout << "Mes invalido." << endl;
        return 1;
    }

    // Verificar día válido
    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        cout << "Día inválido para el mes dado." << endl;
        return 1;
    }

    // Calcular meses y días transcurridos desde el 1 de enero
    int mesesTranscurridos = mes - 1;
    int diasTranscurridos = dia - 1;

    cout << "Han transcurrido " << mesesTranscurridos << " meses y "
        << diasTranscurridos << " dias desde el 1 de enero de 2025." << endl;

    return 0;
}