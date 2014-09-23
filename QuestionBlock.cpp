#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(OnRoadObject* insideObject, Road* road, GLfloat width, GLfloat height, GLfloat length)
{	
	this->insideObject=insideObject;
	this->width=width;
    this->height=height;
	this->length=length;
	this->textureIndex=2;
	AddCollider();

	this->road = road;
	road->AddRoadObject(this);
}

QuestionBlock::~QuestionBlock(void)
{
}

void QuestionBlock::Hit()
{ if(textureIndex==2)
{
	insideObject->AddCollider();
	
	insideObject->Rotate(rotate);
	insideObject->Translate(translate);
	insideObject->Translate(Point3D(0,length,0));
	scene->AddObject(insideObject);

	road->AddRoadObject(insideObject);

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
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,length*0.75, 0-height/2);
  glTexCoord2f(1,1);glVertex3f(width/2 ,length*0.75, 0-height/2);
  glTexCoord2f(1,0);glVertex3f(width/2, 0., 0-height/2);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., 0-height/2);

 //right face
  glTexCoord2f(0, 1);glVertex3f(width/2,length*0.75,0-height/2);
  glTexCoord2f(1, 1);glVertex3f(width/2,length*0.75, height/2);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., height/2);
  glTexCoord2f(0, 0);glVertex3f(width/2, 0., 0-height/2);

 // left face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,length*0.75, 0-height/2);
  glTexCoord2f(1, 1);glVertex3f(0.-width/2,length*0.75, height/2);
  glTexCoord2f(1, 0);glVertex3f(0.-width/2, 0., height/2);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., 0-height/2);

 // back face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,length*0.75, height/2);
  glTexCoord2f(1, 1);glVertex3f(width/2,length*0.75, height/2);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., height/2);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., height/2);

//  top face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2,length*0.75, 0-height/2);
  glTexCoord2f(1, 1);glVertex3f(width/2,length*0.75, -height/2);
  glTexCoord2f(1, 0);glVertex3f(width/2,length*0.75, height/2);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2,length*0.75, height/2);

 // bottom face
  glTexCoord2f(0, 1);glVertex3f(0.-width/2, 0., 0-height/2);
  glTexCoord2f(1, 1);glVertex3f(width/2 ,0., 0-height/2);
  glTexCoord2f(1, 0);glVertex3f(width/2, 0., height/2);
  glTexCoord2f(0, 0);glVertex3f(0.-width/2, 0., height/2);
 glEnd();


  glEnd();
  
}