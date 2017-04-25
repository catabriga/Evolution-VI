#include "EvolutionVI.h"

#include "Sun.h"

EvolutionVI::EvolutionVI(void) :
	gravity(0.0f, -2.0f),
	world(gravity),
	ground(&world)
{
	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;

	numCreatures = 0;
}

EvolutionVI::~EvolutionVI(void)
{

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
