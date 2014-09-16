#include "WorldObject.h"

WorldObject::WorldObject(GLfloat W, GLfloat H,GLfloat X, GLfloat Y, GLfloat Z)
{
    translate = Point3D(X, Y, Z);
    width = W;
    height = H;
	parent = NULL;
}

WorldObject::~WorldObject(void)
{
}

void WorldObject::Draw()
{
	ModifyPerspective();

	for(int i=0;i<children.size();i++)
	{
		children[i]->Draw();
	}

	DrawObject();
	
	ModifyPerspectiveBack();
}

void WorldObject::AddChild(WorldObject* child)
{
	children.push_back(child);
	child->parent = this;
}

void WorldObject::ModifyPerspective()
{
	glTranslatef(translate.x,translate.y,translate.z);

	glRotatef(rotate.y,0,1,0);
	glRotatef(rotate.x,1,0,0);
	glRotatef(rotate.z,0,0,1);
}

void WorldObject::ModifyPerspectiveBack()
{
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
}

void WorldObject::Rotate(Point3D rotation)
{
	rotate += rotation;
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

int WorldObject::ChildrenCount()
{
	return children.size();
}

WorldObject* WorldObject::GetChild(int i)
{
	return children[i];
}

vector<Point3D> WorldObject::GetBoundingBox(){
	cout<<width<<" "<<height<<" "<<length<<endl;
	cout<<translate.x<<" "<<translate.y<<" "<<translate.z<<endl;
	vector<Point3D> res;
		res.push_back(Point3D(translate.x - width/2, translate.y, translate.z - length/2));
		res.push_back(Point3D(translate.x + width/2, translate.y + height, translate.z + length/2));
	return res;
}