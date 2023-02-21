#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include "Obdelnik.h"
#include "mic.h"
using namespace std;



int main() {
    // Hlavni okno
    sf::RenderWindow okno(sf::VideoMode(800, 600), "Pong");
    okno.setFramerateLimit(60);

    // Vytvor levy obdelnik
    Obdelnik levy_obdelnik(0, (600 - 50) / 2, 15, 100, sf::Color::Blue);

    // Vytvor pravy obdélnik
    Obdelnik pravy_obdelnik(785, (600 - 50) / 2, 15, 100, sf::Color::Red);

    // Vytvor mic
    Mic mic(400, 300, 10, sf::Color::White);

    // Urci smer a rychlost mice
    float ballRadius = mic.getRadius();
    int x = std::rand() % 8 + 7;
    int y = std::rand() % 8 + 7;
    sf::Vector2f rychlostMice(x, y);

    int leveSkore = 0;
    int praveSkore = 0;
    bool pohybObdelniku = true;

    // Vytvor font
    sf::Font font;
    if (!font.loadFromFile("C:/Hra/Fonty/font.ttf")) {
        std::cout << "Neda se nacist" << std::endl;
    }

    // text pro leve skore
    sf::Text leveSkoreText;
    leveSkoreText.setFont(font);
    leveSkoreText.setString(std::to_string(leveSkore));;
    leveSkoreText.setCharacterSize(50);
    leveSkoreText.setFillColor(sf::Color::White);
    leveSkoreText.setPosition(20, 20);

    //text pro prave skore
    sf::Text praveSkoreText;
    praveSkoreText.setFont(font);
    praveSkoreText.setString(std::to_string(praveSkore));
    praveSkoreText.setCharacterSize(50);
    praveSkoreText.setFillColor(sf::Color::White);
    praveSkoreText.setPosition(760, 20);

    //text pro vysledek
    sf::Text vysledek;
    vysledek.setFont(font);
    vysledek.setString("The left player wins!");
    vysledek.setCharacterSize(50);
    vysledek.setFillColor(sf::Color::White);
    vysledek.setPosition(220, 20);

    sf::Clock èas;
    bool konecHry = false;
  
    //hlavní loop
    while (okno.isOpen())
    {

        sf::Event event;
        while (okno.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                okno.close();
        }

        okno.clear(sf::Color::Black);

        //Zobraz vse potrebne
        levy_obdelnik.draw(okno);
        pravy_obdelnik.draw(okno);
        mic.draw(okno);

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

        sf::Vector2f micPozice = mic.getPosition();
        sf::Vector2f micRychlost(x, y);

        if (micPozice.y + 2 * mic.getRadius() > 600 || micPozice.y < 0)
            micRychlost.y = -micRychlost.y;
        if (micPozice.x + 2 * mic.getRadius() > 800 || micPozice.x < 0)
            micRychlost.x = -micRychlost.x;

        sf::Vector2f ballPos = mic.getPosition();
        ballPos += rychlostMice;
        mic.setPosition(ballPos);


        if (levy_obdelnik.getGlobalBounds().intersects(mic.getGlobalBounds()) ||
            pravy_obdelnik.getGlobalBounds().intersects(mic.getGlobalBounds()))
        {
            rychlostMice.x = -rychlostMice.x; // Reverse x velocity
        }

        // check if the ball hit the top or bottom
        if (ballPos.y - ballRadius < 0 || ballPos.y + ballRadius > okno.getSize().y)
        {
            rychlostMice.y = -rychlostMice.y; // reverse the vertical velocity
        }
        
        if (mic.getPosition().x + 2 * ballRadius < 0)
        {
            // obnov pravé skóre
            praveSkore++;
            praveSkoreText.setString(std::to_string(praveSkore));

            mic.restarPosition();
        }
        else if(mic.getPosition().x > 800)
        {
            // obnov leve skore
            leveSkore++;
            leveSkoreText.setString(std::to_string(leveSkore));

            // Ball is outside of the screen, restart it
            mic.restarPosition();
        }
        
        //vysledky

        if (leveSkore >= 4)
        {

            rychlostMice = sf::Vector2f(0, 0);
            if (!konecHry) {
                konecHry = true;
                èas.restart();
            }
            pohybObdelniku = false;
            okno.draw(vysledek);
        }
        if (praveSkore >= 4)
        {
            vysledek.setPosition(180, 20);
            vysledek.setString("The right player wins!");

            rychlostMice = sf::Vector2f(0, 0);
            if (!konecHry) {
                konecHry = true;
                èas.restart();
            }
            pohybObdelniku = false;
            okno.draw(vysledek);
        }
        


        if (konecHry && èas.getElapsedTime().asSeconds() > 2)
        {
            okno.draw(vysledek);
            okno.close();
        }
        okno.display();
    }
    
}
