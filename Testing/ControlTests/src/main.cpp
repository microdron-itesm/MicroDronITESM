/**
 * Alberto Jahuey Moncada
 *
 * Tool used to simulate the drone algorithms
 *
 * */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "PropellerDrawable.h"

int main() {
    unsigned int screenHeight = sf::VideoMode::getDesktopMode().height;
    unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;

    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenWidth * 0.75),
                                          static_cast<unsigned int>(screenHeight * 0.9)), "EctoSim", sf::Style::Close);
    window.setFramerateLimit(60);
    PropellerDrawable bottomLeftProp;
    PropellerDrawable bottomRightProp;
    PropellerDrawable topLeftProp;
    PropellerDrawable topRightProp;

    bottomLeftProp.setPosition(100,600);
    topLeftProp.setPosition(100, 500);

    bottomRightProp.setPosition(200,600);
    topRightProp.setPosition(200,500);

    double w1, w2, w3, w4;

    double pitchRate, rollRate, yawRate, thrust, k;

    pitchRate = 0;
    rollRate = 0;
    yawRate = 0;
    thrust = 1.0;

    k = 1.0;


    while (window.isOpen()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            rollRate = -0.5;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            rollRate = 0.5;
        }else{
            rollRate = 0.0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            pitchRate = -0.5;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            pitchRate = 0.5;
        }else{
            pitchRate = 0.0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            yawRate = -0.5;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            yawRate = 0.5;
        }else{
            yawRate = 0.0;
        }

        w1 = yawRate * k - pitchRate * k + rollRate * k + thrust * k;
        w2 = yawRate * k + pitchRate * k + rollRate * k - thrust * k;
        w3 = yawRate * k - pitchRate * k - rollRate * k - thrust * k;
        w4 = yawRate * k + pitchRate * k - rollRate * k + thrust * k;

        printf("%f %f %f %f\n", w1, w2, w3, w4);
        bottomLeftProp.setCurrentSpeed(w1);
        bottomRightProp.setCurrentSpeed(w2);

        topLeftProp.setCurrentSpeed(w3);
        topRightProp.setCurrentSpeed(w4);

        bottomLeftProp.update();
        bottomRightProp.update();
        topLeftProp.update();
        topRightProp.update();

        sf::Event event;
        while (window.pollEvent(event)) {


            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                window.setView(
                        sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }




        window.clear(sf::Color(100,100,100));
        window.draw(bottomLeftProp);
        window.draw(bottomRightProp);
        window.draw(topLeftProp);
        window.draw(topRightProp);

        window.display();
    }

    return 0;
}