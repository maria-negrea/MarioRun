#include "PlantTulip.h"

#define PI 3.14
PlantTulip::PlantTulip(GLfloat width, GLfloat height, GLfloat size)
{
	this->width=width;
	this->height=height;
	this->size=size;
	this->target=NULL;
	contor=0;
}

PlantTulip::~PlantTulip(void)
{
}
void PlantTulip::SetTarget(WorldObject *newtarget)
{
	if(newtarget!=NULL)
	{
		this->target=newtarget;
	}
}
void PlantTulip::DrawObject()
{
GLfloat radius=sqrt(width*width+height*height)/8;
    vector<Point3D>base; 
	vector<Point3D>head;
	vector<Point3D>top;
    
   

	double initialsize=0;
	
    int k;
    double step=1./base.size();
    double j=0;
    glColor4f(0,1,0,1);	



	for (double t = 0; t < 2 * PI; t = t + 0.1)
		  base.push_back(Point3D(radius*0.5*cos(t), initialsize,  radius*0.5*sin(t)));
	    
	
	double pass=0;
	double sizepass=0.5*size;
	for(int i=0;i<2;i++)
	{

   	for( k=0;k<base.size()-1;k++)
	{
		//body


		glBegin(GL_TRIANGLES);
		//	glTexCoord2f(j, 0.0f); 
			glVertex3f(base[k].x, base[k].y+initialsize, base[k].z);				
		//	glTexCoord2f(j, 1.0f);
			glVertex3f(base[k].x-pass, base[k].y+sizepass+initialsize, base[k].z-pass);
		//	glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x-pass, base[k+1].y+sizepass+initialsize, base[k+1].z-pass);
		glEnd();

        glBegin(GL_TRIANGLES);
		//	glTexCoord2f(j+step, 1.0f); 
			glVertex3f(base[k+1].x-pass, base[k+1].y+sizepass+initialsize, base[k+1].z-pass);
		//	glTexCoord2f(j+step, 0.0f); 
			glVertex3f(base[k+1].x, base[k+1].y+initialsize, base[k+1].z);
		//	glTexCoord2f(j, 0.0f);
			glVertex3f(base[k].x, base[k].y+initialsize, base[k].z);
		glEnd();
	}

    if(i%2==0)
		pass-=width*0.2;
	else 
		pass+=width*0.2;
   
	initialsize+=sizepass;
	}

}
void PlantTulip::Update()
{	//scene->AddObject(fireBall);
	
	if(target != NULL)
	 {  
		  Point3D point = target->GetTranslate()-GetTranslate();
		  point.y = 0;
		  GLfloat angleToTarget = AngleBetween(point);
		  Rotate(Point3D(0.0,angleToTarget, 0.0));

		  if(contor==10)
		  {
			  FireBall *fireBall=new FireBall(0.5);
			  fireBall->AddCollider();
			  scene->AddObject(fireBall);
			  fireBall->Translate(GetRight()*0.5+GetForward()*1);
			  fireBall->Rotate(rotate);
			  fireBall->Translate(translate);
			  contor=0;
		  }
		  contor++;
	 }
}