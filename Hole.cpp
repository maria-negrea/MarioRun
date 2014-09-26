#include "Hole.h"

Hole::Hole(Mario* mario, Point3D p1, Point3D p2, Point3D p3, Point3D p4)
{
	this->mario=mario;
	this->p1=p1;
	this->p2=p2;
	this->p3=p3;
	this->p4=p4;
	this->textureIndex=19;
}

void Hole:: DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[textureIndex]);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0, 1); glVertex3f( p2.x, p2.y+0.5, p2.z);
		glTexCoord2f(0, 0); glVertex3f( p1.x, p1.y+0.5, p1.z);
		glTexCoord2f(1, 0); glVertex3f( p4.x, p4.y+0.5, p4.z);
		glTexCoord2f(0, 1); glVertex3f( p2.x, p2.y+0.5, p2.z);
		glTexCoord2f(1, 0); glVertex3f( p4.x, p4.y+0.5, p4.z);
		glTexCoord2f(1, 1); glVertex3f( p3.x, p3.y+0.5, p3.z);

	glEnd();
}

bool Hole:: CheckInPoly(Point3D p3D1,Point3D p3D2,Point3D p3D3,Point3D p3D4,Point3D check3D, View perspective)
{
	 Point2D p1 = Point2D(p3D1,perspective);
	 Point2D p2 = Point2D(p3D2,perspective);
	 Point2D p3 = Point2D(p3D3,perspective);
	 Point2D p4 = Point2D(p3D4,perspective);

	 Point2D check = Point2D(check3D,perspective);

	 Segment2D *polySegments = new Segment2D[4];
	 polySegments[0] = Segment2D(p1,p2);
	 polySegments[1] = Segment2D(p2,p3);
	 polySegments[2] = Segment2D(p3,p4);
	 polySegments[3] = Segment2D(p4,p1);

	 Segment2D *lines = new Segment2D[4];
	 lines[0] = Segment2D(check,p1);
	 lines[1] = Segment2D(check,p2);
	 lines[2] = Segment2D(check,p3);
	 lines[3] = Segment2D(check,p4);

	 if(lines[0].Intersects(polySegments[1]))
	 {
	  return false;
	 }
	 if(lines[0].Intersects(polySegments[2]))
	 {
	  return false;
	 }
	 if(lines[1].Intersects(polySegments[2]))
	 {
	  return false;
	 }
	 if(lines[1].Intersects(polySegments[3]))
	 {
	  return false;
	 }
	 if(lines[2].Intersects(polySegments[3]))
	 {
	  return false;
	 }
	 if(lines[2].Intersects(polySegments[0]))
	 {
	  return false;
	 }
	 if(lines[3].Intersects(polySegments[0]))
	 {
	  return false;
	 }
	 if(lines[3].Intersects(polySegments[1]))
	 {
	  return false;
	 }
	 return true;
}

void Hole:: Update()
{
	if(mario->GetTranslate().y==0 && CheckInPoly(p1, p2, p3, p4, mario->GetTranslate(), View::Up))
	{
		mario->SetDrown();
		mario->SetDead();
	}
}

Hole::~Hole(void)
{
}
