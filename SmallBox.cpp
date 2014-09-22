#include "SmallBox.h"

SmallBox::SmallBox(GLfloat width, GLfloat height, GLfloat length)
{
	this->width=width/3;
	this->height=height/3;
	this->length=length/3;

	fallSpeed = 2;

}

SmallBox::~SmallBox(void)
{

}
void SmallBox::DrawObject()
{
  glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[3]);
  glBegin(GL_QUADS);
 // front face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,height*0.75, 0-length/2.);
  glTexCoord2f(1,1);glVertex3f(width/2 ,height*0.75, 0-length/2.);
  glTexCoord2f(1,0);glVertex3f(width/2, 0., 0-length/2.);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., 0-length/2.);

 //right face
  glTexCoord2f(0, 1);glVertex3f(width/2,height*0.75,0-length/2.);
  glTexCoord2f(1, 1);glVertex3f(width/2,height*0.75, length/2.);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., length/2.);
  glTexCoord2f(0, 0);glVertex3f(width/2, 0., 0-length/2.);

 // left face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,height*0.75, 0-length/2.);
  glTexCoord2f(1, 1);glVertex3f(0.-width/2,height*0.75, length/2.);
  glTexCoord2f(1, 0);glVertex3f(0.-width/2, 0., length/2.);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., 0-length/2.);

 // back face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,height*0.75, length/2.);
  glTexCoord2f(1, 1);glVertex3f(width/2,height*0.75, length/2.);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., length/2.);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., length/2.);

//  top face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,height*0.75, 0-length/2.);
  glTexCoord2f(1, 1);glVertex3f(width/2,height*0.75, -length/2.);
  glTexCoord2f(1, 0);glVertex3f(width/2,height*0.75, length/2.);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2,height*0.75, length/2.);

 // bottom face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2, 0., 0-length/2.);
  glTexCoord2f(1, 1);glVertex3f(width/2 ,0., 0-length/2.);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., length/2.);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., length/2.);
 glEnd();

}
void SmallBox::Update()
{
	PhysicsObject::Update();
	/*if(this->isGrounded==true)
	   scene->RemoveObject(this);
	else return;*/
}