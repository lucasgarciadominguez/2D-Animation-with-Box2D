#pragma once

#include "Entity.h"

namespace AnimationPractice
{

    class Vehicle : public Entity
    {

    public:
        Vehicle(Scene& scene, b2BodyType body_type, float position[], float size[]);
        ~Vehicle();
        std::shared_ptr<Entity> wheel1;
        std::shared_ptr<Entity> wheel2;
        std::shared_ptr<Entity> containerLatLeft;
        std::shared_ptr<Entity> containerLatRight;
        std::shared_ptr<Entity> containerCentre;
        std::shared_ptr<Entity> circleContainer;

    private:
        b2RevoluteJointDef* createWheelJoint(b2World& physics_world, b2Body* body, b2Vec2 wheel_position, float wheel_radius);

    };
}