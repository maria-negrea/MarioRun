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

#include "Star.h"
void QuestionBlock::Hit()
{
	if(textureIndex==2)
	{
		insideObject->AddCollider();
		
		insideObject->Rotate(rotate);
		insideObject->Translate(translate);
		insideObject->Translate(Point3D(0,length,0));

		scene->AddObject(insideObject);

		road->AddRoadObject(insideObject);
		insideObject->SetIndex(roadIndex);

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
  glTexCoord2f(1,1);glVertex3f(0. ,length*0.75, 0);
  glTexCoord2f(0,1);glVertex3f(width ,length*0.75, 0);
  glTexCoord2f(0,0);glVertex3f(width, 0., 0);
  glTexCoord2f(1, 0);glVertex3f(0., 0., 0);

 //right face
  glTexCoord2f(1, 1);glVertex3f(width, length*0.75,0);
  glTexCoord2f(0, 1);glVertex3f(width, length*0.75, height);
   glTexCoord2f(0, 0);glVertex3f(width, 0., height);
  glTexCoord2f(1, 0);glVertex3f(width, 0., 0);
 
 

 // left face
  glTexCoord2f(0, 1);glVertex3f(0., length*0.75, 0);
  glTexCoord2f(1, 1);glVertex3f(0., length*0.75, height);
  glTexCoord2f(1, 0);glVertex3f(0., 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., 0);

 // back face
  glTexCoord2f(0, 1);glVertex3f(0., length*0.75, height);
  glTexCoord2f(1, 1);glVertex3f(width, length*0.75, height);
  glTexCoord2f(1, 0);glVertex3f(width, 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., height);

 // top face
  glTexCoord2f(0, 1);glVertex3f(0., length*0.75, 0);
  glTexCoord2f(1, 1);glVertex3f(width, length*0.75, 0);
  glTexCoord2f(1, 0);glVertex3f(width, length*0.75, height);
  glTexCoord2f(0, 0);glVertex3f(0., length*0.75, height);

 // bottom face
  glTexCoord2f(0, 1);glVertex3f(0., 0., 0);
  glTexCoord2f(1, 1);glVertex3f(width ,0., 0);
  glTexCoord2f(1, 0);glVertex3f(width, 0., height);
  glTexCoord2f(0, 0);glVertex3f(0., 0., height);
 glEnd();


  
  
}