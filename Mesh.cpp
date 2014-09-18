#include "Mesh.h"
#include "Textures.h"

Mesh::Mesh()
{
}

Mesh::~Mesh(void)
{
	//delete[] vertices;
	//delete[] triangles;
}

Mesh::Mesh(Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount)
	:vertices(vertices),triangles(triangles),verticesCount(verticesCount),trianglesCount(trianglesCount)
{
}

void Mesh::DrawObject()
{
	int currentTextureIndex=triangles[0].textureIndex;
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[currentTextureIndex]);

	for(int i=0;i<trianglesCount;i++)
	{
		if(currentTextureIndex!=triangles[i].textureIndex)
		{
			currentTextureIndex=triangles[i].textureIndex;
			glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[currentTextureIndex]);
		}

		glBegin(GL_TRIANGLES);
				glTexCoord2f(triangles[i].v1, triangles[i].u1); glVertex3f( vertices[triangles[i].p1].x, vertices[triangles[i].p1].y, vertices[triangles[i].p1].z);
				glTexCoord2f(triangles[i].v2, triangles[i].u2); glVertex3f( vertices[triangles[i].p2].x, vertices[triangles[i].p2].y, vertices[triangles[i].p2].z);
				glTexCoord2f(triangles[i].v3, triangles[i].u3); glVertex3f( vertices[triangles[i].p3].x, vertices[triangles[i].p3].y, vertices[triangles[i].p3].z);
		glEnd();
	}
}