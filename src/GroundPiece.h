
#ifndef SRC_GROUNDPIECE_H_
#define SRC_GROUNDPIECE_H_

#include "WorldObject.h"

#include "Box2D/Box2D.h"

class GroundPiece : public WorldObject
{
public:
	GroundPiece();
	virtual ~GroundPiece(void);

	void init(b2Body* groundBody, b2Vec2* points, int numPoints, bool transparent);

	bool isTransparent(void);
	void shineLight(void);

private:

	bool transparent;
};

#endif
