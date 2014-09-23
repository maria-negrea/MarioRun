#include "Coin.h"

Coin::Coin(void)
{
	length = 0.1;
	width = 0.5;
	height = 0.5;
}

Coin::~Coin(void)
{
}

void Coin::DrawObject()
{
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[6]);

	vector<Point3D> coin;
	for(double t = 0; t <= 2 * 3.14; t += 0.6)
		coin.push_back(Point3D(0.25 * cos(t), 0.25 * sin(t), -0.05));

	coin.push_back(Point3D(0.25 * cos(0.), 0.25 * sin(0.), -0.05));

	for(int i = 0; i < coin.size() - 1; i++)
	{
		glBegin(GL_QUADS);
			glVertex3f(coin[i].x, coin[i].y, coin[i].z);
			glVertex3f(coin[i + 1].x, coin[i + 1].y, coin[i + 1].z);
			glVertex3f(coin[i + 1].x, coin[i + 1].y, coin[i + 1].z + 0.1);
			glVertex3f(coin[i].x, coin[i].y, coin[i].z + 0.1);

			glTexCoord2f(0.5 + 1.6 * coin[i].x, 0.5 + 1.6 * coin[i].y);	glVertex3f(coin[i].x, coin[i].y, coin[i].z);
			glTexCoord2f(0.5 + 1.6 * coin[i + 1].x, 0.5 + 1.6 * coin[i+1].y); glVertex3f(coin[i + 1].x, coin[i + 1].y, coin[i + 1].z);
			glTexCoord2f(0.5, 0.5); glVertex3f(0, 0, coin[i].z);
			glTexCoord2f(0.5, 0.5); glVertex3f(0, 0, coin[i].z);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.5 + 1.6 * coin[i].x, 0.5 + 1.6 * coin[i].y);	glVertex3f(coin[i].x, coin[i].y, coin[i].z + 0.1);
			glTexCoord2f(0.5 + 1.6 * coin[i + 1].x, 0.5 + 1.6 * coin[i+1].y); glVertex3f(coin[i + 1].x, coin[i + 1].y, coin[i + 1].z + 0.1);
			glTexCoord2f(0.5, 0.5); glVertex3f(0, 0, coin[i].z + 0.1);
		glEnd();
	}
}

void Coin::Update() {
	Rotate(Point3D(0.0, 10.0, 0.0));
}

void Coin::Function(Mario *mario)
{
	scene->RemoveObject(this);
	GlobalScore::GetInstance()->UpdateScore(200);
}
