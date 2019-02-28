//
// Created by alberto on 27/02/19.
//

#include "PropellerDrawable.h"


PropellerDrawable::PropellerDrawable(int size) : PropellerDrawable::CircleShape(size) {

}

double PropellerDrawable::getCurrentSpeed() const {
    return currentSpeed;
}

void PropellerDrawable::setCurrentSpeed(double currentSpeed) {
    this->currentSpeed = currentSpeed;

    if(std::abs(this->currentSpeed) > maxSpeed){
        this->currentSpeed = std::copysign(maxSpeed, currentSpeed);
    }
}

void PropellerDrawable::update() {
    Shape::update();
    double percentCurrentSpeed = currentSpeed / maxSpeed;

    if(percentCurrentSpeed > 0){
        currentColor =sf::Color(0, static_cast<sf::Uint8>( 255 * percentCurrentSpeed), 0);
    }else if(percentCurrentSpeed < 0){
        currentColor =sf::Color(static_cast<sf::Uint8>( 255 * std::abs(percentCurrentSpeed)), 0, 0);
    }else{
        currentColor =sf::Color(0, 0, 0);
    }
    setFillColor(currentColor);
}

