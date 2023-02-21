#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>


class Mic {
public:
    Mic(float x, float y, float radius, sf::Color color) {
        mic_tvar.setPosition(x, y);
        mic_tvar.setRadius(radius);
        mic_tvar.setFillColor(color);
    }

    void move(sf::Vector2f velocity) {
        mic_tvar.move(velocity);
    }

    sf::Vector2f getPosition() {
        return mic_tvar.getPosition();
    }
    void setPosition(sf::Vector2f position) 
    {
        mic_tvar.setPosition(position);
    }
    void restarPosition()
    {
        mic_tvar.setPosition(400, 300);
    }

    float getRadius() {
        return mic_tvar.getRadius();
    }

    sf::FloatRect getGlobalBounds() {
        return mic_tvar.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(mic_tvar);
    }

private:
    sf::CircleShape mic_tvar;
};
