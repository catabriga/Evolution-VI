/*
 * Ground.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: lucas
 */

#include "Ground.h"

Ground::Ground(b2World* world)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	groundBody = world->CreateBody(&groundBodyDef);

	b2Vec2 gb1[6];
	gb1[0].Set(-50.0f, 50.0f);
	gb1[1].Set(-50.0f, 0.0f);
	gb1[2].Set(-25.0f, -25.0f);
	gb1[3].Set(25.0f, -25.0f);
	gb1[4].Set(50.0f, 0.0f);
	gb1[5].Set(50.0f, 50.0f);
	groundPieces[0].init(groundBody, gb1, 6, false);

	b2Vec2 gb2[2];
	gb2[0].Set(-50.0f, 50.0f);
	gb2[1].Set(50.0f, 50.0f);
	groundPieces[1].init(groundBody, gb2, 2, true);

}

Ground::~Ground(void)
{
	// TODO Auto-generated destructor stub
}

