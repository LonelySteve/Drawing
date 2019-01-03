#include "stdafx.h"
#include "util.h"
#include "CCircle.h"

IMPLEMENT_SERIAL(CCircle, CObject, 1)

PREF_W_SHAPE_PROPERTOR(CCircle, radius)

#pragma region 构造函数
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CCircle, CIRCLE, radius(100))
SHAPE_CLASS_COPY_CONSTRUCTOR(CCircle, &radius, NULL, NULL)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CCircle, int radius)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(CIRCLE, radius(radius))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CCircle, int radius)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(CIRCLE, radius(radius))
#pragma endregion

bool CCircle::IsMatched(CPoint pnt)
{
	// 计算点到原点的距离
	double dist = sqrt(pow(pnt.x - OrgX, 2) + pow(pnt.y - OrgY, 2));
	return dist <= radius;
}

void CCircle::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << radius;
	}
	else
	{
		ar >> radius;
	}
	CShape::Serialize(ar);
}

void CCircle::ToDraw(CDC *pDC)
{
	pDC->Ellipse(OrgX - radius, OrgY - radius, OrgX + radius, OrgY + radius);
}
