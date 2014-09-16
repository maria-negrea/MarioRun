#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(GLfloat width, GLfloat height, GLfloat size)
{	
	this->width=width;
    this->height=height;
	this->size=size;
	this->textureIndex=2;
}

QuestionBlock::~QuestionBlock(void)
{
}

void QuestionBlock::Hit()
{ if(textureIndex==2)
{
	Mushroom *newMushroom=new Mushroom(0.5,0.5,0.5);
	
	newMushroom->Translate(Point3D(width*0.5,size*0.75,2));
	scene->AddObject(newMushroom);
	
		textureIndex=3;
}
	else return;
}
void QuestionBlock::SetIndex(int newIndex)
{
	this->textureIndex=newIndex;
}
void QuestionBlock::DrawObject()
{
glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[textureIndex]);
  glBegin(GL_QUADS);
 // front face
  glTexCoord2f(0, 1);glVertex3f(0. ,size*0.75, 0);
  glTexCoord2f(1,1);glVertex3f(width ,size*0.75, 0);
  glTexCoord2f(1,0);glVertex3f(width, 0., 0);
  glTexCoord2f(0, 0);glVertex3f(0., 0., 0);

 //right face
  glTexCoord2f(0, 1);glVertex3f(width, size*0.75,0);
  glTexCoord2f(1, 1);glVertex3f(width, size*0.75, height);
  glTexCoord2f(1, 0);glVertex3f(width, 0., height);
  glTexCoord2f(0, 0);glVertex3f(width, 0., 0);

 // left face
  glTexCoord2f(0, 1);glVertex3f(0., size*0.75, 0);
  glTexCoord2f(1, 1);glVertex3f(0., size*0.75, height);
  glTexCoord2f(1, 0);glVertex3f(0., 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., 0);

 // back face
  glTexCoord2f(0, 1);glVertex3f(0., size*0.75, height);
  glTexCoord2f(1, 1);glVertex3f(width, size*0.75, height);
  glTexCoord2f(1, 0);glVertex3f(width, 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., height);

//  top face
  glTexCoord2f(0, 1);glVertex3f(0., size*0.75, 0);
  glTexCoord2f(1, 1);glVertex3f(width, size*0.75, 0);
  glTexCoord2f(1, 0);glVertex3f(width, size*0.75, height);
  glTexCoord2f(0, 0);glVertex3f(0., size*0.75, height);

 // bottom face
  glTexCoord2f(0, 1);glVertex3f(0., 0., 0);
  glTexCoord2f(1, 1);glVertex3f(width ,0., 0);
  glTexCoord2f(1, 0);glVertex3f(width, 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., height);
 glEnd();


  glEnd();
  
}