
/**********************************************************************
*Project           : AnimationPractice
*
*Author : Lucas García
*
*
*Purpose : 2D Animation project of an scene showing different examples
*
**********************************************************************/
#include "Renderer.h"
#include <Entity.h>
#include <memory>
namespace AnimationPractice
{

    Renderer::Renderer(sf::RenderWindow& window, b2World& physics_world)
        : window_(window), physics_world_(physics_world)
    {
        // Constructor
    }

    Renderer::~Renderer()
    {
        // Destructor
    }
    inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
    {
        return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
    }

    void render_circle
    (
        b2Vec2              center,
        float               radius,
        const b2Transform& transform,
        RenderWindow& renderer,
        float               window_height,
        float               scale
    )
    {
        CircleShape shape;

        radius *= scale;

        shape.setPosition(box2d_position_to_sfml_position(b2Mul(transform, center), window_height, scale) - Vector2f(radius, radius));
        shape.setRadius(radius);
        shape.setFillColor(Color::Blue);
        renderer.draw(shape);
    }
    // ------------------------------------------------------------------------------------------ //

    void render_segment
    (
        const Vector2f& start,
        const Vector2f& end,
        const Color& color,
        RenderWindow& renderer
    )
    {
        Vertex line[] =
        {
            Vertex(start, color),
            Vertex(end, color),
        };

        renderer.draw(line, 2, Lines);
    }

    // ------------------------------------------------------------------------------------------ //

    void render_segment
    (
        b2Vec2              start,
        b2Vec2              end,
        const b2Transform& transform,
        RenderWindow& renderer,
        float               window_height,
        float               scale
    )
    {
        start = b2Mul(transform, start);
        end = b2Mul(transform, end);

        render_segment
        (
            box2d_position_to_sfml_position(start, window_height, scale),
            box2d_position_to_sfml_position(end, window_height, scale),
            Color::Green,
            renderer
        );
    }

    // ------------------------------------------------------------------------------------------ //

    void render_polygon
    (
        const b2Vec2* vertices,
        int                 number_of_vertices,
        const b2Transform& transform,
        RenderWindow& renderer,
        float               window_height,
        float               scale,
        Color color
    )
    {
        ConvexShape sfml_polygon;

        sfml_polygon.setPointCount(number_of_vertices);
        sfml_polygon.setFillColor(color);

        for (int index = 0; index < number_of_vertices; index++)
        {
            sfml_polygon.setPoint
            (
                index,
                box2d_position_to_sfml_position(b2Mul(transform, vertices[index]), window_height, scale)
            );
        }

        renderer.draw(sfml_polygon);
    }
    void Renderer::render(std::map<std::string, std::shared_ptr<Entity>> entities)
    {
        // Limpia la ventana
        window_.clear();
        float window_height = (float)window_.getSize().y;

        for (const auto& pair : entities)
        {
            const b2Transform& body_transform = pair.second->body_->GetTransform();
            // Se recorre la lista de fixtures del body:

            for (b2Fixture* fixture = pair.second->body_->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
            {
                // Se obtiene el tipo de forma de la fixture:

                b2Shape::Type shape_type = fixture->GetShape()->GetType();

                switch (shape_type)
                {
                    case b2Shape::e_circle:
                    {
                        // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                        // En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
                        // del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                        b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());
                        
                        render_circle(circle->m_p, circle->m_radius, body_transform, window_, window_height, 100);

                        break;
                    }
                    case b2Shape::e_edge:
                    {
                        // Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
                        // Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                        // que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
                        // partir de datos de vértices.

                        b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

                        render_segment(edge->m_vertex1, edge->m_vertex2, body_transform, window_, window_height, 100);

                        break;
                    }

                    case b2Shape::e_polygon:
                    {
                        // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                        // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                        b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

                        render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, window_, window_height, 100, pair.second->color);

                        break;
                    }
                }


            }
                
        }

        // Muestra la ventana
        window_.display();
    }

}