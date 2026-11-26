#include <iostream>
#include <string>
#include <chrono>
#include "Ajedrez.h"

using namespace std;

int main() {
    Ajedrez juego;
    string mov;

    cout << "=== BIENVENIDO A LA INTERFAZ DE AJEDREZ EN C++ ===\n";
    cout << "Instrucciones: Ingresa jugadas como 'e2e4' o escribe 'salir'.\n";

    while (true) {
        juego.imprimirTablero();

        if (juego.esJaqueMateActual()) {
            cout << "\n=== JAQUE MATE. ¡Fin del juego! ===\n";
            break;
        }
        if (juego.esTablasPorInsuficiencia()) {
            cout << "\n=== TABLAS por insuficiencia de material. ¡Empate! ===\n";
            break;
        }
        if (juego.seAcaboElTiempo()) {
            break;
        }

        cout << "\nTurno de: " << (juego.estaEnTurnoBlancas() ? "Blancas (Mayúsculas)" : "Negras (Minúsculas)") << "\n";
        cout << "Ingresa movimiento: ";

        auto inicioTurno = chrono::steady_clock::now();
        cin >> mov;
        auto finTurno = chrono::steady_clock::now();

        chrono::duration<double> duracion = finTurno - inicioTurno;

        if (mov == "salir") break;

        juego.mover(mov, duracion.count());
    }

    juego.mostrarHistorial();
    return 0;
}
