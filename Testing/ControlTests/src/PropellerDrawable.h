//
// Created by alberto on 27/02/19.
//

#ifndef CONTROLTESTS_PROPELLERDRAWABLE_H
#define CONTROLTESTS_PROPELLERDRAWABLE_H


#include <SFML/Graphics.hpp>
#include <math.h>

class PropellerDrawable : public sf::CircleShape {
public:
    explicit PropellerDrawable(int size = 10);
    double getCurrentSpeed() const;
    void setCurrentSpeed(double currentSpeed);
    void update();
private:
    double currentSpeed;
    const double maxSpeed = 1;

    sf::Color fullRightColor {255,0,0}; // RED
    sf::Color fullLeftColor {0,255,0}; // GREEN
    sf::Color currentColor {0,0,0}; //Defaults to black

};


#endif //CONTROLTESTS_PROPELLERDRAWABLE_H
