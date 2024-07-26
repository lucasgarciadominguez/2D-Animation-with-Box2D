#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
namespace AnimationPractice
{
    class Scene;
    class Entity
    {
        public:
            Entity(Scene& scene, b2BodyType body_type, float position[], float radius); //generate a circle
            Entity(Scene& scene,  b2BodyType body_type, float position[], float size[]);
            Entity(Scene& scene, b2BodyType body_type, const std::vector<b2Vec2>& vertices);
            Entity(Scene& scene, b2BodyType body_type, float position[], const std::vector<b2Vec2>& vertices);
            //generate a box
            Entity(Scene& scene, b2BodyType body_type,  float x0,float x1,float x2, float x4);   //generate an edge

            ~Entity();

            b2Body* body_;
            Color color;

        private:
            std::unique_ptr<sf::Shape> shape_;
    };
}