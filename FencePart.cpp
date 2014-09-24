#include "FencePart.h"

FencePart::FencePart(GLfloat width, GLfloat height, GLfloat length)
{
	this->width=width;
	this->height=height;
	this->length=length;
}

FencePart::~FencePart(void)
{
}
void FencePart::DrawObject()
{
	glBegin(GL_QUADS);
 // front face
 // glTexCoord2f(0, 1);
  glVertex3f(0,height, 0);
 // glTexCoord2f(1,1);
  glVertex3f(width ,height, 0);
 // glTexCoord2f(1,0);
  glVertex3f(width, 0., 0);
 // glTexCoord2f(0, 0);
  glVertex3f(0, 0., 0);

 //right face
 // glTexCoord2f(0, 1);
  glVertex3f(width,height,0);
 // glTexCoord2f(1, 1);
  glVertex3f(width,height, length);
//  glTexCoord2f(1, 0);
  glVertex3f(width, 0., length);
 // glTexCoord2f(0, 0);
  glVertex3f(width, 0., 0);

 // left face
 // glTexCoord2f(0, 1);
  glVertex3f(0,height, 0);
 // glTexCoord2f(1, 1);
  glVertex3f(0,height, length);
 // glTexCoord2f(1, 0);
  glVertex3f(0, 0., length);
 // glTexCoord2f(0, 0);
  glVertex3f(0, 0., 0);

 // back face
 // glTexCoord2f(0, 1);
  glVertex3f(0,height, length);
 // glTexCoord2f(1, 1);
  glVertex3f(width,height, length);
 // glTexCoord2f(1, 0);
  glVertex3f(width, 0., length);
 // glTexCoord2f(0, 0);
  glVertex3f(0, 0., length);

//  top face
 // glTexCoord2f(0, 1);
  glVertex3f(0,height, 0);
 // glTexCoord2f(1, 1);
  glVertex3f(width,height, 0);
 // glTexCoord2f(1, 0);
  glVertex3f(width,height, length);
 // glTexCoord2f(0, 0);
  glVertex3f(0,height, length);

 // bottom face
 // glTexCoord2f(0, 1);
  glVertex3f(0, 0., 0);
 // glTexCoord2f(1, 1);
  glVertex3f(width ,0., 0);
 // glTexCoord2f(1, 0);
  glVertex3f(width, 0., length);
  //glTexCoord2f(0, 0);
  glVertex3f(0, 0., length);

 glEnd();

 glBegin(GL_TRIANGLES);

 glVertex3f(width, height,length);
 glVertex3f(0, height, length);
 glVertex3f(width/2, height/2, length*1.3);

 glEnd();

 glBegin(GL_TRIANGLES);

  glVertex3f(0,0, length);
  glVertex3f(0,height, length);
  glVertex3f(width/2, height/2, length*1.3);

 glEnd();

  glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, length);
	glVertex3f(width, 0, length);
	glVertex3f(width/2, height/2, length*1.3);
  
  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex3f(width,0, length);
	glVertex3f(width, height, length);
	glVertex3f(width/2, height/2, length*1.3);

 glEnd();

 glBegin(GL_QUADS);
 // front face
 // glTexCoord2f(0, 1);
  glVertex3f(width,height,length*0.5);
 // glTexCoord2f(1,1);
  glVertex3f(width+0.8 ,height, length*0.5);
 // glTexCoord2f(1,0);
  glVertex3f(width+0.8, 0., length*0.5);
 // glTexCoord2f(0, 0);
  glVertex3f(width, 0., length*0.5);

 //right face
 // glTexCoord2f(0, 1);
  glVertex3f(width+0.8,height,length*0.5);
 // glTexCoord2f(1, 1);
  glVertex3f(width+0.8,height, length*0.7);
//  glTexCoord2f(1, 0);
  glVertex3f(width+0.8, 0., length*0.7);
 // glTexCoord2f(0, 0);
  glVertex3f(width+0.8, 0., length*0.5);

 // left face
 // glTexCoord2f(0, 1);
  glVertex3f(width,height, length*0.5);
 // glTexCoord2f(1, 1);
  glVertex3f(width,height, length*0.7);
 // glTexCoord2f(1, 0);
  glVertex3f(width, 0., length*0.7);
 // glTexCoord2f(0, 0);
  glVertex3f(width, 0., length*0.5);

 // back face
 // glTexCoord2f(0, 1);
  glVertex3f(width,height, length*0.7);
 // glTexCoord2f(1, 1);
  glVertex3f(width+0.8,height, length*0.7);
 // glTexCoord2f(1, 0);
  glVertex3f(width+0.8, 0., length*0.7);
 // glTexCoord2f(0, 0);
  glVertex3f(width, 0., length*0.7);

//  top face
 // glTexCoord2f(0, 1);
  glVertex3f(width,height, length*0.5);
 // glTexCoord2f(1, 1);
  glVertex3f(width+0.8,height, length*0.5);
 // glTexCoord2f(1, 0);
  glVertex3f(width+0.8,height, length*0.7);
 // glTexCoord2f(0, 0);
  glVertex3f(width,height, length*0.7);

 // bottom face
 // glTexCoord2f(0, 1);
  glVertex3f(width, 0., length*0.5);
 // glTexCoord2f(1, 1);
  glVertex3f(width+0.8 ,0., length*0.5);
 // glTexCoord2f(1, 0);
  glVertex3f(width+0.8, 0., length*0.7);
  //glTexCoord2f(0, 0);
  glVertex3f(width, 0., length*0.7);

 glEnd();



}
void FencePart::DrawFence()
{

}