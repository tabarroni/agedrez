#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

struct Posicion {
    int fila;
    int columna;
};

class Ajedrez {
private:
    char tablero[8][8];
    bool turnoBlancas;

    bool reyBlancoMovido = false, torreBlancaIzqMovida = false, torreBlancaDerMovida = false;
    bool reyNegroMovido = false, torreNegraIzqMovida = false, torreNegraDerMovida = false;
    Posicion casillaEnPassant = {-1, -1};

    void inicializarTablero() {
        tablero[0][0] = 'r'; tablero[0][1] = 'n'; tablero[0][2] = 'b'; tablero[0][3] = 'q';
        tablero[0][4] = 'k'; tablero[0][5] = 'b'; tablero[0][6] = 'n'; tablero[0][7] = 'r';
        for (int i = 0; i < 8; i++) tablero[1][i] = 'p';

        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 8; j++) tablero[i][j] = '.';
        }

        for (int i = 0; i < 8; i++) tablero[6][i] = 'P';
        tablero[7][0] = 'R'; tablero[7][1] = 'N'; tablero[7][2] = 'B'; tablero[7][3] = 'Q';
        tablero[7][4] = 'K'; tablero[7][5] = 'B'; tablero[7][6] = 'N'; tablero[7][7] = 'R';

        turnoBlancas = true;
    }

    bool caminoLibre(Posicion o, Posicion d, char t[8][8]) {
        int pasoFila = (d.fila > o.fila) ? 1 : (d.fila < o.fila ? -1 : 0);
        int pasoCol = (d.columna > o.columna) ? 1 : (d.columna < o.columna ? -1 : 0);

        int f = o.fila + pasoFila;
        int c = o.columna + pasoCol;

        while (f != d.fila || c != d.columna) {
            if (t[f][c] != '.') return false;
            f += pasoFila;
            c += pasoCol;
        }
        return true;
    }

    bool esMovimientoGeometricoValido(Posicion o, Posicion d, char t[8][8]) {
        char pieza = t[o.fila][o.columna];
        char destino = t[d.fila][d.columna];
        bool esBlanco = isupper(pieza);

        if (pieza == '.' ) return false;
        if (destino != '.' && (isupper(pieza) == isupper(destino))) return false;

        char p = toupper(pieza);
        int difFila = d.fila - o.fila;
        int difCol = d.columna - o.columna;

        switch (p) {
            case 'P': {
                int dir = esBlanco ? -1 : 1;
                if (difCol == 0 && destino == '.') {
                    if (difFila == dir) return true;
                    if ((esBlanco && o.fila == 6 && difFila == -2 && t[o.fila - 1][o.columna] == '.') ||
                        (!esBlanco && o.fila == 1 && difFila == 2 && t[o.fila + 1][o.columna] == '.')) {
                        return true;
                    }
                }
                if (abs(difCol) == 1 && difFila == dir) {
                    if (destino != '.') return true;
                    if (d.fila == casillaEnPassant.fila && d.columna == casillaEnPassant.columna) return true;
                }
                break;
            }
            case 'R':
                if (difFila == 0 || difCol == 0) return caminoLibre(o, d, t);
                break;
            case 'N':
                if ((abs(difFila) == 2 && abs(difCol) == 1) || (abs(difFila) == 1 && abs(difCol) == 2)) return true;
                break;
            case 'B':
                if (abs(difFila) == abs(difCol)) return caminoLibre(o, d, t);
                break;
            case 'Q':
                if (difFila == 0 || difCol == 0 || abs(difFila) == abs(difCol)) return caminoLibre(o, d, t);
                break;
            case 'K':
                if (abs(difFila) <= 1 && abs(difCol) <= 1) return true;
                if (difFila == 0 && abs(difCol) == 2) return true;
                break;
        }
        return false;
    }

