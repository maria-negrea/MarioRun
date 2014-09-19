#include "WorldObject.h"

WorldObject::WorldObject(GLfloat W, GLfloat H,GLfloat X, GLfloat Y, GLfloat Z)
{
    translate = Point3D(X, Y, Z);
    width = W;
    height = H;

	parent = NULL;
	scale = Point3D(1.f, 1.f, 1.f);
	collider = NULL;
	scene = NULL;

	visible = true;
}

WorldObject::WorldObject(bool hasCollider)
{
	scale = Point3D(1.f, 1.f, 1.f);
	collider = NULL;
	scene = NULL;

	visible = true;
}

WorldObject::~WorldObject(void)
{
}

void WorldObject::Draw()
{
	ModifyPerspective();

	if(visible)
	{
		for(int i=0;i<children.size();i++)
		{
			children[i]->Draw();
		}
		DrawObject();
	}
	ModifyPerspectiveBack();
}

void WorldObject::AddChild(WorldObject* child)
{
	if(scene != NULL) 
	{
		scene->AddObject(child);
	}
	children.push_back(child);
	child->parent = this;
}

void WorldObject::RemoveChild(WorldObject *child) {
	if(scene != NULL) {
		scene->RemoveObject(child);
	}
	child->parent = NULL;
}

void WorldObject::ModifyPerspective()
{
	glTranslatef(translate.x,translate.y,translate.z);

	glRotatef(rotate.y,0,1,0);
	glRotatef(rotate.x,1,0,0);
	glRotatef(rotate.z,0,0,1);
	
	glScalef(scale.x, scale.y, scale.z);
}

void WorldObject::ModifyPerspectiveBack()
{
	glScalef(1/scale.x, 1/scale.y, 1/scale.z);

	glRotatef(-rotate.z,0,0,1);
	glRotatef(-rotate.x,1,0,0);
	glRotatef(-rotate.y,0,1,0);

	glTranslatef(-translate.x,-translate.y,-translate.z);
}

void WorldObject::ParentPerspective()
{
	if(parent != NULL)
	{
		parent->ModifyPerspective();
		parent->ParentPerspective();
	}
}

void WorldObject::ParentPerspectiveBack()
{
	if(parent != NULL)
	{
		parent->ParentPerspectiveBack();
		parent->ModifyPerspectiveBack();
	}
}

void WorldObject::Translate(Point3D translation)
{
	translate += translation;
	if(HasCollider())
	{
		if(scene != NULL)
		{
			scene->CollisionCheck(this,translation.Normalize());
		}
	}
}

void WorldObject::Rotate(Point3D rotation)
{
	rotate += rotation;
}

void WorldObject::Scale(Point3D s) {
	scale += s;
}

Point3D WorldObject::GetTranslate()
{
	return translate;
}

Point3D WorldObject::GetForward()
{
	return Point3D(0.0, 0.0, 1.0).RotateY(360-rotate.y);
}

Point3D WorldObject::GetRight() 
{
	return Point3D(1.0, 0.0, 0.0).RotateY(360-rotate.y);
}

Point3D WorldObject::GetRotate() 
{
	return rotate;
}

Point3D WorldObject::GetScale() {
	return scale;
}

int WorldObject::ChildrenCount()
{
	return children.size();
}

WorldObject* WorldObject::GetChild(int i)
{
	return children[i];
}

void WorldObject::SetScene(Scene* scene)
{
	this->scene = scene;
}
vector<Point3D> WorldObject::GetBoundingBox()
{
	vector<Point3D> res;
		res.push_back(Point3D(translate.x - (width*scale.x)/2, translate.y, translate.z - (length*scale.z)/2));
		res.push_back(Point3D(translate.x + (width*scale.x)/2, translate.y + height*scale.y, translate.z + (length*scale.z)/2));
	return res;
}

bool WorldObject::HasCollider()
{
	return collider != NULL;
}

Collider* WorldObject::GetCollider()
{
	return collider;
}

void WorldObject::SetCollider(Collider* collider)
{
	this->collider = collider;
}

void WorldObject::AddCollider()
{
	this->collider = new Collider(this);
}

void WorldObject::SetVisibility(bool visibility)
{
	this->visible = visibility;
}

bool WorldObject::GetVisibility()
{
	return visible;
}

GLfloat WorldObject::AngleBetween(Point3D point)
{
    GLfloat angleToTarget=GetForward().AngleBetween(point);
	GLfloat rightDistance = (point+GetRight()).Magnitude();
	GLfloat distance = point.Magnitude();

	if(rightDistance < sqrt(1.0+distance*distance))
	{
		angleToTarget = 360-angleToTarget;
	}
	return angleToTarget;
}
