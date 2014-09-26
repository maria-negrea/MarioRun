#include "Score.h"

Score::Score(void)
{
}

Score::~Score(void)
{
}

void Score::DrawObject()
{	
	int aux = GlobalScore::GetInstance()->GetScore();
	float pos = -2;

	glBindTexture(GL_TEXTURE_2D, Textures::GetInstance()->GetTextures()[12]);

	do
	{
		int curNr = aux % 10;

		glBegin(GL_QUADS);
			glTexCoord2f(0.1 * (curNr + 1), 1); glVertex3f(pos, 0, 0);
			glTexCoord2f(0.1 * curNr, 1); glVertex3f(pos + 0.5, 0, 0);
			glTexCoord2f(0.1 * curNr, 0); glVertex3f(pos + 0.5, -0.5, 0);
			glTexCoord2f(0.1 * (curNr + 1), 0); glVertex3f(pos, -0.5, 0);
		glEnd();

		pos += 0.5;

		aux /= 10;
	}
	while(aux != 0);
}

void Score::Update()
{
	this->translate = scene->GetCamera()->GetTranslate() + scene->GetCamera()->GetForward() * 5 + Point3D(0, 2.5, 0) + scene->GetCamera()->GetRight() * 3;
	this->rotate = scene->GetCamera()->GetRotate();

	/*if(GlobalScore::GetInstance()->GetScore()>1000)
	{
		this->isWinter=true;
	}*/
}
