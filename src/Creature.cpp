#include <stdlib.h>

#include "Creature.h"

static const float PI = 3.14159265359;

Creature::Creature(void)
{
	body = NULL;
	alive = false;
}

Creature::~Creature(void)
{

}

bool Creature::isAlive(void)
{
	return alive;
}

void Creature::initialize(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 10.0f);
	bodyDef.angle = PI/3.0;
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.98f;

	body->CreateFixture(&fixtureDef);

	alive = true;
}

