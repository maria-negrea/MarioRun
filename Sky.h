#pragma once
#include "WorldObject.h"
#include "Updatable.h"

/*! \brief
* Skybox 
*/
class Sky : public WorldObject, public Updatable
{
	/*! size of the skybox*/
	GLfloat size;
	
	void DrawObject();
public:	
	Sky(GLfloat size);
	~Sky();
	void Update();
};
