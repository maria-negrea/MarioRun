#include "Foot.h"

Foot::Foot(void)
{
	vector<Point3D> base;
	vector<Point3D> top;
	for(double t=0.0; t<2*PI; t+=0.785)
	{
		base.push_back(Point3D(0.8*cos(t), 0.0,  0.4*sin(t)));
		top.push_back(Point3D(0.6*cos(t), 0.0,  0.2*sin(t)));

	}

	vertices=base;
	for(int i=0;i<top.size();i++)
	{
		vertices.push_back(top(i));
	}
	
	int m=vertices.size()/2;
	for(int i=0;i<m-1;i++)
	{
		triangles.push_back({i, m+1, m+i+1});
		triangles.push_back({i, m+i+1, i+1});
	}

	triangles.push_back({m-1, 2*m, m});
	triangles.push_back({m-1, m, 0});

	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[0]);

}

void Foot:: Update()
{
}

Foot::~Foot(void)
{
}
