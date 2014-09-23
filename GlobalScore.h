#pragma once

#include<iostream>
using namespace std;

class GlobalScore
{
private:
	GlobalScore(void);
	static int globalScore;
	static GlobalScore *instance;
public:
	static GlobalScore *GetInstance();
	~GlobalScore(void);
	static void UpdateScore(int score);
	static int GetScore();
	static void SetScore(int score);
};
