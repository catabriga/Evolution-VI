
#ifndef SRC_CREATUREPART_H_
#define SRC_CREATUREPART_H_

#include "Box2D/Box2D.h"

#include "WorldObject.h"

// Forward declaration of creature to enable
// circular reference between these two objects
class Creature;

class CreaturePart : public WorldObject
{
public:
	CreaturePart(void);
	virtual ~CreaturePart(void);

	void init(b2World* world, Creature* ownerCreature, b2Vec2 position, uint8_t* params);
	void destroy(b2World* world);

	b2Vec2 getPosition(void);

	bool isTransparent(void);
	void shineLight(void);

private:

	Creature* ownerCreature;
	b2Body* body;
	b2Fixture* fixture;
	bool transparent;


};

#endif
