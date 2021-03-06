#ifndef SRC_CREATURE_H_
#define SRC_CREATURE_H_

#include <stdint.h>

#include "Box2D/Box2D.h"

#include "CreaturePart.h"
#include "GeneticCode.h"

class Creature
{

public:
	Creature(void);
	virtual ~Creature(void);

	void initialize(b2World* world);
	void initialize(b2World* world, Creature* parent);
	bool isAlive(void);
	bool isRemoved(void);
	void remove(b2World* world);

	void update(void);
	bool isReadyToReproduce(void);
	void reproduce(void);
	void addEnergy(float dE);

	b2Vec2 getPosition(void);

private:

	static const uint32_t MAX_NUM_PARTS = 10;
	CreaturePart parts[MAX_NUM_PARTS];

	GeneticCode geneticCode;

	bool alive;
	bool removed;
	bool readyToReproduce;
	float energy;

	void initializePartsFromGeneticCode(b2World* world, b2Vec2 pos);
};

#endif
