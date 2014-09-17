#pragma once
#include <iostream>
#ifdef __unix || __unix__
 #include <GL/glut.h>
#else
 #include <glut.h>
#endif
#include <vector>
#include "Point3D.h"
#include "Collider.h"

class Scene;

using namespace std;


class WorldObject
{
protected:
	virtual void DrawObject() = 0;

	void ModifyPerspective();
	void ModifyPerspectiveBack();

	void ParentPerspective();
	void ParentPerspectiveBack();

	Point3D rotate;
	Point3D translate;
	Point3D scale;
	
	vector<WorldObject*> children;
	WorldObject* parent;

	Collider* collider;
	Scene *scene;
public:
	GLfloat length, width, height; // OZ, OX and OY
	WorldObject(GLfloat W = 0.0, GLfloat H = 0.0,GLfloat X = 0.0, GLfloat Y = 0.0, GLfloat Z = 0.0);
	WorldObject(bool hasCollider);
	~WorldObject();

	void Translate(Point3D);
	void Rotate(Point3D);
	void Scale(Point3D);

	void Draw();

	Point3D GetForward();
	Point3D GetTranslate();
	Point3D GetRight();
	Point3D GetScale();

	vector<Point3D> GetBoundingBox();

	Point3D GetRotate();
	void SetScene(Scene* scene);

	void AddChild(WorldObject* child);

	int ChildrenCount();
	WorldObject* GetChild(int i);

	bool HasCollider();

	Collider* GetCollider();
	void AddCollider();
	void SetCollider(Collider* collider);
	void RemoveChild(WorldObject *child);
};

#include"Scene.h"
