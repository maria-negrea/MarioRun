#include "Torso.h"

Torso::Torso(void)
{
	verticesCount=24;
	trianglesCount=(verticesCount/3+1)*6;
	vertices=new Point3D[verticesCount];

	int i=0, j=8, k=16;
	GLfloat bigRadius=0.8, smallRadius=0.7;
	for(double t=0.0; t<2*PI; t+=0.785)
	{
		vertices[i++]=Point3D(60.0/100*bigRadius*cos(t), 0.0,  60.0/100*smallRadius*sin(t));
		vertices[j++]=Point3D(bigRadius*cos(t), 0.3,  smallRadius*sin(t));
		vertices[k++]=Point3D(70.0/100*bigRadius*cos(t), 1.0,  70.0/100*smallRadius*sin(t));
	}

	triangles=new Triangle[trianglesCount];

	int m=verticesCount/3;
	j=0;
	for(i=0;i<m-1;i++)
	{
		
		triangles[j++]=Triangle(m+i, i, i+1);
		triangles[j++]=Triangle(m+i, i+1, m+i+1);
		triangles[j++]=Triangle(2*m+i, m+i, m+i+1);
		triangles[j++]=Triangle(2*m+i, m+i+1, 2*m+i+1);
	}
	i--;	
	triangles[j++]=Triangle(m+i, i+1, 0);
	triangles[j++]=Triangle(m+i, 0, m);
	triangles[j++]=Triangle(2*m+i+1, m+i+1, 2*m);
	triangles[j++]=Triangle(2*m, m+i+1, m);

	for(i=0;i<m/2;i++)
	{
		triangles[j++]=Triangle(m-i-1, i, i+1);
		triangles[j++]=Triangle(m-i-1, i+1, m-i-2);
	}

	/*triangles[j++]=Triangle(4*m+i, 4*m+m-i-1, 4*m+m-1);
	triangles[j]=Triangle(4*m+i, 4*m+m-i-1, 4*m);*/

}

void Torso::DrawObject()
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

			glColor3f(1.0, 1.0, 0.0); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
			glColor3f(1.0, 1.0, 0.0);glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
			glColor3f(1.0, 1.0, 0.0); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);
		}
	glEnd();
}

void Torso:: Update()
{
}

Torso::~Torso(void)
{
}
