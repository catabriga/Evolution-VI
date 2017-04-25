#include <stdlib.h>

#include "Creature.h"

static const float PI = 3.14159265359;

Creature::Creature(void)
{
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
	for(int i=0; i<MAX_NUM_PARTS; i++)
	{
		parts[i].destroy(world);
	}

	removed = true;
	alive = false;
	readyToReproduce = false;
}

void Creature::initialize(b2World* world)
{
	b2Vec2 pos(0.0f, 10.0f);

	parts[0].init(world, this, pos);

	alive = true;
	removed = false;
	readyToReproduce = false;
	energy = 100.0;
}

void Creature::initialize(b2World* world, Creature* parent)
{
	b2Vec2 pos = parent->getPosition();

	parts[0].init(world, this, pos);

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

void Creature::reproduce(void)
{
	energy -= 500.0;
}

void Creature::addEnergy(float dE)
{
	energy += dE;
}

b2Vec2 Creature::getPosition(void)
{
	return parts[0].getPosition();
}
