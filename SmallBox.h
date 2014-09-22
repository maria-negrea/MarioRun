#pragma once

#include"PhysicsObject.h"
#include"Textures.h"
class SmallBox:public PhysicsObject 
{
private:
	
public:
	SmallBox(GLfloat width, GLfloat height, GLfloat length);
	~SmallBox(void);
	void DrawObject();
	void Update();

};
