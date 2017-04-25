#include "Sun.h"

#include "LightRayCallback.h"
#include "WorldObject.h"

static const float PI = 3.14159265359;

Sun::Sun()
{
	for(int i=0; i<NUM_SUN_RAYS; i++)
	{
		rays[i].start = b2Vec2(0.0, 0.0);
		rays[i].end = b2Vec2(0.0, 0.0);
	}
}

Sun::~Sun()
{

}

int Sun::getNumRays(void)
{
	return NUM_SUN_RAYS;
}

Sun::SunRay* Sun::getRays(void)
{
	return rays;
}

void Sun::castSunRays(b2World* world)
{
	LightRayCallback lightRayCallback;

	b2Vec2 sunPos(0.0f, 200.0f);
	b2Vec2 origin(0.0f, 0.0f);

	float sunFOV = 30.0 * PI / 180.0;
	float rayLength = 2000.0f;

	b2Vec2 diffPos = origin - sunPos;

	float centerAng = atan2(diffPos.y, diffPos.x);
	float startAng = centerAng - sunFOV/2.0;
	float endAng = centerAng + sunFOV/2.0;
	float increment = (endAng - startAng)/NUM_SUN_RAYS;

	for(int i=0; i<NUM_SUN_RAYS; i++)
	{
		float ang = startAng + i*increment;

		float endX = sunPos.x + cos(ang)*rayLength;
		float endY = sunPos.y + sin(ang)*rayLength;

		b2Vec2 endPoint(endX, endY);
		lightRayCallback.m_point = endPoint;

		world->RayCast(&lightRayCallback, sunPos, endPoint);

		rays[i].start = sunPos;
		rays[i].end = lightRayCallback.m_point;

		b2Fixture* fixture = lightRayCallback.m_fixture;

		if(fixture != NULL)
		{
			WorldObject* wo = (WorldObject*)fixture->GetUserData();

			//if(wo != NULL)
			{
				wo->shineLight();
			}
		}
	}

}
