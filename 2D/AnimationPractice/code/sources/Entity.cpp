#include "Entity.h"
#include "Scene.h"
#include <vector>

namespace AnimationPractice
{
    Entity::Entity(Scene& scene, b2BodyType body_type, float position[], float radius)
    {
        // Create the body:
        b2BodyDef body_definition;
        body_definition.type = body_type;
        body_definition.position.Set(position[0], position[1]); // Absolute initial position
        body_ = scene.physics_world_->CreateBody(&body_definition);

        // Add a fixture:
        b2CircleShape body_shape;
        body_shape.m_radius = radius;

        b2FixtureDef body_fixture;
        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.75f;
        body_fixture.friction = 0.50f;

        body_->CreateFixture(&body_fixture);
        color = Color::Blue;
    }

    Entity::Entity(Scene& scene, b2BodyType body_type, float position[], float size[])
    {
        b2BodyDef body_definition;
        body_definition.type = body_type;
        body_definition.position.Set(position[0], position[1]); // Absolute initial position
        body_ = scene.physics_world_->CreateBody(&body_definition);

        // Add a fixture:
        b2PolygonShape body_shape;
        body_shape.SetAsBox(size[0], size[1]);

        b2FixtureDef body_fixture;
        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction = 0.50f;

        body_->CreateFixture(&body_fixture);
        color = Color::Yellow;

    }

    Entity::Entity(Scene& scene, b2BodyType body_type, const std::vector<b2Vec2>& vertices)
    {
        b2BodyDef body_definition;
        body_definition.type = body_type;
        body_definition.position.Set(0, 0); // Absolute initial position
        body_ = scene.physics_world_->CreateBody(&body_definition);

        // Create a polygon shape using the provided vertices
        b2PolygonShape body_shape;
        body_shape.Set(vertices.data(), vertices.size());

        // Create a fixture and assign the polygon shape to it
        b2FixtureDef body_fixture;
        body_fixture.shape = &body_shape;
        body_fixture.density = 1.0f;   // Adjust as needed
        body_fixture.restitution = 0.0f; // Adjust as needed
        body_fixture.friction = 0.5f;    // Adjust as needed

        body_->CreateFixture(&body_fixture);
        color = Color::Yellow;

    }

    Entity::Entity(Scene& scene, b2BodyType body_type, float position[], const std::vector<b2Vec2>& vertices)
    {
        b2BodyDef body_definition;
        body_definition.type = body_type;
        body_definition.position.Set(position[0], position[1]); // Absolute initial position
        body_ = scene.physics_world_->CreateBody(&body_definition);

        // Create a polygon shape using the provided vertices
        b2PolygonShape body_shape;
        body_shape.Set(vertices.data(), vertices.size());

        // Create a fixture and assign the polygon shape to it
        b2FixtureDef body_fixture;
        body_fixture.shape = &body_shape;
        body_fixture.density = 1.0f;   // Adjust as needed
        body_fixture.restitution = 0.0f; // Adjust as needed
        body_fixture.friction = 0.5f;    // Adjust as needed

        body_->CreateFixture(&body_fixture);
        color = Color::Yellow;

    }

    Entity::Entity(Scene& scene, b2BodyType body_type, float x0, float y0, float x1, float y1)
    {
        b2BodyDef body_definition;
        body_definition.type = body_type;
        body_definition.position.Set(0.f, 0.f); // Absolute initial position
        body_ = scene.physics_world_->CreateBody(&body_definition);

        // Add a fixture:
        b2EdgeShape body_shape;
        body_shape.SetTwoSided(b2Vec2(x0, y0), b2Vec2(x1, y1)); // Local coordinates relative to the body center

        b2FixtureDef body_fixture;
        body_fixture.shape = &body_shape;

        body_->CreateFixture(&body_fixture);
        color = Color::Yellow;

    }

    Entity::~Entity()
    {
        // You could destroy the body here if needed
    }
}