public:
    Ajedrez() { inicializarTablero(); }

    void imprimirTablero() {
        cout << "\n    a   b   c   d   e   f   g   h\n";
        cout << "  +---+---+---+---+---+---+---+---+\n";
        for (int i = 0; i < 8; i++) {
            cout << 8 - i << " |";
            for (int j = 0; j < 8; j++) {
                cout << " " << tablero[i][j] << " |";
            }
            cout << " " << 8 - i << "\n";
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }
        cout << "    a   b   c   d   e   f   g   h\n\n";
    }

    bool estaEnJaque(bool esBlanco, char t[8][8]) {
        Posicion rey = {-1, -1};
        char objRey = esBlanco ? 'K' : 'k';
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (t[i][j] == objRey) { rey = {i, j}; break; }
            }
            if (rey.fila != -1) break;
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char p = t[i][j];
                if (p != '.' && ((esBlanco && islower(p)) || (!esBlanco && isupper(p)))) {
                    if (esMovimientoGeometricoValido({i, j}, rey, t)) return true;
                }
            }
        }
        return false;
    }

    bool esMovimientoValido(Posicion o, Posicion d) {
        return esMovimientoGeometricoValido(o, d, tablero);
    }

    // === LÓGICA DE TABLAS POR INSUFICIENCIA DE MATERIAL ===
    bool hayInsuficienciaMaterial() {
        vector<char> piezasBlancas;
        vector<char> piezasNegras;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char p = tablero[i][j];
                if (p != '.') {
                    if (isupper(p)) piezasBlancas.push_back(p);
                    else piezasNegras.push_back(p);
                }
            }
        }

        // Caso 1: Rey contra Rey solo
        if (piezasBlancas.size() == 1 && piezasNegras.size() == 1) return true;

        // Caso 2: Rey y Alfil o Rey y Caballo contra Rey solo
        if ((piezasBlancas.size() == 2 && piezasNegras.size() == 1) ||
            (piezasBlancas.size() == 1 && piezasNegras.size() == 2)) {
            char piezaExtra = (piezasBlancas.size() == 2) ? piezasBlancas[1] : piezasNegras[1];
            if (toupper(piezaExtra) == 'B' || toupper(piezaExtra) == 'N') return true;
        }

        // Caso 3: Rey y Alfil contra Rey y Alfil (con alfiles en casillas del mismo color)
        if (piezasBlancas.size() == 2 && piezasNegras.size() == 2 &&
            toupper(piezasBlancas[1]) == 'B' && toupper(piezasNegras[1]) == 'B') {
            Posicion alfilB = {-1, -1}, alfilN = {-1, -1};
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (tablero[i][j] == 'B') alfilB = {i, j};
                    if (tablero[i][j] == 'b') alfilN = {i, j};
                }
            }
            // Si la suma de (fila + columna) es par o impar, indica el color de la casilla
            bool colorB = (alfilB.fila + alfilB.columna) % 2 == 0;
            bool colorN = (alfilN.fila + alfilN.columna) % 2 == 0;
            if (colorB == colorN) return true;
        }

        return false;
    }

    bool mover(string movimiento) {
        if (movimiento.length() != 4) return false;
        Posicion o = {8 - (movimiento[1] - '0'), movimiento[0] - 'a'};
        Posicion d = {8 - (movimiento[3] - '0'), movimiento[2] - 'a'};

        char pieza = tablero[o.fila][o.columna];
        if (pieza == '.' || (turnoBlancas && !isupper(pieza)) || (!turnoBlancas && isupper(pieza))) {
            cout << "Movimiento inválido por selección de pieza.\n";
            return false;
        }

        if (!esMovimientoValido(o, d)) {
            cout << "Movimiento no permitido por reglas de la pieza.\n";
            return false;
        }

        char temp[8][8];
        for(int i=0; i<8; i++) for(int j=0; j<8; j++) temp[i][j] = tablero[i][j];

        temp[d.fila][d.columna] = pieza;
        temp[o.fila][o.columna] = '.';

        if (estaEnJaque(turnoBlancas, temp)) {
            cout << "¡Movimiento ilegal! Tu rey quedaría o continuaría en jaque.\n";
            return false;
        }

        tablero[d.fila][d.columna] = pieza;
        tablero[o.fila][o.columna] = '.';

        // Promoción automática a Reina si llega al final
        if ((pieza == 'P' && d.fila == 0) || (pieza == 'p' && d.fila == 7)) {
            tablero[d.fila][d.columna] = isupper(pieza) ? 'Q' : 'q';
        }

        turnoBlancas = !turnoBlancas;
        return true;
    }

    bool esJaqueMateActual() {
        return esJaqueMate(turnoBlancas);
    }

    bool esTablasPorInsuficiencia() {
        return hayInsuficienciaMaterial();
    }

private:
    bool esJaqueMate(bool esBlanco) {
        if (!estaEnJaque(esBlanco, tablero)) return false;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char p = tablero[i][j];
                if (p != '.' && ((esBlanco && isupper(p)) || (!esBlanco && islower(p)))) {
                    for (int di = 0; di < 8; di++) {
                        for (int dj = 0; dj < 8; dj++) {
                            Posicion o = {i, j}, d = {di, dj};
                            if (esMovimientoValido(o, d)) {
                                char temp[8][8];
                                for(int x=0; x<8; x++) for(int y=0; y<8; y++) temp[x][y] = tablero[x][y];
                                temp[d.fila][d.columna] = temp[o.fila][o.columna];
                                temp[o.fila][o.columna] = '.';
                                if (!estaEnJaque(esBlanco, temp)) return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    Ajedrez juego;
    string mov;
    while (true) {
        juego.imprimirTablero();

        if (juego.esJaqueMateActual()) {
            cout << "=== JAQUE MATE. ¡Fin del juego! ===\n";
            break;
        }
        if (juego.esTablasPorInsuficiencia()) {
            cout << "=== TABLAS por insuficiencia de material. ¡Empate! ===\n";
            break;
        }

        cout << "Turno de: " << (juego.esTablasPorInsuficiencia() ? "" : "") << endl;
        cout << "Ingresa movimiento: ";
        cin >> mov;
        if (mov == "salir") break;
        juego.mover(mov);
    }
    return 0;
}
