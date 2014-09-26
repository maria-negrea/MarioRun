#pragma once
#include "Mesh.h"
#include<fstream>
#include "Indexable.h"
#include "Updatable.h"

class Tree: public Mesh, public Indexable
{
	int textureIndex;
public:
	Tree(void);
	void InitializeStemVertices(char* fileName, int i);
	void InitializeStemTriangles(int i, int j);
	void Update();
	~Tree(void);
};
