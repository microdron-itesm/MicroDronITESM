//
// Created by alberto on 27/02/19.
//

#ifndef CONTROLTESTS_DRONEDRAWABLE_H
#define CONTROLTESTS_DRONEDRAWABLE_H


#include <SFML/Graphics.hpp>

class DroneDrawable : public sf::Drawable{

    explicit DroneDrawable();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


};


#endif //CONTROLTESTS_DRONEDRAWABLE_H
