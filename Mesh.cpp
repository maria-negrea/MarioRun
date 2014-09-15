#include "Mesh.h"

Mesh::Mesh(void)
{
}

Mesh::~Mesh(void)
{
}

Mesh::Mesh( vector<Point3D> vertices, vector<Triangle> triangles)
	:vertices(vertices),triangles(triangles)
{
}

void Mesh::DrawObject()
{
	glBegin(GL_TRIANGLES);
		for(int i=0;i<triangles.size();i++)
		{
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i][0]].x, vertices[triangles[i][0]].y, vertices[triangles[i][0]].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i][1]].x, vertices[triangles[i][1]].y, vertices[triangles[i][1]].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[triangles[i][2]].x, vertices[triangles[i][2]].y, vertices[triangles[i][2]].z);
		}
	glEnd();
}