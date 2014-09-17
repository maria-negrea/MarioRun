#pragma once

class Input
{
	static bool right;
	static bool left;
public:
	Input();
	~Input();
	static void SetRight(bool flag);
	static void SetLeft(bool flag);
	static bool GetRight();
	static bool GetLeft();
};
