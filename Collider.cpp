#include "Collider.h"
#include <math.h>

Collider::Collider(WorldObject* object)
	:object(object)
{
}

Collider::~Collider(void)
{
}

#include<iostream>

void Collider::Affected(Collision collision)
{
	cout<<"pos "<<collision.GetInsidePositive().x<<" "<<collision.GetInsidePositive().y<<" "<<collision.GetInsidePositive().z<<endl;
	cout<<"neg "<<collision.GetInsideNegative().x<<" "<<collision.GetInsideNegative().y<<" "<<collision.GetInsideNegative().z<<endl;
	cout<<"hit "<<collision.GetDirection().x<<" "<<collision.GetDirection().y<<" "<<collision.GetDirection().z<<endl;
	Hit(collision);
}

void Collider::Hit(Collision collision)
{
	Point3D direction = collision.GetDirection();
	Point3D moves;

	if(abs(direction.x) < 0.00001)
		direction.x = 0;
	if(abs(direction.y) < 0.00001)
		direction.y = 0;
	if(abs(direction.z) < 0.00001)
		direction.z = 0;

	if(direction.x == 0)
	{
		moves.x = 100000000000;
	}
	else
	{
		if(direction.x > 0)
		{
			moves.x = collision.GetInsidePositive().x/direction.x;
		}
		else
		{
			moves.x = collision.GetInsideNegative().x/direction.x;
		}
	}

	if(direction.y == 0)
	{
		moves.y = 100000000000;
	}
	else
	{
		if(direction.y > 0)
		{
			moves.y = collision.GetInsidePositive().y/direction.y;
		}
		else
		{
			moves.y = collision.GetInsideNegative().y/direction.y;
		}
	}

	if(direction.z == 0)
	{
		moves.z = 100000000000;
	}
	else
	{
		if(direction.z > 0)
		{
			moves.z = collision.GetInsidePositive().z/direction.z;
		}
		else
		{
			moves.z = collision.GetInsideNegative().z/direction.z;
		}
	}

	cout<<endl<<endl;

	cout<<direction.x<<" "<<direction.y<<" "<<direction.z<<endl;
	direction = direction*Min(moves.x,Min(moves.y,moves.z));
	cout<<direction.x<<" "<<direction.y<<" "<<direction.z<<endl;
	cout<<endl<<endl;

	object->Translate(-direction);
}

float Collider::Min(float x,float y)
{
	if(x < y)
		return x;
	return y;
}

Collision Collider::Check(WorldObject* other) 
{
	vector<Point3D> a = object->GetBoundingBox();
	vector<Point3D> b = other->GetBoundingBox();

	if(a[1].x > b[0].x &&
		a[0].x < b[1].x &&
		a[1].y > b[0].y &&
		a[0].y < b[1].y &&
		a[1].z > b[0].z &&
		a[0].z < b[1].z)
	{
		return Collision(Point3D(b[1].x-a[0].x,b[1].y-a[0].y,b[1].z-a[0].z),Point3D(b[0].x-a[1].x,b[0].y-a[1].y,b[0].z-a[1].z),object);
	}
	else
	{
		return Collision();
	}
}