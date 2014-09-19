#include "PlantHead.h"
#define PI 3.14

PlantHead::PlantHead(GLfloat width, GLfloat height, GLfloat size)
{
	this->width=width;
	this->height=height;
	this->size=size;

}
PlantHead::~PlantHead(void)
{
}
void PlantHead::DrawObject()
{   glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[4]); 
    glColor3f(1,1,1);
	
	GLfloat radius=sqrt(width*width+height*height)/3;

	vector<Point3D> head;
	vector<Point3D> mouth;
	vector<Point3D> lips;
	vector<Point3D>lipdown;
   
	for(double t=0;t<PI;t+=0.1)

		mouth.push_back(Point3D(radius*0.75* cos(t), size*0.4, radius*0.75 * sin(t)));
        mouth.push_back(Point3D(radius *0.75* cos(0.0), size*0.4, radius*0.75 * sin(0.0)));
 
	 for(double t=PI;t<2*PI;t+=0.1)
		
		lipdown.push_back(Point3D(radius*0.75* cos(t), size*0.4, radius*0.75 * sin(t)));
        lipdown.push_back(Point3D(radius *0.75* cos(0.0), size*0.4, radius*0.75 * sin(0.0)));
 
    for(double t=PI;t<2*PI;t+=0.1)
		
		lips.push_back(Point3D(radius*0.9* cos(t), size*0.4-size*0.05, radius*0.9 * sin(t)));
        lips.push_back(Point3D(radius *0.9* cos(0.0), size*0.4-size*0.05, radius*0.9 * sin(0.0)));
 
 

  double mouthstep=1./mouth.size();
  double j=0;

    for(int i=0;i<mouth.size()-1;i++)
	{
		glBegin(GL_QUADS);
		   
		    glTexCoord2f(j,0.f);
			glVertex3f(mouth[i].x, mouth[i].y, mouth[i].z);
			glTexCoord2f(j+mouthstep,0.);
			glVertex3f(mouth[i+1].x, mouth[i+1].y, mouth[i+1].z);
	        glTexCoord2f(j+mouthstep,0.2f);
			glVertex3f(0.8*mouth[i+1].x, mouth[i+1].y-size*0.1, 0.8*mouth[i+1].z);
            glTexCoord2f(j, 0.2f);
			glVertex3f(0.8 * mouth[i].x, mouth[i].y-size*0.1 , 0.8*mouth[i].z);

       glEnd();


		glBegin(GL_QUADS);
		    glTexCoord2f(j,0.2f);
			glVertex3f(0.8*mouth[i].x, mouth[i].y-size*0.1, mouth[i].z*0.8);
			glTexCoord2f(j+mouthstep,0.2f);
			glVertex3f(0.8*mouth[i+1].x, mouth[i+1].y-size*0.1, mouth[i+1].z*0.8);
	        glTexCoord2f(j+mouthstep,0.4f);
			glVertex3f(0.6*mouth[i+1].x, mouth[i+1].y-size*0.3, 0.6*mouth[i+1].z);
            glTexCoord2f(j, 0.4f);
			glVertex3f(0.6 * mouth[i].x, mouth[i].y-size*0.3 , 0.6*mouth[i].z);
       
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		   glBegin(GL_TRIANGLE_FAN);
		   glTexCoord2f(0.5 + 0.5*mouth[i+1].x, 0.5+0.5*mouth[i+1].z);
			glVertex3f(0.6*mouth[i+1].x, mouth[i+1].y - size*0.3, 0.6*mouth[i+1].z);
			glTexCoord2f(0.5 + 0.5*mouth[i].x, 0.5+0.5*mouth[i].z);
			glVertex3f(0.6 * mouth[i].x, mouth[i].y - size*0.3, 0.6*mouth[i].z);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0,mouth[i].y-size*0.3,0);
			glEnd();


		j+=mouthstep;
	}



	 for (double t = 0; t < 2 * PI; t = t + 0.1)
	 head.push_back(Point3D(radius*0.75* cos(t), size*0.4, radius*0.75 * sin(t)));
     
	 head.push_back(Point3D(radius *0.75* cos(0.0), size*0.4, radius*0.75 * sin(0.0)));

     double step=1./head.size();
	 j=0;
	 
	 for(int i = 0; i < head.size() - 1; i++)
	 {
		


       glBegin(GL_QUADS);
		    glTexCoord2f(j,0.4f);
			glVertex3f(head[i].x, head[i].y, head[i].z);
			glTexCoord2f(j+step,0.4);
			glVertex3f(head[i+1].x, head[i+1].y, head[i+1].z);
	        glTexCoord2f(j+step,0.6f);
			glVertex3f(0.8*head[i+1].x, head[i+1].y + size*0.15, 0.8*head[i+1].z);
            glTexCoord2f(j, 0.6f);
			glVertex3f(0.8 * head[i].x, head[i].y + size*0.15, 0.8*head[i].z);
        glEnd();

        glBegin(GL_QUADS);
		    glTexCoord2f(j,0.6f);
			glVertex3f(head[i].x*0.8, head[i].y+size*0.15, head[i].z*0.8);
			glTexCoord2f(j+step,0.6);
			glVertex3f(head[i+1].x*0.8, head[i+1].y+size*0.15, head[i+1].z*0.8);
	        glTexCoord2f(j+step,0.8);
			glVertex3f(0.6*head[i+1].x, head[i+1].y + size*0.25, 0.6*head[i+1].z);
            glTexCoord2f(j, 0.8f);
			glVertex3f(0.6 * head[i].x, head[i].y +size* 0.25, 0.6*head[i].z);
	    
        glEnd();

       glBegin(GL_QUADS);
		    glTexCoord2f(j,0.8f);
			glVertex3f(head[i].x*0.6, head[i].y+size*0.25, head[i].z*0.6);
			glTexCoord2f(j+step,0.8f);
			glVertex3f(head[i+1].x*0.6, head[i+1].y+size*0.25, head[i+1].z*0.6);
	       glTexCoord2f(j+step,1.0f);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + size*0.27, 0.5*head[i+1].z);
            glTexCoord2f(j, 1.0f);
			glVertex3f(0.5 * head[i].x, head[i].y + size*0.27, 0.5*head[i].z);
	     
        glEnd();

       
      //top-head
		glBegin(GL_TRIANGLE_FAN);
		 //  glTexCoord2f(0.5 + 0.5*head[i+1].x, 0.5+0.5*head[i+1].z);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + size*0.27, 0.5*head[i+1].z);
		//	glTexCoord2f(0.5 + 0.5*head[i].x, 0.5+0.5*head[i].z);
			glVertex3f(0.5 * head[i].x, head[i].y + size*0.27, 0.5*head[i].z);
		//	glTexCoord2f(0.5,0.5);
			glVertex3f(0,head[i].y+size*0.27,0);
			glEnd();


		j+=step;
	 }

	  for(int i=0;i<lips.size()-1;i++)
	{
	   glColor3f(1,1,1);
		
	   glBegin(GL_QUADS);

		  // glTexCoord2f(j,0.f);
			glVertex3f(lipdown[i].x, lipdown[i].y, lipdown[i].z);
			//glTexCoord2f(j+mouthstep,0.);
			glVertex3f(lipdown[i+1].x,lipdown[i+1].y, lipdown[i+1].z);
	       // glTexCoord2f(j+mouthstep,0.2f);
			glVertex3f(lips[i+1].x, lips[i+1].y, lips[i+1].z);
           // glTexCoord2f(j, 0.2f);
			glVertex3f(lips[i].x, lips[i].y , lips[i].z);
       
       glEnd();

	  glBegin(GL_TRIANGLE_FAN);

	      glVertex3f(lips[i].x, lips[i].y, lips[i].z);
		  glVertex3f(lips[i+1].x, lips[i+1].y, lips[i+1].z);
		  glVertex3f(0,lips[i+1].y, 0);

	  glEnd();
    }
	  glBegin(GL_QUADS);

	    glVertex3f(lipdown[0].x, lipdown[0].y, lipdown[0].z);
		glVertex3f(lipdown[lips.size()-1].x, lipdown[lips.size()-1].y, lipdown[lips.size()-1].z);
		glVertex3f(0.5*head[0].x, head[0].y + size*0.27, 0.5*head[0].z);
        glVertex3f(0.5 * head[head.size()-1].x, head[head.size()-1].y + size*0.27, 0.5*head[head.size()-1].z);
     
	 glEnd();

}