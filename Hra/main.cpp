#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include "Obdelnik.h"
#include "Míè.h"
using namespace std;



int main() {
    // Hlavní okno
    sf::RenderWindow okno(sf::VideoMode(800, 600), "Pong");
    okno.setFramerateLimit(60);

    // Vytvoø levé obdélník
    Obdelnik levy_obdelnik(0, (600 - 50) / 2, 15, 100, sf::Color::Blue);

    // Vytvoø pravý obdélník
    Obdelnik pravy_obdelnik(785, (600 - 50) / 2, 15, 100, sf::Color::Red);

    // Vytvoø míè
    Míè míè(400, 300, 10, sf::Color::White);

    // Urèi smìr a rychlost míèe
    float ballRadius = míè.getRadius();
    int x = std::rand() % 8 + 7;
    int y = std::rand() % 8 + 7;
    sf::Vector2f rychlostMíèe(x, y);

    int levéSkore = 0;
    int pravéSkore = 0;
    bool pohybObdelniku = true;

    // Vytvoø font
    sf::Font font;
    if (!font.loadFromFile("C:/Hra/Fonty/font.ttf")) {
        std::cout << "Neda se nacist" << std::endl;
    }

    // text pro levé skóre
    sf::Text leveSkoreText;
    leveSkoreText.setFont(font);
    leveSkoreText.setString(std::to_string(levéSkore));;
    leveSkoreText.setCharacterSize(50);
    leveSkoreText.setFillColor(sf::Color::White);
    leveSkoreText.setPosition(20, 20);

    //text pro pravé skore
    sf::Text praveSkoreText;
    praveSkoreText.setFont(font);
    praveSkoreText.setString(std::to_string(pravéSkore));
    praveSkoreText.setCharacterSize(50);
    praveSkoreText.setFillColor(sf::Color::White);
    praveSkoreText.setPosition(760, 20);

    //text pro výsledek
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

        //Zobraz vše potøebné
        levy_obdelnik.draw(okno);
        pravy_obdelnik.draw(okno);
        míè.draw(okno);

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

        sf::Vector2f míèPozice = míè.getPosition();
        sf::Vector2f míèRychlost(x, y);

        if (míèPozice.y + 2 * míè.getRadius() > 600 || míèPozice.y < 0)
            míèRychlost.y = -míèRychlost.y;
        if (míèPozice.x + 2 * míè.getRadius() > 800 || míèPozice.x < 0)
            míèRychlost.x = -míèRychlost.x;

        sf::Vector2f ballPos = míè.getPosition();
        ballPos += rychlostMíèe;
        míè.setPosition(ballPos);


        if (levy_obdelnik.getGlobalBounds().intersects(míè.getGlobalBounds()) ||
            pravy_obdelnik.getGlobalBounds().intersects(míè.getGlobalBounds()))
        {
            rychlostMíèe.x = -rychlostMíèe.x; // Reverse x velocity
        }

        // check if the ball hit the top or bottom
        if (ballPos.y - ballRadius < 0 || ballPos.y + ballRadius > okno.getSize().y)
        {
            rychlostMíèe.y = -rychlostMíèe.y; // reverse the vertical velocity
        }
        
        if (míè.getPosition().x + 2 * ballRadius < 0)
        {
            // obnov pravé skóre
            pravéSkore++;
            praveSkoreText.setString(std::to_string(pravéSkore));

            míè.restarPosition();
        }
        else if(míè.getPosition().x > 800)
        {
            // obnov levé skóre
            levéSkore++;
            leveSkoreText.setString(std::to_string(levéSkore));

            // Ball is outside of the screen, restart it
            míè.restarPosition();
        }
        
        //výsledky

        if (levéSkore >= 4)
        {

            rychlostMíèe = sf::Vector2f(0, 0);
            if (!konecHry) {
                konecHry = true;
                èas.restart();
            }
            pohybObdelniku = false;
            okno.draw(vysledek);
        }
        if (pravéSkore >= 4)
        {
            vysledek.setPosition(180, 20);
            vysledek.setString("The right player wins!");

            rychlostMíèe = sf::Vector2f(0, 0);
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
