#pragma once

/*! \brief
*	Used for objects who need updated
*	A WorldObject added into Scene who is also Updatable will be updataed automatically
*	@see Scene
*/
class Updatable
{
public:
	Updatable();
	~Updatable();

	virtual void Update() = 0;
};
