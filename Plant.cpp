#include "Plant.h"
#define PI 3.14
Plant::Plant(GLfloat width, GLfloat height, GLfloat size)
{
	this->width=width;
	this->height=height;
	this->size=size;

}

Plant::~Plant(void)
{

}
void Plant::DrawObject()
{ 
    GLfloat radius=sqrt(width*width+height*height)/8;
    vector<Point3D>base; 
	vector<Point3D>head;
    
   

	double initialsize=0;
	double pass=0;
    double centre=0;;
    int k;
    double step=1./base.size();
    double j=0;
    glColor3f(0,1,0);
	for(int i=0;i<4;i++)
	{
		for (double t = 0; t < 2 * PI; t = t + 0.1)
		
			base.push_back(Point3D(centre+radius*0.5*cos(t), initialsize+size*pass, centre+ radius*0.5*sin(t)));
	        
		
		base.push_back(Point3D(centre+radius*0.5*cos(0.),initialsize+pass*size,0));
		

   	for( k=0;k<base.size()-1;k++)
	{
		//body
		glBegin(GL_TRIANGLES);
		//	glTexCoord2f(j, 0.0f); 
			glVertex3f(base[k].x, base[k].y, base[k].z);				
		//	glTexCoord2f(j, 1.0f);
			glVertex3f(base[k].x, initialsize+size*0.4, base[k].z);
		//	glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x, initialsize+size*0.4, base[k+1].z);
		glEnd();

        glBegin(GL_TRIANGLES);
		//	glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x, initialsize+size*0.4, base[k+1].z);
		//	glTexCoord2f(j+step, 0.0f); 
			glVertex3f(base[k+1].x, base[k+1].y, base[k+1].z);
		//	glTexCoord2f(j, 0.0f);
			glVertex3f(base[k].x, base[k].y, base[k].z);
		glEnd();



	}
	
		base.clear();
	pass+=0.4*size;
		centre+=0.1*size;
		initialsize+=size*pass;
	}


}