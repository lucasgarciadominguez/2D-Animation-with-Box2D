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

#include <memory>
#include <Entity.h>
#include "CollisionHandler.h"
namespace AnimationPractice
{
    class Renderer;
    class Vehicle;
    class Turret;

    //class b2World;

    class Scene
    {
    public:
        Scene(sf::RenderWindow& renderWindow, float target_fps);
        void run(); // Executes the main loop
        void update(float t);   // Updates a single frame 
        // Calls the Step() method of b2World
        void render();  // Draws all the entities
        void addPlayer(const std::string& name, std::shared_ptr<Vehicle> entity);
        void addTurret(const std::string& name, std::shared_ptr<Turret> entity);
        void addEntity(const std::string& name, std::shared_ptr<Entity> entity);
        ~Scene();
    private:
        bool process(Window& window);

    public:
        b2World* physics_world_;
        CollisionHandler collision_handler_;

    private:
        Renderer* renderer;
        //std::shared_ptr<CollisionHandler> collision_handler_;

        std::map<std::string, std::shared_ptr <Entity >> entities;
        std::shared_ptr <Vehicle > vehicle;
        std::shared_ptr <Turret > turret;
        bool  exit = false;
        float delta_time;
        Clock timer;
        const float target_fps = 60.f;
        float target_time;


    };
}
