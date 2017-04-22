#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "DebugDraw.h"

#include "Window.h"

static const float PI = 3.14159265359;

DebugDraw::DebugDraw()
{
	glWindow = initWindow();
	initGl();
}

DebugDraw::~DebugDraw()
{

}

void DebugDraw::initGl(void)
{
	int zero = 0;
	glutInit(&zero, NULL);

	int width = 600;
	int height = 600;

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);

}

void mouseFunc(int type, int button, int x, int y)
{
	//printf("mouse - type: %d, button: %d, x: %d, y: %d\n", type, button, x, y);
}

void keyPress(int code)
{
	//printf("key: %d, type: press\n", code);

	switch(code)
	{
		case 10:
		case 11:
		case 12:
		case 13:
		{

		}break;

		case 25:	// W
		{

		}break;

		case 38:	// A
		{

		}break;

		case 39:	// S
		{

		}break;

		case 40:	// D
		{

		}break;

		case 113:	// LEFT ARROW
		{

		}break;

		case 114:	// RIGHT ARROW
		{

		}break;

		case 111:	// UP ARROW
		{

		}break;

		case 116:	// DOWN ARROW
		{

		}break;

		case 50:
		case 65:	// SPACE
		{

		}break;
	}
}

void keyRelease(int code)
{
	//printf("key: %d, type: release\n", code);

	switch(code)
	{
		case 25:	// W
		{

		}break;

		case 38:	// A
		{

		}break;

		case 39:	// S
		{

		}break;

		case 40:	// D
		{

		}break;

		case 113:	// LEFT ARROW
		{

		}break;

		case 114:	// RIGHT ARROW
		{

		}break;

		case 111:	// UP ARROW
		{

		}break;

		case 116:	// DOWN ARROW
		{

		}break;

		case 50:
		case 65:	// SPACE
		{

		}break;

	}
}

void DebugDraw::update(b2World* world)
{
	int windowOpen;
	windowOpen = processWindow(glWindow, mouseFunc, keyPress, keyRelease);

	if(windowOpen)
	{
		drawWorld(world);
		showWindow(glWindow);
	}

}

static void drawCircle(b2CircleShape* circle)
{
	b2Vec2 center = circle->m_p;
	float radius = circle->m_radius;

	glPushMatrix();

		glTranslatef(center.x, center.y, 0.0);

		glBegin(GL_LINE_LOOP);

			int numSegments = 16;

			for(int i=0; i<numSegments; i++)
			{
				float ang = 2*PI*float(i)/float(numSegments);
				float x = radius*cos(ang);
				float y = radius*sin(ang);

				glVertex2f( x, y);
			}

		glEnd();

	glPopMatrix();

}

static void drawPolygon(b2PolygonShape* polygon)
{
	int numVertex = polygon->GetVertexCount();

	glBegin(GL_LINE_LOOP);

		for(int i=0; i<numVertex; i++)
		{
			b2Vec2 vertex = polygon->GetVertex(i);

			glVertex2f( vertex.x, vertex.y);
		}

	glEnd();

}

static void drawShape(b2Shape* shape)
{
	switch(shape->GetType())
	{
		case b2Shape::e_circle:
		{
			drawCircle((b2CircleShape*)shape);
		}break;

		case b2Shape::e_polygon:
		{
			drawPolygon((b2PolygonShape*)shape);
		}break;

		default:
		{

		}break;
	}
}

static void drawFixture(b2Fixture* fixture)
{
	b2Shape* shape = fixture->GetShape();

	drawShape(shape);
}

static void drawBody(b2Body* body)
{
	glPushMatrix();

		b2Vec2 bodyPos = body->GetPosition();
		float bodyAngle = body->GetAngle();

		glTranslatef(bodyPos.x, bodyPos.y, 0.0);
		glRotatef(bodyAngle * 180.0 / PI, 0, 0, 1.0);

		printf("Body x:%f y:%f\n", bodyPos.x, bodyPos.y);

		b2Fixture* fixtureNode = body->GetFixtureList();
		while (fixtureNode)
		{
			b2Fixture* f = fixtureNode;
			fixtureNode = fixtureNode->GetNext();

			drawFixture(f);
		}

	glPopMatrix();
}

void DebugDraw::drawWorld(b2World* world)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(300, 300, 0);
	glScalef(10, 10, 10);

	glColor3f( 0.0, 1.0, 0.0);
	glLineWidth(1.0);

	b2Body* node = world->GetBodyList();
	while (node)
	{
		b2Body* b = node;
		node = node->GetNext();

		drawBody(b);
	}

}
