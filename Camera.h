#pragma once

#include "WorldObject.h"
#include "Updatable.h"

/*! \brief
* The camera used for the perspective of the view
*/
class Camera : public WorldObject
{
protected:
	/** Direction into which the camers looks */
	Point3D direction;
	/** Implements the method, for the class not to be abstract */
	void DrawObject();
public:
	Camera();
	~Camera();

	/** Changes the view to the camera's perspective */ 
	void Perspective();
};
