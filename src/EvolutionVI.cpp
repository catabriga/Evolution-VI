#include "EvolutionVI.h"

EvolutionVI::EvolutionVI(void) :
	gravity(0.0f, -10.0f),
	world(gravity)
{
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;

	numCreatures = 0;

	groundBody = NULL;
}

EvolutionVI::~EvolutionVI(void)
{

}

void EvolutionVI::initGroundBody(void)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

}

void EvolutionVI::initCreatures(void)
{
	creatureList[numCreatures].initialize(&world);
	numCreatures++;
}

void EvolutionVI::run(void)
{
	initGroundBody();
	initCreatures();

	while(true)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
		debugDraw.update(&world);
	}
}
