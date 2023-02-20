#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>


class Mни {
public:
    Mни(float x, float y, float radius, sf::Color color) {
        mни_tvar.setPosition(x, y);
        mни_tvar.setRadius(radius);
        mни_tvar.setFillColor(color);
    }

    void move(sf::Vector2f velocity) {
        mни_tvar.move(velocity);
    }

    sf::Vector2f getPosition() {
        return mни_tvar.getPosition();
    }
    void setPosition(sf::Vector2f position) 
    {
        mни_tvar.setPosition(position);
    }
    void restarPosition()
    {
        mни_tvar.setPosition(400, 300);
    }

    float getRadius() {
        return mни_tvar.getRadius();
    }

    sf::FloatRect getGlobalBounds() {
        return mни_tvar.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(mни_tvar);
    }

private:
    sf::CircleShape mни_tvar;
};
