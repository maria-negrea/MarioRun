#pragma once
#include "Updatable.h"
#include "WorldObject.h"
//#include "Road.h"

class Camera;
class Omi;


/*! \brief
*	A collection of all the objects on the screen and a camera for the perspective 
*/
class Scene
{
	/*!The camera from wich perspective the scene gets rendered*/
	Camera* mainCamera;
	
	/*!Objects in the scene */
	vector<WorldObject*> sceneObjects;	
	/*!Objects that need updating */
	vector<Updatable*> updateObjects;
	/*!Light sources*/
	vector<Omi*> lightSources;	

	/*!Objects that have colliders */
	vector<WorldObject*> colliders;

	vector<Cutout*> cutouts;

	/*! Removes an object from the updateObjects list */
	void RemoveUpdatable(Updatable* object);
	void RemoveCutout(Cutout* cutout);
	void AddSpecialObject(WorldObject* object);
public:
	Scene();
	~Scene();
	
	void RemoveCollider(WorldObject* object);
	/*!Draws the object on the screen */
	void Render();
	/*! Updates all the objects that need updating */
	void Update();

	Camera* GetCamera();
	
	void SetMainCamera(Camera* camera);

	/*! Adds an object from the objects in the sceen if the object is Updatable it also adds it from the updateObjects list*/
	void AddObject(WorldObject* object);
	/*! Adds an object from the objects in the sceen if the object is Updatable it also removes it from the updateObjects list*/
	void RemoveObject(WorldObject* object);

	void CollisionCheck(WorldObject* object,Point3D previousPosition);
};

#include "Camera.h"
#include "Omi.h"
