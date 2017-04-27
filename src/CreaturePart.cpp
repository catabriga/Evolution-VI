#include "CreaturePart.h"
#include "Creature.h"

static const float PI = 3.14159265359;

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

static float geneToFloat(uint8_t gene)
{
	return (float)gene / (float)UINT8_MAX;
}

// The genes are in polar coordinates, first gene is
// angle and second is range
static b2Vec2 geneToVec(uint8_t gene1, uint8_t gene2)
{
	const float MAX_RANGE = 5.0;

	float angle = geneToFloat(gene1) * 2.0 * PI;
	float range = geneToFloat(gene2) * MAX_RANGE;

	float x = cos(angle) * range;
	float y = sin(angle) * range;

	return b2Vec2(x,y);
}

void CreaturePart::init(b2World* world, Creature* ownerCreature, b2Vec2 position, uint8_t* params)
{
	this->ownerCreature = ownerCreature;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = position;
	bodyDef.angle = 0.0;
	body = world->CreateBody(&bodyDef);

	b2Vec2 centerZero(0.0f, 0.0f);

	b2PolygonShape triangle;
	b2Vec2 vertices[3];
	vertices[0] = geneToVec(params[0], params[1]);
	vertices[1] = geneToVec(params[2], params[3]);
	vertices[2] = geneToVec(params[4], params[5]);

	triangle.Set(vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &triangle;
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
