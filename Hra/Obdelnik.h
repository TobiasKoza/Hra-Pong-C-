#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
using namespace std;


class Obdelnik {
public:
    Obdelnik(float x, float y, float width, float height, sf::Color color) {
        obdelnik_tvar.setPosition(x, y);
        obdelnik_tvar.setSize(sf::Vector2f(width, height));
        obdelnik_tvar.setFillColor(color);
    }

    void move(float x, float y) {
        obdelnik_tvar.move(x, y);
    }

    sf::Vector2f getPosition() {
        return obdelnik_tvar.getPosition();
    }


    sf::FloatRect getGlobalBounds() {
        return obdelnik_tvar.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(obdelnik_tvar);
    }

private:
    sf::RectangleShape obdelnik_tvar;
};