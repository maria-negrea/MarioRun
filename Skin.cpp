#include "Skin.h"
#include<fstream>

Skin::Skin(char* file, bool symmetry)
{
	ifstream f(file);

	f>>verticesCount;
	f>>trianglesCount;

	vertices = new Point3D[verticesCount*2];
	triangles = new Triangle[trianglesCount*2];

	for(int i=0 ; i<verticesCount; ++i)
	{
		f>>vertices[i].x>>vertices[i].y>>vertices[i].z;
	}

	if(symmetry)
	{
		for(int i=verticesCount ; i<verticesCount*2; ++i)
		{
			vertices[i] = vertices[i-verticesCount];
			vertices[i].x = -vertices[i].x;
		}

		for(int i=0;i<25;i++)
		{
			triangles[i].textureIndex = 1;
		}

		for(int i=84;i<98;i++)
		{
			triangles[i].textureIndex = 2;
		}
		for(int i=227;i<231;i++)
		{
			triangles[i].textureIndex = 2;
		}

		for(int i=112;i<140;i++)
		{
			triangles[i].textureIndex = 3;//5
		}

		for(int i=140;i<169;i++)
		{
			triangles[i].textureIndex = 5;
		}

		for(int i=169;i<187;i++)
		{
			triangles[i].textureIndex = 4;
		}

		for(int i=187;i<227;i++)
		{
			triangles[i].textureIndex = 3;
		}
		triangles[231].textureIndex = 3;
		triangles[232].textureIndex = 3;
	}

	for(int i=0 ; i<trianglesCount; ++i)
	{
		f>>triangles[i].p1>>triangles[i].p2>>triangles[i].p3;
	}

	if(symmetry)
	{
		for(int i=trianglesCount ; i<trianglesCount*2; ++i)
		{
			triangles[i] = triangles[i-trianglesCount];
			triangles[i].p1 += verticesCount;
			triangles[i].p2 += verticesCount;
			triangles[i].p3 += verticesCount;
		}

		verticesCount *= 2;
		trianglesCount *= 2;
	}

	printVertices = new Point3D[verticesCount];
}

Skin::~Skin(void)
{
}

void Skin::DrawObject()
{
	Point3D* originPoints = new Point3D[verticesCount];
	for(int i=0;i<verticesCount;i++)
	{
		originPoints[i] = vertices[i]+GetFullTranslate();
	}
	for(int i=0;i<verticesCount;i++)
	{
		printVertices[i] = vertices[i]+GetFullTranslate();
	}

	for(int i=0;i<binds.size();i++)
	{
		binds[i].ModifyPoints(printVertices,originPoints);
	}

	for(int i=0;i<verticesCount;i++)
	{
		printVertices[i] = printVertices[i]-GetFullTranslate();//.RotateZ(rotate.z).RotateX(rotate.x).RotateY(rotate.y);
	}

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
				glTexCoord2f(triangles[i].v1, triangles[i].u1); glVertex3f( printVertices[triangles[i].p1].x, printVertices[triangles[i].p1].y, printVertices[triangles[i].p1].z);
				glTexCoord2f(triangles[i].v2, triangles[i].u2); glVertex3f( printVertices[triangles[i].p2].x, printVertices[triangles[i].p2].y, printVertices[triangles[i].p2].z);
				glTexCoord2f(triangles[i].v3, triangles[i].u3); glVertex3f( printVertices[triangles[i].p3].x, printVertices[triangles[i].p3].y, printVertices[triangles[i].p3].z);
		glEnd();
	}
	delete originPoints;
}

void Skin::AddBind(WorldObject* bone, vector<int> points)
{
	binds.push_back(BoneBind(bone,points,bone->GetFullTranslate(),bone->GetFullRotate()));
}