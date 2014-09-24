#include "Star.h"

Star::Star(GLfloat width, GLfloat height, GLfloat length)
{
	this->length = length;
	this->width = width;
	this->height = height;
	this->speed = 2;
	
	fallSpeed=1;

	road = NULL;
}

Star::~Star(void)
{
}

void Star::DrawObject()
{
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[13]);

	for(double i = -0.05; i <= 0.05; i += 0.1)
	{
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.5, 0.876);glVertex3f(0, 0.876, 0);
			glTexCoord2f(0.632, 0.643);glVertex3f(0.132, 0.643, i);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.632, 0.643);glVertex3f(0.132, 0.643, i);
			glTexCoord2f(0.893, 0.589);glVertex3f(0.393, 0.589, 0);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.893, 0.589);glVertex3f(0.393, 0.589, 0);
			glTexCoord2f(0.712, 0.39);glVertex3f(0.212, 0.39, i);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.712, 0.39);glVertex3f(0.212, 0.39, i);
			glTexCoord2f(0.742, 0.13);glVertex3f(0.242, 0.13, 0);

			glTexCoord2f(0.742, 0.13);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.742, 0.13);glVertex3f(0.242, 0.13, 0);
			glTexCoord2f(0.5, 0.238);glVertex3f(0, 0.238, i);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.5, 0.238);glVertex3f(0, 0.238, i);
			glTexCoord2f(0.256, 0.127);glVertex3f(-0.244, 0.127, 0);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.256, 0.127);glVertex3f(-0.244, 0.127, 0);
			glTexCoord2f(0.286, 0.395);glVertex3f(-0.214, 0.395, i);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.286, 0.395);glVertex3f(-0.214, 0.395, i);
			glTexCoord2f(0.105, 0.588);glVertex3f(-0.395, 0.588, 0);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.105, 0.588);glVertex3f(-0.395, 0.588, 0);
			glTexCoord2f(0.368, 0.648);glVertex3f(-0.132, 0.648, i);

			glTexCoord2f(0.5, 0.557);glVertex3f(0, 0.557, i);
			glTexCoord2f(0.368, 0.648);glVertex3f(-0.132, 0.648, i);
			glTexCoord2f(0.5, 0.876);glVertex3f(0, 0.876, 0);
		glEnd();
	}
	
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.876, 0);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.132, 0.643, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.132, 0.643, 0.05);

		glTexCoord2f(0.5, 0.6);glVertex3f(0.132, 0.643, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.132, 0.643, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.393, 0.589, 0);

		glTexCoord2f(0.5, 0.6);glVertex3f(0.393, 0.589, 0);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.212, 0.39, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.212, 0.39, -0.05);

		glTexCoord2f(0.5, 0.6);glVertex3f(0.212, 0.39, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.212, 0.39, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0.242, 0.13, 0);

		glTexCoord2f(0.5, 0.6);glVertex3f(0.242, 0.13, 0);
		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.238, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.238, -0.05);

		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.238, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.238, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.244, 0.127, 0);

		glTexCoord2f(0.5, 0.6);glVertex3f(-0.244, 0.127, 0);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.214, 0.395, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.214, 0.395, -0.05);

		glTexCoord2f(0.5, 0.6);glVertex3f(-0.214, 0.395, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.214, 0.395, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.395, 0.588, 0);

		glTexCoord2f(0.5, 0.6);glVertex3f(-0.395, 0.588, 0);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.132, 0.648, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.132, 0.648, -0.05);

		glTexCoord2f(0.5, 0.6);glVertex3f(-0.132, 0.648, 0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(-0.132, 0.648, -0.05);
		glTexCoord2f(0.5, 0.6);glVertex3f(0, 0.876, 0);
	glEnd();
}

void Star::Update()
{
	PhysicsObject::Update();
	this->Translate(GetForward()*speed);
	if(speed > 0.3)
		this->speed -= 0.01;
}

void Star::Function(Mario *mario)
{
	scene->RemoveObject(this);
	mario->SetInvulnerable();
	GlobalScore::GetInstance()->UpdateScore(300);
}

void Star::Translate(Point3D translation)
{
	WorldObject::Translate(translation);
	if(road != NULL)
	{
		road->OffRoad(this);
	}
}