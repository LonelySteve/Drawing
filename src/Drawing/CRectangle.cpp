#include "stdafx.h"
#include "util.h"
#include "CRectangle.h"

IMPLEMENT_SERIAL(CRectangle, CObject, 1)

PREF_WH_SHAPE_PROPERTOR(CRectangle)

#pragma region 构造函数
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CRectangle, RECTANGLE, width(200), height(100))
SHAPE_CLASS_COPY_CONSTRUCTOR(CRectangle, &width, NULL, &height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CRectangle, int width, int height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(RECTANGLE, width(width), height(height))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CRectangle, int width, int height)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(RECTANGLE, width(width), height(height))
#pragma endregion

bool CRectangle::IsMatched(CPoint pnt)
{
	// X 轴方向的绝对偏移量计算
	long abs_offsetX = abs(pnt.x - OrgX);
	// Y 轴方向的绝对偏移量计算
	long abs_offsetY = abs(pnt.y - OrgY);

	double half_of_width = width / 2.0;
	double half_of_height = height / 2.0;

	return abs_offsetX <= half_of_width && abs_offsetY <= half_of_height;
}

void CRectangle::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << width;
		ar << height;
	}
	else
	{
		ar >> width;
		ar >> height;
	}
	CShape::Serialize(ar);
}

void CRectangle::ToDraw(CDC *pDC)
{
	pDC->Rectangle(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
