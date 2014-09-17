#include "Foot.h"
#include "Textures.h"

Foot::Foot()
{
	verticesCount=16;
	trianglesCount=(verticesCount/2+1)*4;
	vertices=new Point3D[verticesCount];

	int i=0, j=8;
	for(double t=0.0; t<2*PI; t+=0.785)
	{
		vertices[i]=Point3D(0.8*cos(t), 0.0,  0.4*sin(t));
		vertices[j]=Point3D(0.6*cos(t), 0.5,  0.2*sin(t));
		i++;
		j++;
	}
	

	int m=verticesCount/2;
	triangles=new Triangle[trianglesCount];
	j=0;
	for(i=0;i<m-1;i++)
	{
		triangles[j++]=Triangle(m+i, i, i+1);
		triangles[j++]=Triangle(m+i, i+1, m+i+1);
	}

	i--;

	/*triangles[j++]=Triangle(m+i, i+1, 0);
	triangles[j++]=Triangle(m+i, 0, m);
	triangles[j++]=Triangle(2*m+i+1, m+i+1, 2*m);
	triangles[j]=Triangle(2*m, m+i+1, m);*/


	triangles[j++]=Triangle(m+i, i+1, 0);
	triangles[j++]=Triangle(m+i, 0, m);
	triangles[j++]=Triangle(m, m-1, 0);

	for(i=0;i<m/2;i++)
	{
		triangles[j++]=Triangle(i, m-i-1, m-i-2);
		triangles[j++]=Triangle(i, m-i-2, i+1);
		triangles[j++]=Triangle(m+i, m+m-i-1, m+m-i-2);
		triangles[j++]=Triangle(m+i, m+m-i-2, m+i+1);
	}

	triangles[j++]=Triangle(i, m-i-1, m-1);
	triangles[j++]=Triangle(i, m-i-1, 0);
	triangles[j++]=Triangle(m+i, m+m-i-1, m+m-1);
	triangles[j]=Triangle(m+i, m+m-i-1, m);
}

void Foot::DrawObject()
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

			glColor3f(1.0, 0.0, 0.0); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
			glColor3f(1.0, 0.0, 0.0);glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
			glColor3f(1.0, 0.0, 0.0); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);
		}
	glEnd();
}

void Foot:: Update()
{
}

Foot::~Foot(void)
{
}
