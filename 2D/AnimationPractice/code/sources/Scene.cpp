#include "Scene.h"
#include "Renderer.h"
#include <Box2D/Box2D.h>
#include <memory>
#include <ciso646>
#include <Vehicle.h>
#include <Turret.h>
#include "CollisionHandler.h"
namespace AnimationPractice
{
    Scene::~Scene()
    {
        delete renderer;
        delete physics_world_;
    }

    bool Scene::process(Window& window)
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::KeyPressed:
            {
                switch (event.key.code)
                {
                case Keyboard::Left:
                {
                    vehicle->wheel1->body_->SetLinearDamping(0.f); 
                    vehicle->wheel2->body_->SetLinearDamping(0.f); 
                    vehicle->wheel1->body_->ApplyTorque(+25, true);
                    vehicle->wheel2->body_->ApplyTorque(+25, true);

                    break;
                }
                case Keyboard::Right:
                {
                    vehicle->wheel1->body_->SetLinearDamping(0.f); 
                    vehicle->wheel2->body_->SetLinearDamping(0.f); 
                    vehicle->wheel1->body_->ApplyTorque(-25, true);
                    vehicle->wheel2->body_->ApplyTorque(-25, true);

                    break;
                }
                case Keyboard::Down:
                {
                    vehicle->wheel1->body_->SetLinearDamping(10.0f); 
                    vehicle->wheel2->body_->SetLinearDamping(10.0f); 

                    break;
                }
                case Keyboard::R:
                {
                    //b2Vec2 force(10.0f, 0.0f); 
                    //turret->rotateCup(2);
                    //vehicle->containerLatLeft->body_->SetType(b2_dynamicBody);

                    //vehicle->containerLatLeft->body_->SetAngularVelocity(-10.0f);
                    //vehicle->containerLatLeft->body_->SetAngularVelocity(-10.0f);

                    break;
                }
                }

                break;
            }

            case Event::Closed:
            {
                return true;
            }
            }
        }

        return false;
    }

    Scene::Scene(sf::RenderWindow& renderWindow, float target_fps)
    {

        b2Vec2 gravity(0, -10.f); // define gravity
        physics_world_ = new b2World{ gravity }; // initialize Box2D world
        //collision_handler_ = std::make_shared<CollisionHandler>();
        //AnimationPractice::CollisionHandler collisionHandler(b2Vec2(3.5f, 5.25f), b2Vec2(3.5f, 5.25f), 2.f);
        //collision_handler_ = collisionHandler;
        physics_world_->SetContactListener(&collision_handler_);

        renderer = new Renderer{ renderWindow, *physics_world_ };
        target_time = 1.f / target_fps;
        delta_time = target_time;                     // estimated duration of the current frame

    }

    void Scene::run()
    {
        // Main loop
        do
        {
            timer.restart();

            exit = process(renderer->window_);

            update(delta_time);
            render();
            float elapsed = timer.getElapsedTime().asSeconds();

            if (elapsed < target_time)
            {
                sleep(seconds(target_time - elapsed));
            }

            // reset estimation of the duration of the next frame:
            delta_time = timer.getElapsedTime().asSeconds();
            collision_handler_.Update();


        } while (not exit);
    }

    void Scene::update(float t)
    {
        // Update Box2D world
        physics_world_->Step(t, 8, 4);
    }

    void Scene::render()
    {
        renderer->render(entities);
    }
    void Scene::addPlayer(const std::string& name, std::shared_ptr<Vehicle> _vehicle)
    {
        entities[name] = _vehicle;
        vehicle = _vehicle;
    }
    void Scene::addTurret(const std::string& name, std::shared_ptr<Turret> _turret)
    {
        entities[name] = _turret;
        turret = _turret;
    }
    void Scene::addEntity(const std::string& name, std::shared_ptr<Entity> entity)
    {
        entities[name] = entity;
    }


}