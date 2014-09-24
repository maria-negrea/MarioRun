#include "FullMountain.h"

FullMountain::FullMountain(GLfloat width, GLfloat height,GLfloat length)
{
	this->width=width;
	this->height=height;
	this->length=length;
	Mountain *mountain=new Mountain(width/2, height*0.6, length);
	mountain->Translate(Point3D(-width/2,0,0));
	
	 this->AddChild(mountain);
	 
}

FullMountain::~FullMountain(void)
{
}
void FullMountain::DrawObject()
{
	GLfloat radius=sqrt(width*width+length*length)/2.;

	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[17]); 
	
    vector<Point3D>base; 
	vector<Point3D>head;
 
    int k;
    double step=1./base.size();
    double j=0;

	 for (double t = 0; t < 2 * 3.14; t = t + 0.1)
	 head.push_back(Point3D(radius*0.75* cos(t), 0, radius*0.75 * sin(t)));
      head.push_back(Point3D(radius *0.75* cos(0.0), 0, radius*0.75 * sin(0.0)));

     step=1./head.size();
	 j=0;
	 
	 for(int i = 0; i < head.size() - 1; i++)
	 {
		

        glBegin(GL_QUADS);
		    glTexCoord2f(j,0.f);
			glVertex3f(head[i].x, head[i].y, head[i].z);
			glTexCoord2f(j+step,0.f);
			glVertex3f(head[i+1].x, head[i+1].y, head[i+1].z);
	        glTexCoord2f(j+step,0.25f);
			glVertex3f(0.9*head[i+1].x, head[i+1].y + height*0.2, 0.9*head[i+1].z);
            glTexCoord2f(j, 0.25f);
			glVertex3f(0.9 * head[i].x, head[i].y + height*0.2, 0.9*head[i].z);
        glEnd();

         glBegin(GL_QUADS);
		    glTexCoord2f(j,0.25f);
			glVertex3f(head[i].x*0.9, head[i].y+height*0.2, head[i].z*0.9);
			glTexCoord2f(j+step,0.25);
			glVertex3f(head[i+1].x*0.9, head[i+1].y+height*0.2, head[i+1].z*0.9);
	        glTexCoord2f(j+step,0.5f);
			glVertex3f(0.8*head[i+1].x, head[i+1].y + height*0.4, 0.8*head[i+1].z);
            glTexCoord2f(j, 0.5f);
			glVertex3f(0.8 * head[i].x, head[i].y + height*0.4, 0.8*head[i].z);
        glEnd();

        glBegin(GL_QUADS);
		    glTexCoord2f(j,0.5f);
			glVertex3f(head[i].x*0.8, head[i].y+height*0.4, head[i].z*0.8);
			glTexCoord2f(j+step,0.5);
			glVertex3f(head[i+1].x*0.8, head[i+1].y+height*0.4, head[i+1].z*0.8);
	        glTexCoord2f(j+step,0.75f);
			glVertex3f(0.7*head[i+1].x, head[i+1].y + height*0.6, 0.7*head[i+1].z);
            glTexCoord2f(j, 0.75f);
			glVertex3f(0.7 * head[i].x, head[i].y +height* 0.6, 0.7*head[i].z);
	     
        glEnd();

       glBegin(GL_QUADS);
		    glTexCoord2f(j,0.75f);
			glVertex3f(head[i].x*0.7, head[i].y+height*0.6, head[i].z*0.7);
			glTexCoord2f(j+step,0.75);
			glVertex3f(head[i+1].x*0.7, head[i+1].y+height*0.6, head[i+1].z*0.7);
	        glTexCoord2f(j+step,1.0f);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + height*0.8, 0.5*head[i+1].z);
            glTexCoord2f(j, 1.0f);
			glVertex3f(0.5 * head[i].x, head[i].y + height*0.8, 0.5*head[i].z);
	     
        glEnd();
       
      //top-head
		glBegin(GL_TRIANGLE_FAN);
		    glTexCoord2f(0.5 + 0.5*head[i+1].x, 0.5+0.5*head[i+1].z);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + height*0.8, 0.5*head[i+1].z);
			glTexCoord2f(0.5 + 0.5*head[i].x, 0.5+0.5*head[i].z);
			glVertex3f(0.5 * head[i].x, head[i].y + height*0.8, 0.5*head[i].z);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0,head[i].y+height*0.8,0);
			glEnd();


		j+=step;
	 }
}