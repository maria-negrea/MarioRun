#include "BoneBind.h"

BoneBind::BoneBind(WorldObject* bone,vector<int> points,Point3D bindTranslate,Point3D bindRotate)
	:bone(bone),bindTranslate(bindTranslate),bindRotate(bindRotate)
{
	for(int i=0;i<points.size();i++)
	{
		bool ok = true;
		for(int j=i+1;j<points.size();j++)
		{
			if(points[i] == points[j])
			{
				ok = false;
				break;
			}
		}
		if(ok)
		{
			this->points.push_back(points[i]);
		}
	}
}

BoneBind::~BoneBind(void)
{
}

void BoneBind::ModifyPoints(Point3D* allPoints,Point3D* originPoints)
{
	for(int i=0;i<points.size();i++)
	{
		Point3D rotate = GetRotate();
		allPoints[points[i]] = originPoints[points[i]];
		allPoints[points[i]] = (allPoints[points[i]]-bindTranslate).RotateZ(rotate.z).RotateX(rotate.x).RotateY(rotate.y)+bindTranslate;
		allPoints[points[i]] += GetTranslate();
	}
}

Point3D BoneBind::GetTranslate()
{
	return bone->GetFullTranslate()-bindTranslate;
}

Point3D BoneBind::GetRotate()
{
	return bone->GetFullRotate()-bindRotate;
}