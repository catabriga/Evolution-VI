#ifndef SRC_SUN_H_
#define SRC_SUN_H_

#include "Box2D/Box2D.h"

class Sun
{
public:
	struct SunRay
	{
		b2Vec2 start;
		b2Vec2 end;
	};

	typedef struct SunRay SunRay;

	Sun();
	virtual ~Sun();

	void castSunRays(b2World* world);

	int getNumRays(void);
	SunRay* getRays(void);

private:
	static const int NUM_SUN_RAYS = 100;
	SunRay rays[NUM_SUN_RAYS];

};

#endif
