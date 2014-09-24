#include "Tree.h"

Tree::Tree(void)
{
	verticesCount=64;
	trianglesCount=(verticesCount-1)*4;
	vertices=new Point3D[verticesCount];
	GLfloat bigRadius=5.0, smallRadius=4.0;

	width=bigRadius*2;
	length=bigRadius*2;
	height=13.0;

	int i=0;
	for(double t=0.0; t<2*PI; t+=0.785)
	{		
		vertices[i]=Point3D(bigRadius*cos(t), 23.07/100*height,  smallRadius*sin(t));
		cout<<vertices[i]<<endl;
		vertices[i+8]=Point3D(60.0/100*bigRadius*cos(t), 46.15/100*height, 60.0/100*smallRadius*sin(t));
		vertices[i+16]=Point3D(80.0/100*bigRadius*cos(t), 46.15/100*height,  80.0/100*smallRadius*sin(t));
		vertices[i+24]=Point3D(40.0/100*bigRadius*cos(t), 69.23/100*height, 40.0/100*smallRadius*sin(t));
		vertices[i+32]=Point3D(60.0/100*bigRadius*cos(t), 69.23/100*height,  60.0/100*smallRadius*sin(t));
		vertices[i+40]=Point3D(5.0/100*bigRadius*cos(t), height,  5.0/100*smallRadius*sin(t));
		i++;
	}

	int index=i+40;
	InitializeStemVertices("TreeStemCoordinates.cpp", index);

	int m=verticesCount/8;
	triangles=new Triangle[trianglesCount];

	int j=0;

	GLfloat stepV=1.0/(verticesCount/8), stepU=1.0/8;
	GLfloat countU=0.0, countV;
	for(i=0;i<m-1;i++)
	{
		countV=0.0;
		triangles[j++]=Triangle(m+i, i, i+1, 9, countV+stepV, countU, countV, countU, countV, countU+stepU);
		triangles[j++]=Triangle(m+i, i+1, m+i+1, 9, countV+stepV, countU, countV, countU+stepU, countV+stepV, countU+stepU);
		countV+=stepV;
		triangles[j++]=Triangle(2*m+i, m+i, m+i+1, 9, countV+stepV, countU, countV, countU, countV, countU+stepU);
		triangles[j++]=Triangle(2*m+i, m+i+1, 2*m+i+1, 9, countV+stepV, countU, countV, countU+stepU, countV+stepV, countU+stepU);
		countV+=stepV;
		triangles[j++]=Triangle(3*m+i, 2*m+i, 2*m+i+1, 9, countV+stepV, countU, countV, countU, countV, countU+stepU);
		triangles[j++]=Triangle(3*m+i, 2*m+i+1, 3*m+i+1, 9, countV+stepV, countU, countV, countU+stepU, countV+stepV, countU+stepU);
		countV+=stepV;
		triangles[j++]=Triangle(4*m+i, 3*m+i, 3*m+i+1, 9, countV+stepV, countU, countV, countU, countV, countU+stepU);
		triangles[j++]=Triangle(4*m+i, 3*m+i+1, 4*m+i+1, 9, countV+stepV, countU, countV, countU+stepU, countV+stepV, countU+stepU);
		countV+=stepV;
		triangles[j++]=Triangle(5*m+i, 4*m+i, 4*m+i+1, 9, countV+stepV, countU, countV, countU, countV, countU+stepU);
		triangles[j++]=Triangle(5*m+i, 4*m+i+1, 5*m+i+1, 9, countV+stepV, countU, countV, countU+stepU, countV+stepV, countU+stepU);
		countU+=stepU;
	}

	i--;
	countV=0.0;

	triangles[j++]=Triangle(m+i+1, i+1, m, 9, countV+stepV, countU, countV, countU, countV+stepV, 1.0);
	triangles[j++]=Triangle(m, i+1, 0, 9, countV+stepV, 1.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(2*m+i+1, m+i+1, 2*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 1.0);
	triangles[j++]=Triangle(2*m, m+i+1, m, 9, countV+stepV, 1.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(3*m+i+1, 2*m+i+1, 3*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 1.0);
	triangles[j++]=Triangle(3*m, 2*m+i+1, 2*m, 9, countV+stepV, 1.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(4*m+i+1, 3*m+i+1, 4*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 1.0);
	triangles[j++]=Triangle(4*m, 3*m+i+1, 3*m, 9, countV+stepV, 1.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(5*m+i+1, 4*m+i+1, 5*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 1.0);
	triangles[j++]=Triangle(5*m, 4*m+i+1, 4*m, 9, countV+stepV, 1.0, countV, countU, countV, 0.0);


	/*triangles[j++]=Triangle(m+i+1, i+1, m, 9, countV+stepV, countU, countV, countU, countV+stepV, 0.0);
	triangles[j++]=Triangle(m, i+1, 0, 9, countV+stepV, 0.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(2*m+i+1, m+i+1, 2*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 0.0);
	triangles[j++]=Triangle(2*m, m+i+1, m, 9, countV+stepV, 0.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(3*m+i+1, 2*m+i+1, 3*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 0.0);
	triangles[j++]=Triangle(3*m, 2*m+i+1, 2*m, 9, countV+stepV, 0.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(4*m+i+1, 3*m+i+1, 4*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 0.0);
	triangles[j++]=Triangle(4*m, 3*m+i+1, 3*m, 9, countV+stepV, 0.0, countV, countU, countV, 0.0);

	countV+=stepV;
	triangles[j++]=Triangle(5*m+i+1, 4*m+i+1, 5*m, 9, countV+stepV, countU, countV, countU, countV+stepV, 0.0);
	triangles[j++]=Triangle(5*m, 4*m+i+1, 4*m, 9, countV+stepV, 0.0, countV, countU, countV, 0.0);*/

	stepV*=2;
	countV=0.0;
	for(i=0;i<m/2;i++)
	{
		triangles[j++]=Triangle(5*m+m-i-1, 5*m+i, 5*m+i+1, 9, 1.0, countV, 0.0, countV, 0.0, countV+stepV);
		triangles[j++]=Triangle(5*m+m-i-1, 5*m+i+1, 5*m+m-i-2, 9, countV, 0.0, 0.0, countV+stepV, 1.0, countV+stepV);

		triangles[j++]=Triangle(m-i-1, i, i+1, 9, 1.0, countV, 0.0, countV, 0.0, countV+stepV);
		triangles[j++]=Triangle(m-i-1, i+1, m-i-2, 9, countV, 0.0, 0.0, countV+stepV, 1.0, countV+stepV);
	}

	InitializeStemTriangles(index, j);

		
}

void Tree:: InitializeStemVertices(char* fileName, int i)
{
	ifstream file(fileName);
	cout<<"Stem area"<<endl;
	while(!file.eof())
	{
		Point3D point;
		file>>point;
		cout<<point<<endl;
		vertices[i++]=point;
	}
	
	file.close();
}

void Tree:: InitializeStemTriangles(int i, int j)
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[6]);
	int m=(verticesCount-i)/2;

	GLfloat stepU=1.0/m, countU=0.0;

	int k;
	for(k=0;k<m-1;k++)
	{
		triangles[j++]=Triangle(m+i+k, i+k, i+k+1, 10, 1.0, countU, 0.0, countU, 0.0, countU+stepU);
		triangles[j++]=Triangle(m+i+k, i+k+1, m+i+k+1, 10, 1.0, countU, 0.0, countU+stepU, 1.0, countU+stepU);
		countU+=stepU;
	}

	triangles[j++]=Triangle(m+i+k, i+k, i, 10, 1.0, countU, 0.0, countU, 0.0, 0.0);
	triangles[j]=Triangle(m+i+k, i, m+i, 10, 1.0, countU, 0.0, 0.0, 1.0, 0.0);

}

Tree::~Tree(void)
{
}
