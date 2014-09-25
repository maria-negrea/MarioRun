#include "SnowManHead.h"

SnowManHead::SnowManHead(GLfloat radius)
{
	this->radius=radius;
	quadratic=gluNewQuadric();					
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	GLfloat c=1;

	verticesCount=13;
	trianglesCount=16;
	vertices=new Point3D[verticesCount];

	vertices=new Point3D[verticesCount];
	InitializeSnowManSpikes("SnowManSpikes.cpp");
	triangles=new Triangle[trianglesCount];
	
}

void SnowManHead:: InitializeSnowManSpikes(char* fileName)
{
	/*int i=0;
	ifstream file(fileName);
	cout<<"Stem area"<<endl;
	while(!file.eof())
	{
		Point3D point;
		file>>point;
		cout<<point<<endl;
		vertices[i++]=point;
	}
	
	file.close();*/
}

void SnowManHead:: DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[11]);
	
	gluSphere(quadratic,radius,100,50);
}

SnowManHead::~SnowManHead(void)
{
}
