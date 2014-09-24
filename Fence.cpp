#include "Fence.h"

Fence::Fence(GLfloat width,GLfloat length,GLfloat height, int size)
{
	this->width=width;
	this->length=length;
	this->height=height;
	this->size=size;
	
    vector<FencePart*> parts;
for(int i=0;i<size;i++)
{
	 FencePart *part=new FencePart(width, height, length);
	 part->Translate(Point3D(width*1.5*i,0,0));
	 part->Rotate(Point3D(270,0,0));
     parts.push_back(part);
}
	for(int i=0;i<size;i++)
	{
	

		this->AddChild(parts.back());
		parts.pop_back();
	
	}


}

Fence::~Fence(void)
{
}

void Fence::DrawObject()
{	

}