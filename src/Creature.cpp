#include <stdlib.h>

#include "Creature.h"

static const float PI = 3.14159265359;

Creature::Creature(void)
{
	body = NULL;
	alive = false;
	removed = true;
	readyToReproduce = false;
	energy = 0.0;
}

Creature::~Creature(void)
{

}

bool Creature::isAlive(void)
{
	return alive;
}

bool Creature::isRemoved(void)
{
	return removed;
}

bool Creature::isReadyToReproduce(void)
{
	return readyToReproduce;
}

void Creature::remove(b2World* world)
{
	world->DestroyBody(body);
	body = NULL;

	removed = true;
	alive = false;
	readyToReproduce = false;
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
	fixtureDef.friction = 5.0f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);

	alive = true;
	removed = false;
	readyToReproduce = false;
	energy = 100.0;
}

void Creature::initialize(b2World* world, Creature* parent)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = parent->body->GetPosition();
	bodyDef.angle = parent->body->GetAngle();
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 5.0f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.userData = this;

	body->CreateFixture(&fixtureDef);

	alive = true;
	removed = false;
	readyToReproduce = false;
	energy = 100.0;
}

void Creature::update(void)
{
	energy -= 0.1;

	if(energy < 0.0)
	{
		alive = false;
	}

	if(energy > 1000.0)
	{
		readyToReproduce = true;
	}
}

void Creature::shineLight(void)
{
	energy += 0.2;
}

void Creature::reproduce(void)
{
	energy -= 500.0;
}
