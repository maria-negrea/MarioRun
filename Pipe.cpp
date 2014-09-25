#include "Pipe.h"

Pipe::Pipe(GLfloat width, GLfloat height, GLfloat length)
{
	this->width=width;
	this->height=height;
	this->length=length;
	plant=new PlantTulip(1,1,1);
	plant->Scale(Point3D(2, 2, 2));
	plant->Translate(Point3D(0, height, 0));
	AddChild(plant);
}

void Pipe:: SetTarget(WorldObject* target)
{
	plant->SetTarget(target);
}


Pipe::~Pipe(void)
{
}

void Pipe::DrawObject()
{
	vector<Point3D> pipe;

	for(double t = 0; t <= 2 * 3.14; t+= 0.1)
		pipe.push_back(Point3D(width/2 * cos(t), 0, length/2 * sin(t)));

	pipe.push_back(Point3D(width/2 * cos(0.), 0, length/2 * sin(0.)));

	double pas = 1./pipe.size();
	double j = 0;

	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[23]);

	for(int i = 0; i < pipe.size() - 1; i++)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(j, 1);glVertex3f(pipe[i].x, pipe[i].y, pipe[i].z);
			glTexCoord2f(j + pas, 1);glVertex3f(pipe[i + 1].x, pipe[i + 1].y, pipe[i + 1].z);
			glTexCoord2f(j + pas, 0);glVertex3f(pipe[i + 1].x, pipe[i + 1].y + 75.0/100*height, pipe[i + 1].z);
			glTexCoord2f(j, 0);glVertex3f(pipe[i].x, pipe[i].y + 75.0/100*height, pipe[i].z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(1.3*pipe[i].x, pipe[i].y + 75.0/100*height, 1.3*pipe[i].z);
			glVertex3f(1.3*pipe[i + 1].x, pipe[i + 1].y + 75.0/100*height, 1.3*pipe[i + 1].z);
			glVertex3f(1.3*pipe[i + 1].x, pipe[i + 1].y + height, 1.3*pipe[i + 1].z);
			glVertex3f(1.3*pipe[i].x, pipe[i].y + height, 1.3*pipe[i].z);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
			glVertex3f(1.3*pipe[i].x, height, 1.3*pipe[i].z);
			glVertex3f(1.3*pipe[i + 1].x, height, 1.3*pipe[i + 1].z);
			glVertex3f(0, height, 0);

			glVertex3f(1.3*pipe[i].x,75.0/100*height, 1.3*pipe[i].z);
			glVertex3f(1.3*pipe[i + 1].x, 75.0/100*height, 1.3*pipe[i + 1].z);
			glVertex3f(0, 75.0/100*height, 0);

			glVertex3f(pipe[i].x, 75.0/100*height, pipe[i].z);
			glVertex3f(pipe[i + 1].x, 75.0/100*height, pipe[i + 1].z);
			glVertex3f(0, 75.0/100*height, 0);
		glEnd();

		j += pas;
	}
}
