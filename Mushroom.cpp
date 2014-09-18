#include "Mushroom.h"
#define PI 3.14
#include<vector>
Mushroom::Mushroom(GLfloat width, GLfloat height, GLfloat size)
{
	this->size=size;
	this->width=width;
	this->height=height;
	fallSpeed = 1;
	this->speed = 2;
}

Mushroom::~Mushroom(void)
{
}



void Mushroom::DrawMushroom()
{
	 //* texture for body*/
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[0]); 
	GLfloat radius=sqrt(width*width+height*height)/2;
    vector<Point3D>base; 
	vector<Point3D>head;
    

	//this->Translate(Point3D( width*0.5,0,height*0.5));
	//glTranslatef(width*0.5,0,height*0.5);

	for (double t = 0; t < 2 * PI; t = t + 0.1)
	base.push_back(Point3D(radius*0.5*cos(t), 0,  radius*0.5*sin(t)));
	
	base.push_back(Point3D(radius*0.5*cos(0.),0));
		

 
    int k;
    double step=1./base.size();
    double j=0;

   	for( k=0;k<base.size()-1;k++)
	{
		//body
		glBegin(GL_TRIANGLES);
			glTexCoord2f(j, 0.0f); 
			glVertex3f(base[k].x, base[k].y, base[k].z);				
			glTexCoord2f(j, 1.0f);
			glVertex3f(base[k].x, size*0.4, base[k].z);
			glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x, size*0.4, base[k+1].z);
		glEnd();

        glBegin(GL_TRIANGLES);
			glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x, size*0.4, base[k+1].z);
			glTexCoord2f(j+step, 0.0f); 
			glVertex3f(base[k+1].x, base[k+1].y, base[k+1].z);
			glTexCoord2f(j, 0.0f);
			glVertex3f(base[k].x, base[k].y, base[k].z);
		glEnd();


		//bottom
        glBegin(GL_TRIANGLE_FAN);
		    glTexCoord2f(0.75 +base[k+1].x, 0.75+base[k+1].z);
			glVertex3f(base[k+1].x, base[k+1].y, base[k+1].z);
			glTexCoord2f(0.75 +base[k].x, 0.75+base[k].z);
			glVertex3f( base[k].x, base[k].y, base[k].z);
			glTexCoord2f(0.75,0.75);
			glVertex3f(0,base[k].y,0);
			glEnd();

     j+=step;
	}


   //*texture for the head*/
   //head

	
	 glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[1]); 
     
	 for (double t = 0; t < 2 * PI; t = t + 0.1)
	 head.push_back(Point3D(radius*0.75* cos(t), size*0.4, radius*0.75 * sin(t)));
     
	 head.push_back(Point3D(radius *0.75* cos(0.0), size*0.4, radius*0.75 * sin(0.0)));

     step=1./head.size();
	 j=0;
	 
	 for(int i = 0; i < head.size() - 1; i++)
	 {
		 //bottom-head
         glBegin(GL_TRIANGLE_FAN);
		    glTexCoord2f(0.5 +head[i+1].x, 0.5+head[i+1].z);
			glVertex3f(head[i+1].x, head[i+1].y, head[i+1].z);
			glTexCoord2f(0.5 +head[i].x, 0.5+head[i].z);
			glVertex3f( head[i].x, head[i].y, head[i].z);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0,head[i].y,0);
		 glEnd();


        glBegin(GL_QUADS);
		    glTexCoord2f(j,0.f);
			glVertex3f(head[i].x, head[i].y, head[i].z);
			glTexCoord2f(j+step,0.f);
			glVertex3f(head[i+1].x, head[i+1].y, head[i+1].z);
	        glTexCoord2f(j+step,0.25f);
			glVertex3f(1.2*head[i+1].x, head[i+1].y + size*0.1, 1.2*head[i+1].z);
            glTexCoord2f(j, 0.25f);
			glVertex3f(1.2 * head[i].x, head[i].y + size*0.1, 1.2*head[i].z);
        glEnd();

         glBegin(GL_QUADS);
		    glTexCoord2f(j,0.25f);
			glVertex3f(head[i].x*1.2, head[i].y+size*0.1, head[i].z*1.2);
			glTexCoord2f(j+step,0.25);
			glVertex3f(head[i+1].x*1.2, head[i+1].y+size*0.1, head[i+1].z*1.2);
	        glTexCoord2f(j+step,0.5f);
			glVertex3f(0.8*head[i+1].x, head[i+1].y + size*0.2, 0.8*head[i+1].z);
            glTexCoord2f(j, 0.5f);
			glVertex3f(0.8 * head[i].x, head[i].y + size*0.2, 0.8*head[i].z);
        glEnd();

        glBegin(GL_QUADS);
		    glTexCoord2f(j,0.5f);
			glVertex3f(head[i].x*0.8, head[i].y+size*0.2, head[i].z*0.8);
			glTexCoord2f(j+step,0.5);
			glVertex3f(head[i+1].x*0.8, head[i+1].y+size*0.2, head[i+1].z*0.8);
	        glTexCoord2f(j+step,0.75f);
			glVertex3f(0.6*head[i+1].x, head[i+1].y + size*0.3, 0.6*head[i+1].z);
            glTexCoord2f(j, 0.75f);
			glVertex3f(0.6 * head[i].x, head[i].y +size* 0.3, 0.6*head[i].z);
	     
        glEnd();

       glBegin(GL_QUADS);
		    glTexCoord2f(j,0.75f);
			glVertex3f(head[i].x*0.6, head[i].y+size*0.3, head[i].z*0.6);
			glTexCoord2f(j+step,0.75);
			glVertex3f(head[i+1].x*0.6, head[i+1].y+size*0.3, head[i+1].z*0.6);
	        glTexCoord2f(j+step,1.0f);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + size*0.5, 0.5*head[i+1].z);
            glTexCoord2f(j, 1.0f);
			glVertex3f(0.5 * head[i].x, head[i].y + size*0.5, 0.5*head[i].z);
	     
        glEnd();
       
      //top-head
		glBegin(GL_TRIANGLE_FAN);
		    glTexCoord2f(0.5 + 0.5*head[i+1].x, 0.5+0.5*head[i+1].z);
			glVertex3f(0.5*head[i+1].x, head[i+1].y + size*0.5, 0.5*head[i+1].z);
			glTexCoord2f(0.5 + 0.5*head[i].x, 0.5+0.5*head[i].z);
			glVertex3f(0.5 * head[i].x, head[i].y + size*0.5, 0.5*head[i].z);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0,head[i].y+size*0.5,0);
			glEnd();


		j+=step;
	 }

}
void Mushroom::DrawObject()
{  
	 Mushroom::DrawMushroom();
}

void Mushroom::Update()
{
	PhysicsObject::Update();
	this->Translate(Point3D(0,0,speed));
	if(speed > 0.3)
		this->speed -= 0.01;
}