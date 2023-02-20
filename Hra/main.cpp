#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include "Obdelnik.h"
#include "M��.h"
using namespace std;



int main() {
    // Hlavn� okno
    sf::RenderWindow okno(sf::VideoMode(800, 600), "Pong");
    okno.setFramerateLimit(60);

    // Vytvo� lev� obd�ln�k
    Obdelnik levy_obdelnik(0, (600 - 50) / 2, 15, 100, sf::Color::Blue);

    // Vytvo� prav� obd�ln�k
    Obdelnik pravy_obdelnik(785, (600 - 50) / 2, 15, 100, sf::Color::Red);

    // Vytvo� m��
    M�� m��(400, 300, 10, sf::Color::White);

    // Ur�i sm�r a rychlost m��e
    float ballRadius = m��.getRadius();
    int x = std::rand() % 8 + 7;
    int y = std::rand() % 8 + 7;
    sf::Vector2f rychlostM��e(x, y);

    int lev�Skore = 0;
    int prav�Skore = 0;
    bool pohybObdelniku = true;

    // Vytvo� font
    sf::Font font;
    if (!font.loadFromFile("C:/Hra/Fonty/font.ttf")) {
        std::cout << "Neda se nacist" << std::endl;
    }

    // text pro lev� sk�re
    sf::Text leveSkoreText;
    leveSkoreText.setFont(font);
    leveSkoreText.setString(std::to_string(lev�Skore));;
    leveSkoreText.setCharacterSize(50);
    leveSkoreText.setFillColor(sf::Color::White);
    leveSkoreText.setPosition(20, 20);

    //text pro prav� skore
    sf::Text praveSkoreText;
    praveSkoreText.setFont(font);
    praveSkoreText.setString(std::to_string(prav�Skore));
    praveSkoreText.setCharacterSize(50);
    praveSkoreText.setFillColor(sf::Color::White);
    praveSkoreText.setPosition(760, 20);

    //text pro v�sledek
    sf::Text vysledek;
    vysledek.setFont(font);
    vysledek.setString("The left player wins!");
    vysledek.setCharacterSize(50);
    vysledek.setFillColor(sf::Color::White);
    vysledek.setPosition(220, 20);

    sf::Clock �as;
    bool konecHry = false;
  
    //hlavn� loop
    while (okno.isOpen())
    {

        sf::Event event;
        while (okno.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                okno.close();
        }

        okno.clear(sf::Color::Black);

        //Zobraz v�e pot�ebn�
        levy_obdelnik.draw(okno);
        pravy_obdelnik.draw(okno);
        m��.draw(okno);

        okno.draw(leveSkoreText);
        okno.draw(praveSkoreText);

        if (pohybObdelniku)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && levy_obdelnik.getPosition().y > 0)
                levy_obdelnik.move(0, -10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && levy_obdelnik.getPosition().y < 500)
                levy_obdelnik.move(0, 10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pravy_obdelnik.getPosition().y > 0)
                pravy_obdelnik.move(0, -10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pravy_obdelnik.getPosition().y < 500)
                pravy_obdelnik.move(0, 10);
        }

        sf::Vector2f m��Pozice = m��.getPosition();
        sf::Vector2f m��Rychlost(x, y);

        if (m��Pozice.y + 2 * m��.getRadius() > 600 || m��Pozice.y < 0)
            m��Rychlost.y = -m��Rychlost.y;
        if (m��Pozice.x + 2 * m��.getRadius() > 800 || m��Pozice.x < 0)
            m��Rychlost.x = -m��Rychlost.x;

        sf::Vector2f ballPos = m��.getPosition();
        ballPos += rychlostM��e;
        m��.setPosition(ballPos);


        if (levy_obdelnik.getGlobalBounds().intersects(m��.getGlobalBounds()) ||
            pravy_obdelnik.getGlobalBounds().intersects(m��.getGlobalBounds()))
        {
            rychlostM��e.x = -rychlostM��e.x; // Reverse x velocity
        }

        // check if the ball hit the top or bottom
        if (ballPos.y - ballRadius < 0 || ballPos.y + ballRadius > okno.getSize().y)
        {
            rychlostM��e.y = -rychlostM��e.y; // reverse the vertical velocity
        }
        
        if (m��.getPosition().x + 2 * ballRadius < 0)
        {
            // obnov prav� sk�re
            prav�Skore++;
            praveSkoreText.setString(std::to_string(prav�Skore));

            m��.restarPosition();
        }
        else if(m��.getPosition().x > 800)
        {
            // obnov lev� sk�re
            lev�Skore++;
            leveSkoreText.setString(std::to_string(lev�Skore));

            // Ball is outside of the screen, restart it
            m��.restarPosition();
        }
        
        //v�sledky

        if (lev�Skore >= 4)
        {

            rychlostM��e = sf::Vector2f(0, 0);
            if (!konecHry) {
                konecHry = true;
                �as.restart();
            }
            pohybObdelniku = false;
            okno.draw(vysledek);
        }
        if (prav�Skore >= 4)
        {
            vysledek.setPosition(180, 20);
            vysledek.setString("The right player wins!");

            rychlostM��e = sf::Vector2f(0, 0);
            if (!konecHry) {
                konecHry = true;
                �as.restart();
            }
            pohybObdelniku = false;
            okno.draw(vysledek);
        }
        


        if (konecHry && �as.getElapsedTime().asSeconds() > 2)
        {
            okno.draw(vysledek);
            okno.close();
        }
        okno.display();
    }
    
}
