#include "GlobalScore.h"

GlobalScore::GlobalScore(void)
{
}

GlobalScore::~GlobalScore(void)
{
}

GlobalScore* GlobalScore::instance = NULL;
int GlobalScore::globalScore = 0;

GlobalScore* GlobalScore::GetInstance()
{
	if(instance == NULL)
		instance = new GlobalScore;

	return instance;
}

void GlobalScore::UpdateScore(int score)
{
	globalScore += score;
}

int GlobalScore::GetScore()
{
	return globalScore;
}

void GlobalScore::SetScore(int score)
{
	globalScore = score;
}