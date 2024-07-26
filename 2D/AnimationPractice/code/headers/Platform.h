#pragma once
#pragma once
#include <box2d/box2d.h>
#include <memory>
#include "Entity.h"

namespace AnimationPractice
{
    class Platform : public Entity {
    public:

        Platform(Scene& scene, b2BodyType body_type, const std::vector<b2Vec2>& triangleVertices)
            : Entity(scene, body_type, triangleVertices)
        {

        }
        void ascend(float amount) {
            b2Vec2 position = body_->GetPosition();
            position.y += amount;
            body_->SetTransform(position, body_->GetAngle());
        }
    };
}