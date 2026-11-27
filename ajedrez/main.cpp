#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include "Ajedrez.h"

using namespace std;

const int TAM_CASILLA = 80; // 80 píxeles por casilla (Tablero de 640x640)

int main() {
    Ajedrez juego;
    sf::RenderWindow ventana(sf::VideoMode({640, 640}), "Ajedrez C++ con SFML");

    // Cargar fuente para textos o mensajes
    sf::Font fuente;
    if (!fuente.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Aviso: No se pudo cargar la fuente Arial del sistema." << endl;
    }

    // ==========================================
    // CARGAR TEXTURAS DE LAS PIEZAS
    // ==========================================
    map<char, sf::Texture> texturas;

    // Lista de piezas y sus archivos (asegúrate de tener la carpeta 'assets' en tu proyecto)
    string ruta = "assets/";

    // Blancas (Mayúsculas)
    texturas['P'].loadFromFile(ruta + "w_pawn.png");
    texturas['R'].loadFromFile(ruta + "w_rook.png");
    texturas['N'].loadFromFile(ruta + "w_knight.png");
    texturas['B'].loadFromFile(ruta + "w_bishop.png");
    texturas['Q'].loadFromFile(ruta + "w_queen.png");
    texturas['K'].loadFromFile(ruta + "w_king.png");

    // Negras (Minúsculas)
    texturas['p'].loadFromFile(ruta + "b_pawn.png");
    texturas['r'].loadFromFile(ruta + "b_rook.png");
    texturas['n'].loadFromFile(ruta + "b_knight.png");
    texturas['b'].loadFromFile(ruta + "b_bishop.png");
    texturas['q'].loadFromFile(ruta + "b_queen.png");
    texturas['k'].loadFromFile(ruta + "b_king.png");

    // Bucle principal del juego
    while (ventana.isOpen()) {
        // Manejo de eventos en SFML 3.1.0
        while (const std::optional evento = ventana.pollEvent()) {
            if (evento->is<sf::Event::Closed>()) {
                ventana.close();
            }

            // Manejo de clics del mouse
            if (const auto* mousePressed = evento->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    int x = mousePressed->position.x;
                    int y = mousePressed->position.y;
                    int col = x / TAM_CASILLA;
                    int fila = y / TAM_CASILLA;

                    cout << "Clic en casilla -> Fila: " << fila << ", Columna: " << col << endl;
                }
            }
        }

        ventana.clear(sf::Color(50, 50, 50));

        // ==========================================
        // DIBUJADO DEL TABLERO Y LAS PIEZAS
        // ==========================================
        for (int fila = 0; fila < 8; ++fila) {
            for (int col = 0; col < 8; ++col) {
                // 1. Dibujar la casilla
                sf::RectangleShape casilla(sf::Vector2f(TAM_CASILLA, TAM_CASILLA));
                casilla.setPosition({static_cast<float>(col * TAM_CASILLA), static_cast<float>(fila * TAM_CASILLA)});

                if ((fila + col) % 2 == 0) {
                    casilla.setFillColor(sf::Color(240, 217, 181)); // Claro
                } else {
                    casilla.setFillColor(sf::Color(181, 136, 99));  // Oscuro
                }
                ventana.draw(casilla);

                // 2. Dibujar la pieza si la hay en esa posición
                char pieza = juego.getPieza(fila, col);
                if (pieza != '.') {
                    if (texturas.find(pieza) != texturas.end()) {
                        sf::Sprite sprite(texturas[pieza]);

                        // Escalar la imagen automáticamente al tamaño de la casilla (80x80)
                        sf::Vector2u tamTex = texturas[pieza].getSize();
                        if (tamTex.x > 0 && tamTex.y > 0) {
                            float escalaX = static_cast<float>(TAM_CASILLA) / tamTex.x;
                            float escalaY = static_cast<float>(TAM_CASILLA) / tamTex.y;
                            sprite.setScale({escalaX, escalaY});
                        }

                        // Posicionar el sprite en la pantalla
                        sprite.setPosition({static_cast<float>(col * TAM_CASILLA), static_cast<float>(fila * TAM_CASILLA)});
                        ventana.draw(sprite);
                    }
                }
            }
        }

        ventana.display();
    }

    return 0;
}
