#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace AnimationPractice
{
    class Turret : public Entity
    {
    public:
        Turret(Scene& scene, b2BodyType body_type, float position[], const std::vector<b2Vec2>& rectVertices1, const std::vector<b2Vec2>& rectVertices2, const std::vector<b2Vec2>& triangleVertices);
        ~Turret();

        void rotateCup(float angle);
        //void dumpBalls();
        std::shared_ptr<Entity> circle;

    private:
        std::shared_ptr<Entity> lateral;
        std::shared_ptr<Entity> lateral2;
        b2RevoluteJoint* motorJoint;

    };
}