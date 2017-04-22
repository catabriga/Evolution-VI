#ifndef SRC_DEBUGDRAW_H_
#define SRC_DEBUGDRAW_H_

#include "Box2D/Box2D.h"

class DebugDraw
{
public:
	DebugDraw(void);
	virtual ~DebugDraw(void);

	void update(b2World* world);

private:
	struct window* glWindow;

	void initGl(void);

	void drawWorld(b2World* world);
};

#endif
