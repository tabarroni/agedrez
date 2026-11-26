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
        cout <<"\n    a   b   c   d   e   f   g   h\n";
        cout << "  +---+---+---+---+---+---+---+---+\n";
        for(int i =0;i<8;i++){
            cout << 8 - i << " |";
            for(int j=0;j<8;j++){
                cout << " " << tablero[i][j] << " |";
            }
            cout << " " << 8 - i << "\n";
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }
        cout << "    a   b   c   d   e   f   g   h\n\n";
    }
    // Convierte una jugada en texto (ej. "e2e4") a coordenadas numéricas
    bool convertirCoordenadas(string mov, Posicion &origen, Posicion &destino){
        if(mov.length() !=4) ruturn false;
        origen.columna = mov[0] - 'a';
        origen.fila = 8 - (mov[1] - '0');

        destino.columna = mov[2] - 'a';
        destino.fila = 8 - (mov[3] - '0');

        // Verificar que estén dentro del tablero
        if (origen.fila < 0 || origen.fila > 7 || origen.columna < 0 || origen.columna > 7 ||
            destino.fila < 0 || destino.fila > 7 || destino.columna < 0 || destino.columna > 7) {
            return false;
        }

        return true;


    }
    bool validarturno(char pieza){
        if (turnoBlancas && isupper(pieza)) return true;
        if (!turnoBlancas && islower(pieza)) return true;
        return false;

    // Validación simplificada de movimientos por tipo de pieza
    bool esMovimientoValido(posicion o, posicion d){
        char pieza = tablero[o.fila][o.columna];
        char destino = tablero[d.fila][d.columna];
        //no puedes comerte tu misma pieza
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
