#ifndef SRC_CREATURE_H_
#define SRC_CREATURE_H_

#include "Box2D/Box2D.h"

class Creature
{

public:
	Creature(void);
	virtual ~Creature(void);

	void initialize(b2World* world);
	bool isAlive(void);

private:
	b2Body* body;
	bool alive;
};

#endif
