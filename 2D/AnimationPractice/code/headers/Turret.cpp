#include "Turret.h"
#include "Scene.h"

namespace AnimationPractice
{
    Turret::Turret(Scene& scene, b2BodyType body_type, float position[], const std::vector<b2Vec2>& rectVertices1,
        const std::vector<b2Vec2>& rectVertices2, const std::vector<b2Vec2>& triangleVertices)
        : Entity(scene, body_type, position, triangleVertices)
    {
        // Crear la esfera central
        float circlePos1[2] = { position[0] + 0.2f , position[1] + 1.75f };
        circle = std::make_shared<Entity>(scene, b2_kinematicBody, circlePos1, 0.2f);

        // Hacer que el cuerpo principal sea un sensor
        b2Fixture* fixture = body_->GetFixtureList();
        fixture->SetSensor(true);

        // Crear los cuerpos laterales
        lateral = std::make_shared<Entity>(scene, b2_kinematicBody, position, rectVertices1);
        lateral2 = std::make_shared<Entity>(scene, b2_kinematicBody, position, rectVertices2);

        scene.addEntity("circleTurret", circle);
        scene.addEntity("lateralLTurret", lateral);
        scene.addEntity("lateralRTurret", lateral2);

        //// Create joint between the circle and lateral 1
        b2RevoluteJointDef joint_def1;
        joint_def1.Initialize(lateral->body_, circle->body_, circle->body_->GetWorldCenter());
        joint_def1.collideConnected = false;
        joint_def1.enableLimit = true;
        joint_def1.lowerAngle = -b2_pi / 3; // Limite inferior -45 grados
        joint_def1.upperAngle = b2_pi / 3;  // Limite superior 45 grados
        scene.physics_world_->CreateJoint(&joint_def1);

        //// Create joint between the circle and lateral 2
        b2RevoluteJointDef joint_def2;
        joint_def2.Initialize(lateral2->body_, circle->body_, circle->body_->GetWorldCenter());
        joint_def2.collideConnected = false;
        joint_def2.enableLimit = true;
        joint_def2.lowerAngle = -b2_pi / 3; // Limite inferior -45 grados
        joint_def2.upperAngle = b2_pi / 3;  // Limite superior 45 grados
        scene.physics_world_->CreateJoint(&joint_def2);

        //// Configurar the motor in the sphere for rotating
        //b2RevoluteJointDef motorJointDef;
        //motorJointDef.bodyA = circle->body_;
        //motorJointDef.bodyB = body_;
        //motorJointDef.localAnchorA.Set(0.0f, 0.0f);
        //motorJointDef.localAnchorB.Set(0.0f, 0.0f);
        //motorJointDef.enableMotor = true;
        //motorJointDef.motorSpeed = 1.0f; // Radians per second
        //motorJointDef.maxMotorTorque = 10.0f; 

        //motorJoint = (b2RevoluteJoint*)scene.physics_world_->CreateJoint(&motorJointDef);
    }

    Turret::~Turret()
    {
    }

    void Turret::rotateCup(float angle)
    {
        lateral->body_->SetType(b2_dynamicBody);
        lateral2->body_->SetType(b2_dynamicBody);
        //circle->body_->SetType(b2_dynamicBody);

        //lateral ->body_->GetFixtureList()->SetSensor(true);
        //lateral2->body_->GetFixtureList()->SetSensor(true);
            // Aplicar velocidad angular a los laterales
        lateral->body_->SetAngularVelocity(-angle);
        lateral2->body_->SetAngularVelocity(-angle);
        // Apply force to the circle
        //motorJoint->SetMotorSpeed(angle); 
        //circle->body_->SetAngularVelocity(-10010);

    }
}