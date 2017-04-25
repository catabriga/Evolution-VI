
#ifndef SRC_EVOLUTIONVI_H_
#define SRC_EVOLUTIONVI_H_

#include "Box2D/Box2D.h"

#include "Ground.h"
#include "Creature.h"
#include "DebugDraw.h"

class EvolutionVI
{

public:
	EvolutionVI(void);
	virtual ~EvolutionVI(void);

	void run(void);

private:

	b2Vec2 gravity;
	b2World world;

	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;

	Ground ground;

	static const int MAX_NUM_CREATURES = 1000;
	int numCreatures;
	Creature creatureList[MAX_NUM_CREATURES];

	Sun sun;

	DebugDraw debugDraw;

	void initGroundBody(void);
	void initCreatures(void);

	void updateCreatures(void);

	int getAvailableCreatureSpot(void);
};

#endif
