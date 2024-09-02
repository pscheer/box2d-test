
#include "box2d/box2d.h"
#include <memory>
#include <vector>

const float WINDOW_WIDTH = 20.f;
const float WINDOW_HEIGHT = 15.f;

class Mote
{
private:
    b2BodyId _bodyId;

public:
    Mote(b2WorldId worldId, b2Vec2 pos, float radius)
    {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = pos;

        _bodyId = b2CreateBody(worldId, &bodyDef);

        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 2.0f;
        shapeDef.friction = 0.3f;
        shapeDef.restitution = 0.8f;

        b2Circle circle = {};
        circle.radius = radius;

        b2ShapeId ball1ShapeId = b2CreateCircleShape(_bodyId, &shapeDef, &circle);
    }
};

class Motes
{
private:
    std::vector<std::unique_ptr<Mote>> _motes;
    const int MOTES_PER_ROW = 200;
    const int ROW_COUNT = 5;

public:
    Motes(b2WorldId worldId)
    {
        float rowStart = 0.5f;
        float radius = 0.05f;
        for (int i = 0; i < ROW_COUNT; i++)
        {
            for (int j = 0; j < MOTES_PER_ROW; j++)
            {
                _motes.push_back(std::make_unique<Mote>(worldId, (b2Vec2){((float)j + 0.5f) / ((float)MOTES_PER_ROW / WINDOW_WIDTH), rowStart + radius * i * 2.1f}, radius));
            }
        }
    }
};

int main()
{
    b2Vec2 gravity = {0.0f, 9.8f};
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;
    b2WorldId worldId = b2CreateWorld(&worldDef);
    b2World_EnableSleeping(worldId, true);
    b2World_EnableWarmStarting(worldId, true);
    b2World_EnableContinuous(worldId, true);

    Motes motes(worldId);

    int counter = 100;
    while (counter-- > 0)
    {
        b2World_Step(worldId, 1.0f / 60.0f, 4);
    }

    return 0;
}
