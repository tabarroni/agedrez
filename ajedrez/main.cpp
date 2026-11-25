#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
//estructura para representar la posicion en el tablero
struct Posicion {
    int fila;
    int columna;
    int columna;
};
class Ajedrez{
private:
    char tablero[8][8];
    bool turnoBlancas; //true si es el turno de las blancas, false si es de las negras
    void inicializarTablero(){
        //piezas negras
        tablero[0][0]= "r"; tablero[0][1]="n"; tablero[0][2] = 'b'; tablero[0][3] = 'q';
        tablero[0][4] = 'k'; tablero[0][5] = 'b'; tablero[0][6] = 'n'; tablero[0][7] = 'r';
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
