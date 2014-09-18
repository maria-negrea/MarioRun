#include "Collider.h"
#include <math.h>

Collider::Collider(void)
{
}

Collider::~Collider(void)
{
}

#include<iostream>

void Collider::Affected(Collision* collision)
{
	if(collision != NULL)
	{
		cout<<"hit"<<endl;
		Hit(collision);
	}
}

void Collider::Hit(Collision* collision)
{
	
}

Collision* Collider::check(vector<Point3D> a, vector<Point3D> b) {
	bool hasCollision = (a[1].x > b[0].x &&
		a[0].x < b[1].x &&
		a[1].y > b[0].y &&
		a[0].y < b[1].y &&
		a[1].z > b[0].z &&
		a[0].z < b[1].z);
	return NULL;
}