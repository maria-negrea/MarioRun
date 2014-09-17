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

Mesh::Mesh( Point3D* vertices, Triangle* triangles, int verticesCount,int trianglesCount)
	:vertices(vertices),triangles(triangles),verticesCount(verticesCount),trianglesCount(trianglesCount)
{
}

