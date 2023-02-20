#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>


class M�� {
public:
    M��(float x, float y, float radius, sf::Color color) {
        m��_tvar.setPosition(x, y);
        m��_tvar.setRadius(radius);
        m��_tvar.setFillColor(color);
    }

    void move(sf::Vector2f velocity) {
        m��_tvar.move(velocity);
    }

    sf::Vector2f getPosition() {
        return m��_tvar.getPosition();
    }
    void setPosition(sf::Vector2f position) 
    {
        m��_tvar.setPosition(position);
    }
    void restarPosition()
    {
        m��_tvar.setPosition(400, 300);
    }

    float getRadius() {
        return m��_tvar.getRadius();
    }

    sf::FloatRect getGlobalBounds() {
        return m��_tvar.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m��_tvar);
    }

private:
    sf::CircleShape m��_tvar;
};
