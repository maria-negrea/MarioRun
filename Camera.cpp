#include "Camera.h"
#include<iostream>

using namespace std;

Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::DrawObject()
{

}

void Camera::Perspective()
{
	glRotatef(-rotate.z,0,0,1);
	glRotatef(-rotate.x,1,0,0);
	glRotatef(-180-rotate.y,0,1,0);

	glTranslatef(-translate.x,-translate.y,-translate.z);
}