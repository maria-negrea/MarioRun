#include "CutoutObject.h"

CutoutObject::CutoutObject(void)
{
}

CutoutObject::~CutoutObject(void)
{
}

float CutoutObject::GetDepth()
{
	//return -translate.y;
	return (scene->GetCamera()->GetTranslate()-translate).Magnitude();
}

void CutoutObject::DrawCutout()
{
	Draw();
}
