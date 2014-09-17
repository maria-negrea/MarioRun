#include "Input.h"

bool Input::left = false;
bool Input::right = false;

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::SetRight(bool flag)
{
	right = flag;
}

void Input::SetLeft(bool flag)
{
	left = flag;
}

bool Input::GetLeft()
{
	return left;
}

bool Input::GetRight()
{
	return right;
}