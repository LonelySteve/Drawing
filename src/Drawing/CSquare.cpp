#include "stdafx.h"
#include "util.h"
#include "CSquare.h"

IMPLEMENT_SERIAL(CSquare, CObject, 1)

PREF_W_SHAPE_PROPERTOR(CSquare, width)

#pragma region 构造函数
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CSquare, SQUARE, width(100))
SHAPE_CLASS_COPY_CONSTRUCTOR(CSquare, &width, NULL, NULL)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CSquare, int width)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(SQUARE, width(width))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CSquare, int width)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(SQUARE, width(width))
#pragma endregion

bool CSquare::IsMatched(CPoint pnt)
{
	// X 轴方向的绝对偏移量计算
	long abs_offsetX = abs(pnt.x - OrgX);
	// Y 轴方向的绝对偏移量计算
	long abs_offsetY = abs(pnt.y - OrgY);

	double half_of_width = width / 2.0;

	return abs_offsetX <= half_of_width && abs_offsetY <= half_of_width;
}

void CSquare::Serialize(CArchive & ar)
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

void CSquare::ToDraw(CDC * pDC)
{
	pDC->Rectangle(OrgX - width / 2, OrgY - width / 2, OrgX + width / 2, OrgY + width / 2);
}
