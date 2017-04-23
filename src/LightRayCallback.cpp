#include "LightRayCallback.h"

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
	m_fixture = fixture;
	m_point = point;

	return fraction;
}
