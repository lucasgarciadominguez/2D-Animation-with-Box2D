#pragma once
#include <memory>
#include <box2d/box2d.h>
#include <iostream>
#include "Turret.h"
#include "Vehicle.h"
#include <Platform.h>
namespace AnimationPractice
{
    class CollisionHandler : public b2ContactListener
    {
    public:
        bool enabled = false;
        bool actionPending = false; // Nuevo flag para indicar una acción pendiente
        bool actionPendingSecondMovementPlatform = false; // Nuevo flag para indicar una acción pendiente

        bool platformAscendPending = false;
        std::shared_ptr<Turret> turret;
        std::shared_ptr<Entity> collisionFloor;
        std::shared_ptr<Vehicle> vehicle;
        std::shared_ptr<Platform> platform; // Referencia a la plataforma

        b2Vec2 startPoint; // Punto inicial
        b2Vec2 endPoint;   // Punto final
        float speed;       // Velocidad de la plataforma
        bool movingToEnd;  // Flag para saber hacia dónde se está moviendo
        bool movingUp;     // Flag para saber hacia dónde se está moviendo

        //CollisionHandler(b2Vec2 start, b2Vec2 end, float moveSpeed)
        //    : startPoint(start), endPoint(end), speed(moveSpeed), movingToEnd(true)
        //{
        //}

        void BeginContact(b2Contact* contact) override
        {
            b2Fixture* fixtureA = contact->GetFixtureA();
            b2Fixture* fixtureB = contact->GetFixtureB();
            if (collisionFloor && vehicle && turret)
            {
                if (!enabled)
                {
                    // La colisión es entre la torreta y el vehicle
                    if (fixtureA->IsSensor() || fixtureB->IsSensor())
                    {
                        if ((fixtureA == collisionFloor->body_->GetFixtureList() && fixtureB == vehicle->body_->GetFixtureList()) ||
                            (fixtureB == collisionFloor->body_->GetFixtureList() && fixtureA == vehicle->body_->GetFixtureList()))
                        {
                            std::cout << "Collision between Turret and CollisionFloor detected!" << std::endl;
                            enabled = true;
                            actionPending = true; // Marca que hay una acción pendiente
                            platformAscendPending = true; // Marca que la plataforma debe ascender

                        }
                    }
                }
            }
            if (platform && vehicle )
            {
                if (!movingUp)
                {
                    // La colisión es entre la torreta y el vehicle
                    if (fixtureA->IsSensor() || fixtureB->IsSensor())
                    {
                        if ((fixtureA == platform->body_->GetFixtureList() && fixtureB == vehicle->body_->GetFixtureList()) ||
                            (fixtureB == platform->body_->GetFixtureList() && fixtureA == vehicle->body_->GetFixtureList()))
                        {
                            //std::cout << "Collision between Turret and CollisionFloor detected!" << std::endl;
                            //enabled = true;
                            actionPendingSecondMovementPlatform = true; // Marca que hay una acción pendiente
                            //platformAscendPending = true; // Marca que la plataforma debe ascender

                        }
                    }
                }
            }
        }

        void EndContact(b2Contact* contact) override
        {
            if (enabled)
            {
                collisionFloor->body_->GetFixtureList()->SetSensor(false);
                enabled = false; // Deshabilita la rotación para evitar una rotación continua
            }
        }

        // Método para realizar la acción pendiente en un punto seguro
        void Update()
        {
            if (actionPending)
            {
                turret->rotateCup(10);
                actionPending = false; // Resetea el flag de acción pendiente
            }
            if (platformAscendPending)
            {
                MovePlatform();

            }
            if (actionPendingSecondMovementPlatform)
            {
                platform->body_->GetFixtureList()->SetSensor(false);
                movingUp = true;
                endPoint = b2Vec2(0.f, 8.5f);
            }
        }

        void MovePlatform()
        {
            if (!collisionFloor) return;

            b2Vec2 currentPosition = platform->body_->GetPosition();

            if (movingUp)
            {
                if (currentPosition.y >= endPoint.y)
                {
                    movingUp = false;
                    platform->body_->GetFixtureList()->SetSensor(true);
                }
                else
                {
                    platform->ascend(speed); // Asumimos que ascend() toma la velocidad como parámetro
                }
            }
            else
            {
                if (currentPosition.y <= startPoint.y)
                {
                    //movingUp = true;
                }
                else
                {
                    //platform->descend(speed); // Asumimos que descend() toma la velocidad como parámetro
                }
            }
        }
    };
}