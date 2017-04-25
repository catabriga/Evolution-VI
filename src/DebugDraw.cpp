#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "DebugDraw.h"

#include "Window.h"

static const float PI = 3.14159265359;

static float cameraX = 300.0;
static float cameraY = 300.0;
static float cameraScale = 5.0;

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
		case 24:	// Q
		{
			cameraScale *= 1.04;
		}break;

		case 25:	// W
		{
			cameraY -= 10.0;
		}break;

		case 26:	// E
		{
			cameraScale /= 1.04;
		}break;

		case 38:	// A
		{
			cameraX += 10.0;
		}break;

		case 39:	// S
		{
			cameraY += 10.0;
		}break;

		case 40:	// D
		{
			cameraX -= 10.0;
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

void DebugDraw::update(b2World* world, Sun* sun)
{
	int windowOpen;
	windowOpen = processWindow(glWindow, mouseFunc, keyPress, keyRelease);

	if(windowOpen)
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(cameraX, cameraY, 0);
		glScalef(cameraScale, cameraScale, cameraScale);

		drawWorld(world);
		drawSun(sun);

		showWindow(glWindow);
	}

}

static void drawCircle(b2CircleShape* circle)
{
	b2Vec2 center = circle->m_p;
	float radius = circle->m_radius;

	glPushMatrix();

		glTranslatef(center.x, center.y, 0.0);

		glBegin(GL_LINE_STRIP);

			int numSegments = 16;

			for(int i=0; i<numSegments+1; i++)
			{
				float ang = 2*PI*float(i)/float(numSegments);
				float x = radius*cos(ang);
				float y = radius*sin(ang);

				glVertex2f( x, y);
			}

			glVertex2f( 0, 0);

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

static void drawChain(b2ChainShape* chain)
{
	glBegin(GL_LINES);

	for (int i=0; i<chain->GetChildCount(); i++)
	{
		b2EdgeShape edge;
		chain->GetChildEdge(&edge, i);

		glVertex2f( edge.m_vertex1.x, edge.m_vertex1.y);
		glVertex2f( edge.m_vertex2.x, edge.m_vertex2.y);
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

		case b2Shape::e_chain:
		{
			drawChain((b2ChainShape*)shape);
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
	glColor3f( 0.0, 0.0, 0.0);
	glLineWidth(1.0);

	b2Body* node = world->GetBodyList();
	while (node)
	{
		b2Body* b = node;
		node = node->GetNext();

		drawBody(b);
	}

}

void DebugDraw::drawSun(Sun* sun)
{
	glColor3f( 1.0, 0.4, 0.4);
	glLineWidth(1.0);

	Sun::SunRay* rays = sun->getRays();

	glBegin(GL_LINES);

	for(int i=0; i<sun->getNumRays(); i++)
	{
		glVertex2f( rays[i].start.x, rays[i].start.y );
		glVertex2f( rays[i].end.x, rays[i].end.y );
	}

	glEnd();
}
