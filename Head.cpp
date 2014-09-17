#include "Head.h"

Head::Head(void)
{
	verticesCount=48;
	trianglesCount=(verticesCount/6+1)*10;
	vertices=new Point3D[verticesCount];

	triangles=new Triangle[trianglesCount];
	GLfloat bigRadius=1.6, smallRadius=1.2;
	GLfloat heightBetween=0.2;

	int i=0;
	for(double t=0.0; t<2*PI; t+=0.785)
	{
		/*vertices[i]=Point3D(50.0/100*bigRadius*cos(t), 0.0,  50.0/100*smallRadius*sin(t));
		vertices[i+8]=Point3D(bigRadius*cos(t), 2.5*heightBetween,  smallRadius*sin(t));
		vertices[i+16]=Point3D(81.25/100*bigRadius*cos(t), 6*heightBetween,  81.25/100*smallRadius*sin(t));
		vertices[i+24]=Point3D(56.25/100*bigRadius*cos(t), 8.0*heightBetween,  56.25/100*smallRadius*sin(t));		
		vertices[i+32]=Point3D(46.875/100*bigRadius*cos(t), 11.0*heightBetween,  46.875/100*smallRadius*sin(t));
		vertices[i+40]=Point3D(12.5/100*bigRadius*cos(t), 14.0*heightBetween,  12.5/100*smallRadius*sin(t));
		i++;*/
		vertices[i]=Point3D(80.0/100*bigRadius*cos(t), 0.0,  80.0/100*smallRadius*sin(t));
		vertices[i+8]=Point3D(bigRadius*cos(t), 0.6,  smallRadius*sin(t));
		vertices[i+16]=Point3D(90.0/100*bigRadius*cos(t), 1.2,  90.0/100*smallRadius*sin(t));
		vertices[i+24]=Point3D(60.0/100*bigRadius*cos(t), 1.7,  60.0/100*smallRadius*sin(t));		
		vertices[i+32]=Point3D(50.0/100*bigRadius*cos(t), 2.1,  50.0/100*smallRadius*sin(t));
		vertices[i+40]=Point3D(30.0/100*bigRadius*cos(t), 2.7,  30.0/100*smallRadius*sin(t));
		i++;
	}

	int m=verticesCount/6;
	int j=0;
	for(i=0;i<m-1;i++)
	{
		
		triangles[j++]=Triangle(m+i, i, i+1);
		triangles[j++]=Triangle(m+i, i+1, m+i+1);
		triangles[j++]=Triangle(2*m+i, m+i, m+i+1);
		triangles[j++]=Triangle(2*m+i, m+i+1, 2*m+i+1);
		triangles[j++]=Triangle(3*m+i, 2*m+i, 2*m+i+1);
		triangles[j++]=Triangle(3*m+i, 2*m+i+1, 3*m+i+1);
		triangles[j++]=Triangle(4*m+i, 3*m+i, 3*m+i+1);
		triangles[j++]=Triangle(4*m+i, 3*m+i+1, 4*m+i+1);
		triangles[j++]=Triangle(5*m+i, 4*m+i, 4*m+i+1);
		triangles[j++]=Triangle(5*m+i, 4*m+i+1, 5*m+i+1);
	}
	i--;	
	triangles[j++]=Triangle(m+i, i+1, 0);
	triangles[j++]=Triangle(m+i, 0, m);
	triangles[j++]=Triangle(5*m+i+1, 4*m+i+1, 5*m);
	triangles[j++]=Triangle(5*m, 4*m+i+1, 4*m);

	for(i=0;i<m/2;i++)
	{
		triangles[j++]=Triangle(4*m+i, 4*m+m-i-1, 4*m+i+1);
		triangles[j++]=Triangle(4*m+i, 4*m+i+1, 4*m+m-i-2);
	}

	triangles[j++]=Triangle(4*m+i, 4*m+m-i-1, 4*m+m-1);
	triangles[j]=Triangle(4*m+i, 4*m+m-i-1, 4*m);
}

void Head::DrawObject()
{
	/*glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[0]);*/
	glBegin(GL_TRIANGLES);
		for(int i=0;i<trianglesCount;i++)
		{
			/*Point3D v = vertices[triangles[i].p1];
			glTexCoord2f(0.5, 0); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
			Point3D v1 = vertices[triangles[i].p2];
			glTexCoord2f(0, 1); glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
			Point3D v2 = vertices[triangles[i].p3];
			glTexCoord2f(1, 1); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);*/

			glColor3f(0.0, 1.0, 0.0); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
			glColor3f(0.0, 1.0, 0.0);glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
			glColor3f(0.0, 1.0, 0.0); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);
		}
	glEnd();
}

void Head::Update()
{
}

Head::~Head(void)
{
}
