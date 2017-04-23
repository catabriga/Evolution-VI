#ifndef SRC_LIGHTRAYCALLBACK_H_
#define SRC_LIGHTRAYCALLBACK_H_

#include "Box2D/Box2D.h"

class LightRayCallback : public b2RayCastCallback
{
public:
	LightRayCallback();
	virtual ~LightRayCallback();

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	b2Fixture* m_fixture;
	b2Vec2 m_point;
};

#endif
