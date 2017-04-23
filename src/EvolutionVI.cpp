#include "EvolutionVI.h"

EvolutionVI::EvolutionVI(void) :
	gravity(0.0f, -2.0f),
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

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);
	//groundBody->CreateFixture(&groundBox, 0.0f);


	b2Vec2 vs[6];
	vs[0].Set(-50.0f, 50.0f);
	vs[1].Set(-50.0f, 0.0f);
	vs[2].Set(-25.0f, -25.0f);
	vs[3].Set(25.0f, -25.0f);
	vs[4].Set(50.0f, 0.0f);
	vs[5].Set(50.0f, 50.0f);
	b2ChainShape chain;
	chain.CreateChain(vs, 6);

	groundBody->CreateFixture(&chain, 0.0f);

}

void EvolutionVI::initCreatures(void)
{
	for(int i=0; i<50; i++)
	{
		creatureList[numCreatures].initialize(&world);
		numCreatures++;
	}
}

int EvolutionVI::getAvailableCreatureSpot(void)
{
	for(int i=0; i<MAX_NUM_CREATURES; i++)
	{
		Creature* creature = &(creatureList[i]);

		if(creature->isRemoved())
		{
			return i;
		}
	}

	return -1;
}

void EvolutionVI::updateCreatures(void)
{
	for(int i=0; i<MAX_NUM_CREATURES; i++)
	{
		Creature* creature = &(creatureList[i]);

		if(creature->isAlive())
		{
			creature->update();

			if(creature->isReadyToReproduce())
			{
				int spotIndex = getAvailableCreatureSpot();

				// If there is not spot for a new creature, consume the resources
				// of a child anyway
				creature->reproduce();

				if(spotIndex >= 0)
				{
					creatureList[spotIndex].initialize(&world, creature);
				}
				else
				{
					printf("Max number of creatures reached\n");
				}
			}
		}
		else if(creature->isRemoved() == false)
		{
			creature->remove(&world);
		}
	}
}


void EvolutionVI::run(void)
{
	initGroundBody();
	initCreatures();

	int i =0;

	while(true)
	{
		world.Step(timeStep, velocityIterations, positionIterations);

		sun.castSunRays(&world);
		updateCreatures();

		if(i%10 == 0)
			debugDraw.update(&world, &sun);

		i++;
	}
}
