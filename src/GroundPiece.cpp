/*
 * GroundPiece.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: lucas
 */

#include "GroundPiece.h"

GroundPiece::GroundPiece()
{
	this->transparent = true;
}

GroundPiece::~GroundPiece(void)
{

}

void GroundPiece::init(b2Body* groundBody, b2Vec2* points, int numPoints, bool transparent)
{
	b2ChainShape chain;
	chain.CreateChain(points, numPoints);
	b2Fixture* fixture = groundBody->CreateFixture(&chain, 0.0f);
	fixture->SetUserData(this);

	this->transparent = transparent;
}


bool GroundPiece::isTransparent(void)
{
	return transparent;
}

void GroundPiece::shineLight(void)
{

}
