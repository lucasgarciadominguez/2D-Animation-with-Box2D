
/**********************************************************************
*Project           : AnimationPractice
*
*Author : Lucas García
*
*
*Purpose : 2D Animation project of an scene showing different examples 
*
**********************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
namespace AnimationPractice
{
    class Entity;
    class Renderer
    {
    public:
        Renderer(sf::RenderWindow& window, b2World& physics_world);
        ~Renderer();

        void render(std::map<std::string, std::shared_ptr<Entity>> entities);

        sf::RenderWindow& window_;

    private:
        b2World& physics_world_;
    };
}

