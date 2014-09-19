#pragma once
#include "Mesh.h"
#include<fstream>

class Tree: public Mesh
{
public:
	Tree(void);
	void InitializeStemVertices(char* fileName, int i);
	void InitializeStemTriangles(int i, int j);
	~Tree(void);
};
