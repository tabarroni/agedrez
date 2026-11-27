#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include "Ajedrez.h"

using namespace std;

const int TAM_CASILLA = 80; // 80 píxeles por casilla (Tablero de 640x640)

int main() {
    Ajedrez juego;
    sf::RenderWindow ventana(sf::VideoMode({640, 640}), "Ajedrez C++ con SFML");

    // Cargar fuente para las piezas y textos (asegúrate de tener Arial en Windows o ajusta la ruta)
    sf::Font fuente;
    if (!fuente.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Error al cargar la fuente Arial." << endl;
    }

    // Bucle principal del juego
    while (ventana.isOpen()) {
        // Manejo de eventos en SFML 3.1.0 usando std::optional
        while (const std::optional evento = ventana.pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana.close();
            }

            // Aquí puedes integrar la lógica de clics del mouse para tu ajedrez usando sf::Event
            if (const auto* mousePressed = evento->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    int x = mousePressed->position.x;
                    int y = mousePressed->position.y;
                    int col = x / TAM_CASILLA;
                    int fila = y / TAM_CASILLA;

                    // Ejemplo: aquí llamarías a tu lógica de selección de casilla
                    // juego.seleccionarCasilla(fila, col);
                }
            }
        }

        ventana.clear(sf::Color(50, 50, 50)); // Color de fondo gris oscuro

        // ==========================================
        // DIBUJADO DEL TABLERO Y PIEZAS (Ejemplo)
        // ==========================================
        for (int fila = 0; fila < 8; ++fila) {
            for (int col = 0; col < 8; ++col) {
                sf::RectangleShape casilla(sf::Vector2f(TAM_CASILLA, TAM_CASILLA));
                casilla.setPosition({static_cast<float>(col * TAM_CASILLA), static_cast<float>(fila * TAM_CASILLA)});

                // Alternar colores del tablero
                if ((fila + col) % 2 == 0) {
                    casilla.setFillColor(sf::Color(240, 217, 181)); // Claro
                } else {
                    casilla.setFillColor(sf::Color(181, 136, 99));  // Oscuro
                }
                ventana.draw(casilla);
            }
        }

        ventana.display();
    }

    return 0;
}
