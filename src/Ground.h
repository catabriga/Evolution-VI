
#ifndef SRC_GROUND_H_
#define SRC_GROUND_H_

#include "Box2D/Box2D.h"

#include "GroundPiece.h"

class Ground
{
public:
	Ground(b2World* world);
	virtual ~Ground(void);

private:

	static const int MAX_NUM_GROUND_PIECES = 10;
	GroundPiece groundPieces[MAX_NUM_GROUND_PIECES];

	b2Body* groundBody;
};

#endif
