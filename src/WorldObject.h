#ifndef SRC_WORLDOBJECT_H_
#define SRC_WORLDOBJECT_H_

class WorldObject
{
public:
	WorldObject(void) {};
	virtual ~WorldObject(void) {};

	virtual bool isTransparent(void) = 0;
	virtual void shineLight(void) = 0;
};

#endif
