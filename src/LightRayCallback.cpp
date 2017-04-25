#include "LightRayCallback.h"

#include "WorldObject.h"

LightRayCallback::LightRayCallback()
{
	m_fixture = NULL;
}

LightRayCallback::~LightRayCallback()
{

}

float32 LightRayCallback::ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
						const b2Vec2& normal, float32 fraction)
{
	WorldObject* wo = (WorldObject*)fixture->GetUserData();

	if(wo == NULL || wo->isTransparent())
	{
		return -1;
	}

	m_fixture = fixture;
	m_point = point;

	return fraction;
}
