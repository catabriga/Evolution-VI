#include "CreaturePart.h"
#include "Creature.h"

CreaturePart::CreaturePart(void)
{
	ownerCreature = NULL;
	body = NULL;
	fixture = NULL;
	transparent = true;
}

CreaturePart::~CreaturePart(void)
{

}

void CreaturePart::init(b2World* world, Creature* ownerCreature, b2Vec2 position)
{
	this->ownerCreature = ownerCreature;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = position;
	bodyDef.angle = 0.0;
	body = world->CreateBody(&bodyDef);

	b2Vec2 centerZero(0.0f, 0.0f);
	float angle = 0.0f;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f, centerZero, angle);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 5.0f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.userData = this;

	fixture = body->CreateFixture(&fixtureDef);

	transparent = false;
}

void CreaturePart::destroy(b2World* world)
{
	if(body != NULL)
	{
		world->DestroyBody(body);
	}

	ownerCreature = NULL;
	body = NULL;
	fixture = NULL;
	transparent = true;
}

b2Vec2 CreaturePart::getPosition(void)
{
	return body->GetPosition();
}

bool CreaturePart::isTransparent(void)
{
	return transparent;
}

void CreaturePart::shineLight(void)
{
	ownerCreature->addEnergy(0.2);
}
