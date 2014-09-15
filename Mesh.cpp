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
		for(int i=0;i<tiranlgles.size();i++)
		{
			glTexCoord2f(0, 0); glVertex3f( vertices[tirangles[i][0]].x, vertices[tirangles[i][0]].y, vertices[tirangles[i][0]].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[tirangles[i][1]].x, vertices[tirangles[i][1]].y, vertices[tirangles[i][1]].z);
			glTexCoord2f(0, 0); glVertex3f( vertices[tirangles[i][2]].x, vertices[tirangles[i][2]].y, vertices[tirangles[i][2]].z);
		}
	glEnd();
}