#include "stdafx.h"
#include "util.h"
#include "CTriangle.h"

IMPLEMENT_SERIAL(CTriangle, CObject, 1)

PREF_W_SHAPE_PROPERTOR(CTriangle, width)

SHAPE_CLONE(CTriangle)

#pragma region 构造函数
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CTriangle, TRIANGLE, width(100))
SHAPE_CLASS_COPY_CONSTRUCTOR(CTriangle, &width, NULL, NULL)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CTriangle, SHAPE_PROPERTY_WIDTH)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(TRIANGLE, width(width))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CTriangle, SHAPE_PROPERTY_WIDTH)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(TRIANGLE, width(width))
#pragma endregion

bool CTriangle::IsMatched(CPoint pnt)
{
	// 这其实就是个线性规划问题...
	double sqrt_3 = sqrt(3);

	double b1 = OrgY - width / sqrt_3 + OrgX * sqrt_3;
	double b2 = OrgY - OrgX * sqrt_3 - sqrt_3 * width / 3;

	return pnt.y >= -sqrt_3 * pnt.x + b1 && pnt.y >= sqrt_3 * pnt.x + b2 && pnt.y <= OrgY + sqrt_3 * width / 6;
}

void CTriangle::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << width;
	}
	else
	{
		ar >> width;
	}
	CShape::Serialize(ar);
}

void CTriangle::ToDraw(CDC *pDC)
{
	POINT ps[3]{
		POINT{OrgX - width / 2, long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX + width / 2, long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX, long(OrgY - width / sqrt(3))}};

	pDC->Polygon(ps, 3);
}
