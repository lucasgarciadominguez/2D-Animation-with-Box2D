//
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.03+
//
// Controles:
//
//   Espacio: aplicar impulso hacia arriba.
//   Izquierda/derecha: aplicar fuerza de giro.
//   Click->Arrastrar->soltar: aplicar impulso en la dirección seleccionada.
//

#include <ciso646>
#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Scene.h>
#include <Vehicle.h>
#include <Turret.h>
#include "Platform.h"

using namespace sf;
using namespace std;
using namespace  AnimationPractice;

int main ()
{
    constexpr auto window_width  = 1920u;
    constexpr auto window_height = 1080u;

    RenderWindow window(VideoMode(window_width, window_height), "Box2D Forces", Style::Titlebar | Style::Fullscreen, ContextSettings(32));

    window.setVerticalSyncEnabled (true);
    const float target_fps = 60.f;

    Scene scene(window, target_fps);
    float vectorPos[2] = { 4, 4 };
    
    float vectorPos2[2] = { 5, 2 };
    float vectorScale2[2] = { 1,  .2f };

    constexpr float left = 0.01f;
    constexpr float right = 19.20f;
    constexpr float top = 10.80f;
    constexpr float bottom = 0.01f;

    //shared_ptr<Entity> wall1 = make_shared <Entity>(scene, b2_staticBody, left, bottom, right, bottom);
    shared_ptr<Entity> wall2 = make_shared <Entity>(scene, b2_staticBody, left, bottom, left, top);
    shared_ptr<Entity> wall3 = make_shared <Entity>(scene, b2_staticBody, left, top, right, top);
    shared_ptr<Entity> wall4 = make_shared <Entity>(scene, b2_staticBody, right, bottom, right, top);
    float vehiclePos[2] = { 1, 3};
    float vehicleSize[2] = { .5f, 0.2f }; // vehicle size
    std::shared_ptr<Vehicle> vehicle = std::make_shared<Vehicle>(scene, b2_dynamicBody, vehiclePos, vehicleSize);
    scene.collision_handler_.vehicle = vehicle;

    vector<b2Vec2> vertices;
    vertices.push_back(b2Vec2(0.0f, 0.0f));
    vertices.push_back(b2Vec2(0.0f, 1.5f));
    vertices.push_back(b2Vec2(2.0f, 1.5f));  
    vertices.push_back(b2Vec2(2.50f, 1.25f));
    vertices.push_back(b2Vec2(3.f, 1.0f));
    vertices.push_back(b2Vec2(3.5f, 0.75f));
    vertices.push_back(b2Vec2(3.5f, 0.f)); // this vertex closes the polygon

    vector<b2Vec2> vertices2;
    vertices2.push_back(b2Vec2(3.5f, 0.0f));
    vertices2.push_back(b2Vec2(3.5f, 0.75f));
    vertices2.push_back(b2Vec2(6, 0.50f));  
    vertices2.push_back(b2Vec2(6, 0.f));  // this vertex closes the polygon

    vector<b2Vec2> vertices3;
    vertices3.push_back(b2Vec2(6.f, 0.0f));
    vertices3.push_back(b2Vec2(6.f, 0.5f));
    vertices3.push_back(b2Vec2(6.5f, .5f));  
    vertices3.push_back(b2Vec2(7.5f, .65f));  
    vertices3.push_back(b2Vec2(8.f, .75f)); 
    vertices3.push_back(b2Vec2(8.5f, 1.f));  

    vertices3.push_back(b2Vec2(8.5f, 0.f));  // this vertex closes the polygon

    vector<b2Vec2> vertices4;
    vertices4.push_back(b2Vec2(12.f, 0.0f));
    vertices4.push_back(b2Vec2(12.f, 0.5f));
    vertices4.push_back(b2Vec2(17.f, .75f));
    vertices4.push_back(b2Vec2(17., 0.f));  // this vertex closes the polygon

    vector<b2Vec2> verticesFloorSensor;
    verticesFloorSensor.push_back(b2Vec2(17.f, 0.0f));
    verticesFloorSensor.push_back(b2Vec2(17.f, 0.75f));
    verticesFloorSensor.push_back(b2Vec2(20.f, .75f));
    verticesFloorSensor.push_back(b2Vec2(20., 0.f));  // this vertex closes the polygon

    vector<b2Vec2> vertices5;
    vertices5.push_back(b2Vec2(2.5f, 6.0f));
    vertices5.push_back(b2Vec2(2.75f, 6.25f));
    vertices5.push_back(b2Vec2(3.5f, 5.25f));
    vertices5.push_back(b2Vec2(3.5f, 4.75f));

    vector<b2Vec2> vertices6;
    vertices6.push_back(b2Vec2(3.5f, 5.25f));
    vertices6.push_back(b2Vec2(4.25f, 6.25f));
    vertices6.push_back(b2Vec2(4.50f, 6.f));
    vertices6.push_back(b2Vec2(3.5f, 4.75f));

    vector<b2Vec2> verticesSensorFloorUp;
    verticesSensorFloorUp.push_back(b2Vec2(2.75f, 6.25f));
    verticesSensorFloorUp.push_back(b2Vec2(4.25f, 6.25f));
    verticesSensorFloorUp.push_back(b2Vec2(3.5f, 5.25f));

    vector<b2Vec2> vertices7;
    vertices7.push_back(b2Vec2(4.25f, 6.25f));
    vertices7.push_back(b2Vec2(8.5f, 6.25f));
    vertices7.push_back(b2Vec2(8.5f, 6.f));
    vertices7.push_back(b2Vec2(4.5f, 6.f));

    vector<b2Vec2> verticesPlatform;
    verticesPlatform.push_back(b2Vec2(8.5f, -2.50f));
    verticesPlatform.push_back(b2Vec2(8.5f, -2.25f));
    verticesPlatform.push_back(b2Vec2(12.f, -2.25f));
    verticesPlatform.push_back(b2Vec2(12., -2.5f));  // this vertex closes the polygon
    // Create a ramp
    shared_ptr<Entity> ramp1 = make_shared<Entity>(scene, b2_staticBody, vertices);
    shared_ptr<Entity> ramp2 = make_shared<Entity>(scene, b2_staticBody, vertices2);
    shared_ptr<Entity> ramp3 = make_shared<Entity>(scene, b2_staticBody, vertices3);
    shared_ptr<Entity> floor = make_shared<Entity>(scene, b2_staticBody, vertices4);

    shared_ptr<Platform> platform = make_shared<Platform>(scene, b2_kinematicBody, verticesPlatform);
    platform->color = Color::Magenta;

    scene.collision_handler_.platform = platform;
    scene.collision_handler_.startPoint = b2Vec2(0.f, 0.0f);
    scene.collision_handler_.endPoint = b2Vec2(0.f, 2.75f);
    scene.collision_handler_.speed = 0.01f;

    shared_ptr<Entity> floorSensor = make_shared<Entity>(scene, b2_staticBody, verticesFloorSensor);
    scene.collision_handler_.collisionFloor = floorSensor;
    floorSensor->color = Color::Green;

    b2Fixture* fixture = floorSensor->body_->GetFixtureList();
    fixture->SetSensor(true);

    //create the floor
    shared_ptr<Entity> floorUp1 = make_shared<Entity>(scene, b2_staticBody, vertices5);
    floorUp1->color = Color::Cyan;

    shared_ptr<Entity> floorUp2 = make_shared<Entity>(scene, b2_staticBody, vertices6);
    floorUp2->color = Color::Cyan;

    shared_ptr<Entity> floorUpSensor = make_shared<Entity>(scene, b2_staticBody, verticesSensorFloorUp);
    floorUpSensor->color = Color::Color(255,0,0,100);
    floorUpSensor->body_->GetFixtureList()->SetSensor(true);


    shared_ptr<Entity> floorUp3 = make_shared<Entity>(scene, b2_staticBody, vertices7);


    // coordinates for the last vertices
    float lastX = 1.35f;
    float lastY = 0.25f;

    // define all the vertices for the lateral of the turret
    std::vector<b2Vec2> rectVertices;
    rectVertices.push_back(b2Vec2(0.5f - lastX, 3.0f - lastY));
    rectVertices.push_back(b2Vec2(0.75f - lastX, 3.25f - lastY));
    rectVertices.push_back(b2Vec2(1.5f - lastX, 2.25f - lastY));
    rectVertices.push_back(b2Vec2(1.5f - lastX, 1.75f - lastY));

    // define all the vertices for the lateral of the turret
    std::vector<b2Vec2> rectVertices2;
    rectVertices2.push_back(b2Vec2(1.5f - lastX, 2.25f - lastY));
    rectVertices2.push_back(b2Vec2(2.25f - lastX, 3.25f - lastY));
    rectVertices2.push_back(b2Vec2(2.50f - lastX, 3.0f - lastY));
    rectVertices2.push_back(b2Vec2(1.5f - lastX, 1.75f - lastY));

    // define all the vertices for the base of the turret
    std::vector<b2Vec2> baseVertices;
    baseVertices.push_back(b2Vec2(1.35f - lastX, 2.25f - lastY));
    baseVertices.push_back(b2Vec2(1.65f - lastX, 2.25f - lastY));
    baseVertices.push_back(b2Vec2(1.65f - lastX, 0.5f - lastY));
    baseVertices.push_back(b2Vec2(1.35f - lastX, 0.5f - lastY));

    float vectorPosTurret[2] = { 17, 0.5f };
    // create the turret
    std::shared_ptr<Turret> turret = std::make_shared<Turret>(scene, b2_kinematicBody, vectorPosTurret, rectVertices, rectVertices2, baseVertices);
    scene.collision_handler_.turret = turret;

    // Agregar la torreta a la escena
    scene.addTurret("turret", turret);
    scene.addEntity("ramp1", ramp1);
    scene.addEntity("ramp2", ramp2);
    scene.addEntity("ramp3", ramp3);
    scene.addEntity("floor", floor);
    scene.addEntity("platform", platform);

    scene.addEntity("floorSensor", floorSensor);

    scene.addEntity("floorUp1", floorUp1);
    scene.addEntity("floorUp2", floorUp2);
    scene.addEntity("floorUpSensor", floorUpSensor);

    scene.addEntity("floorUp3", floorUp3);

    //scene.addEntity("wall1", wall1);
    scene.addEntity("wall2", wall2);
    scene.addEntity("wall3", wall3);
    scene.addEntity("wall4", wall4);
    scene.addPlayer("vehicle", vehicle);

    for (size_t i = 0; i < 5; i++)
    {
        float vehiclePos[2] = { 17, 2.5f + i };

        shared_ptr<Entity> circle = make_shared <Entity>(scene, b2_dynamicBody, vehiclePos, .1);
        scene.addEntity("circle"+i, circle);

    }
    scene.run();

    return 0;
}
