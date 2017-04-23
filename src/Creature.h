#ifndef SRC_CREATURE_H_
#define SRC_CREATURE_H_

#include "Box2D/Box2D.h"

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
	void shineLight(void);
	bool isReadyToReproduce(void);
	void reproduce(void);

private:
	b2Body* body;
	bool alive;
	bool removed;
	bool readyToReproduce;
	float energy;
};

#endif
