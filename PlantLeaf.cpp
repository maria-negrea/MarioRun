#include "PlantLeaf.h"
#define PI 3.14
PlantLeaf::PlantLeaf(GLfloat width, GLfloat height, GLfloat size)
{   this->width=width;
	this->height=height;
	this->size=size;
}

PlantLeaf::~PlantLeaf(void)
{
}
void PlantLeaf::DrawObject()
{
	glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[5]); 
	glColor4f(1.0f,1.0f,1.0f, 1.0f);

	glBegin(GL_QUADS);
      glTexCoord2f(0.f,0.f);
	  glVertex3f(0,0,0);
      glTexCoord2f(0.f,1.f);
	  glVertex3f(0,0,height*0.3);
      glTexCoord2f(0.33f,1.f);
	  glVertex3f(width*0.2,size*0.3,height*0.3);
      glTexCoord2f(0.33,0.f);
	  glVertex3f(width*0.2,size*0.3,0);

      glTexCoord2f(0.33f,0.f);
	  glVertex3f(width*0.2,size*0.3,0);
      glTexCoord2f(0.33f,1.f);
	  glVertex3f(width*0.2, size*0.3,height*0.3);
      glTexCoord2f(0.66f,1.f);
	  glVertex3f(width*0.2+width*0.3, size*0.3, height*0.3);
      glTexCoord2f(0.66f,0.f);
	  glVertex3f(width*0.2+width*0.3, size*0.3, 0);

	  glTexCoord2f(0.66f,0.f);
	  glVertex3f(width*0.2+width*0.3, size*0.3, 0);
	  glTexCoord2f(0.66f,1.f);
	  glVertex3f(width*0.2+width*0.3, size*0.3, height*0.3);
	  glTexCoord2f(1.f,1.f);
	  glVertex3f(width*0.6,0,height*0.3);
	  glTexCoord2f(1.f,0.f);
	  glVertex3f(width*0.6,0, height*0);
	  
  glEnd();

  glDisable(GL_BLEND);
 glEnable(GL_DEPTH_TEST);

}