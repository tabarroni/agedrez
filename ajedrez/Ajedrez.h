#ifndef AJEDREZ_H
#define AJEDREZ_H

#include <vector>
#include <string>

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

    double tiempoBlancas = 300.0;
    double tiempoNegras = 300.0;

    vector<string> historial;

    void inicializarTablero();
    bool caminoLibre(Posicion o, Posicion d, char t[8][8]);
    bool esMovimientoGeometricoValido(Posicion o, Posicion d, char t[8][8]);
    bool esJaqueMate(bool esBlanco);

public:
    Ajedrez();
    void imprimirTablero();
    bool estaEnJaque(bool esBlanco, char t[8][8]);
    bool esMovimientoValido(Posicion o, Posicion d);
    bool hayInsuficienciaMaterial();
    bool mover(string movimiento, double tiempoConsumido);
    bool esJaqueMateActual();
    bool esTablasPorInsuficiencia();
    bool estaEnTurnoBlancas();
    bool seAcaboElTiempo();
    void mostrarHistorial();
    double getTiempoBlancas();
    double getTiempoNegras();
};

#endif
