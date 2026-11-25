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
        for (int i =0; i<8; i++) tablero[1][i]= "p";
        //espacios vacios
        for(int i=2; i<6;i++){
            for(int j=0;j<8;j++){
                tablero[i][j]= '.';
            }
        }
        //piezas blancas
        for (int i = 0; i < 8; i++) tablero[6][i] = 'P';
        tablero[7][0] = 'R'; tablero[7][1] = 'N'; tablero[7][2] = 'B'; tablero[7][3] = 'Q';
        tablero[7][4] = 'K'; tablero[7][5] = 'B'; tablero[7][6] = 'N'; tablero[7][7] = 'R';
        turnoBlancas = true;

public:
    Ajedrez(){
        inicializarTablero()
    }
    void imprimirTablero(){
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
