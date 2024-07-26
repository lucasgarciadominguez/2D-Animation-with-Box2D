#include "Vehicle.h"
#include "Scene.h"
#include <vector>
namespace AnimationPractice
{
    Vehicle::Vehicle(Scene& scene, b2BodyType body_type, float position[], float size[])
        : Entity(scene, body_type, position, size)
    {
        float wheelPos1[2] = { position[0] - size[0] / 2.0f, position[1] - size[1] / 1 };
        float wheelPos2[2] = { position[0] + size[0] / 2.0f, position[1] - size[1] / 1 };
        float wheelSize[2] = { 0.15f, 0.15f }; // Size of the wheels 

        //float vehiclePos[2] = { 1, 3 };
        //float vehicleSize[2] = { .5f, 0.2f }; // vehicle size
        float containerPos[2] = { 0.5f, 2 };
        float containerSize[2] = { .5f, 0.05f }; // Size of the wheels 

        // add the wheels as entities to the vehicle
        std::vector<b2Vec2> verticesContainerLatLeft;
        verticesContainerLatLeft.push_back(b2Vec2(.0f, 2.f));
        verticesContainerLatLeft.push_back(b2Vec2(.1f, 2.f));
        verticesContainerLatLeft.push_back(b2Vec2(.1f, 1.5f));
        verticesContainerLatLeft.push_back(b2Vec2(0.f, 1.5f));
        //vertices.push_back(b2Vec2(.8f, 1.75f));
        std::vector<b2Vec2> verticesContainerCentre;
        verticesContainerCentre.push_back(b2Vec2(.1f, 1.6f));
        verticesContainerCentre.push_back(b2Vec2(.9f, 1.6f));
        verticesContainerCentre.push_back(b2Vec2(.9f, 1.5f));
        verticesContainerCentre.push_back(b2Vec2(.1f, 1.5f));

        std::vector<b2Vec2> verticesContainerLatRight;
        verticesContainerLatRight.push_back(b2Vec2(0.9f, 2.f));
        verticesContainerLatRight.push_back(b2Vec2(1.f, 2.f));
        verticesContainerLatRight.push_back(b2Vec2(1.f, 1.5f));
        verticesContainerLatRight.push_back(b2Vec2(0.9f, 1.5f));


        wheel1 = std::make_shared<Entity>(scene, body_type, wheelPos1, wheelSize[0]);
        wheel2 = std::make_shared<Entity>(scene, body_type, wheelPos2, wheelSize[1]);

        float containerPosCentre[2] = { 0.5f, 1.7 };

        containerLatLeft = std::make_shared<Entity>(scene, b2_dynamicBody, containerPosCentre, verticesContainerLatLeft);
        containerLatRight = std::make_shared<Entity>(scene, b2_dynamicBody, containerPosCentre, verticesContainerLatRight);


        containerCentre = std::make_shared<Entity>(scene, b2_dynamicBody, containerPosCentre, verticesContainerCentre);

        // this adds the wheels as entities to the entity map of the scene
        scene.addEntity("wheel1", wheel1);
        scene.addEntity("wheel2", wheel2);
        scene.addEntity("containerLatLeftCar", containerLatLeft);
        scene.addEntity("containerLatRightCar", containerLatRight);
        scene.addEntity("containerCentreCar", containerCentre);
        // Create joint between the circle and lateral 1
        b2RevoluteJointDef joint_LatLeft;
        joint_LatLeft.Initialize(containerLatLeft->body_, body_, b2Vec2(.1f, 1.5f));
        joint_LatLeft.collideConnected = false;
        joint_LatLeft.enableLimit = true;
        joint_LatLeft.lowerAngle = 80; // Limit -60 degrees
        joint_LatLeft.upperAngle =100;  // Limit 60 degrees
        scene.physics_world_->CreateJoint(&joint_LatLeft);

        //// Create joint between the circle and lateral 1
        b2RevoluteJointDef joint_LatRight;
        joint_LatRight.Initialize(containerLatRight->body_, containerCentre->body_, containerCentre->body_->GetWorldCenter());
        joint_LatRight.collideConnected = false;
        joint_LatRight.enableLimit = true;
        joint_LatRight.lowerAngle = 0; // Limit -45 degrees
        joint_LatRight.upperAngle = 10;  // Limit 60 degrees
        scene.physics_world_->CreateJoint(&joint_LatRight);

        //// Create joint between the circle and lateral 1
        b2RevoluteJointDef joint_ContainerCentre;
        joint_ContainerCentre.Initialize(containerCentre->body_, body_, b2Vec2(.0f, 1.5f));
        joint_ContainerCentre.collideConnected = false;
        scene.physics_world_->CreateJoint(&joint_ContainerCentre);

        //// Create joint between the circle and lateral 1
        b2RevoluteJointDef joint_ContainerCentre2;
        joint_ContainerCentre2.Initialize(containerCentre->body_, body_, b2Vec2(1.0f, 1.5f));
        joint_ContainerCentre2.collideConnected = false;
        scene.physics_world_->CreateJoint(&joint_ContainerCentre2);




        b2RevoluteJointDef joint_def;
        joint_def.Initialize(body_, wheel1->body_, b2Vec2(wheelPos1[0], wheelPos1[1]));

        joint_def.enableMotor = true;

        joint_def.collideConnected = false;

        scene.physics_world_->CreateJoint(&joint_def);

        b2RevoluteJointDef joint_def2;
        joint_def2.Initialize(body_, wheel2->body_, b2Vec2(wheelPos2[0], wheelPos2[1]));

        joint_def2.enableMotor = true;
        joint_def.collideConnected = false;

        scene.physics_world_->CreateJoint(&joint_def2);
    }

    b2RevoluteJointDef* Vehicle::createWheelJoint(b2World& physics_world, b2Body* body, b2Vec2 wheel_position, float wheel_radius)
    {
        b2RevoluteJointDef joint_def;
        joint_def.Initialize(body, nullptr, wheel_position);

        joint_def.enableMotor = true;
        joint_def.maxMotorTorque = 100.0f;
        joint_def.motorSpeed = 0.0f;

        return (b2RevoluteJointDef*)physics_world.CreateJoint(&joint_def);
    }

    Vehicle::~Vehicle()
    {
    }
}