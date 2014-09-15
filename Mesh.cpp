#include "Mesh.h"

Mesh::~Mesh(void)
{
}

Mesh::Mesh( Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount)
	:vertices(vertices),triangles(triangles),verticesCount(verticesCount),trianglesCount(trianglesCount)
{
}

void Mesh::DrawObject()
{
	glBegin(GL_TRIANGLES);
		for(int i=0;i<trianglesCount;i++)
		{
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);
		}
	glEnd();
}