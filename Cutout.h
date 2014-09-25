#pragma once

class Cutout
{
public:
	Cutout();
	~Cutout();
	virtual float GetDepth() = 0;
	virtual void DrawCutout() = 0;

	bool operator<(Cutout& a);
};