#include "SplitBox.h"

SplitBox::SplitBox(GLfloat width, GLfloat height, GLfloat length)
{
	this->width=width;
	this->height=height;
	this->length=length;
}

SplitBox::~SplitBox(void)
{
}
void SplitBox::DrawObject()
{
	if(WorldObject::isSummer)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[3]);
	}
	if(WorldObject::isWinter)
	{
		glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[32]);
	}
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
void SplitBox::Split()
{
   for(int i=0;i<4;i++)
   {
	SmallBox *smallBox=new SmallBox(width,height, length);
	smallBox->Translate(translate);
	if(i%2==0)
	smallBox->Translate(Point3D(i*2,height*i,i*2));
	else smallBox->Translate(Point3D(-i*2, height *1.5, -i*2));
	scene->AddObject(smallBox);
      
   }

   	scene->RemoveObject(this);
}

bool SplitBox::Function(Mario *mario)
{
	if(mario->IsBig())
	{
		Split();
		return true;
	}

	return false;
}

