/*
    
*/
#include <iostream>

using namespace std;

int main() {

    int x = 1;
    int y = 1;
    int siguiente;

    cout << "Serie de Fibonacci:" << endl;

    cout << x << ",\n" << y;

    for (int i = 3; i <= 30; i++) {
        siguiente = x + y;
        cout << ",\n" << siguiente;

        x = y;
        y = siguiente;
    }

    cout << endl;
    return 0;
}
