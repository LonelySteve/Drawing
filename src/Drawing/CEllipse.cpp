#include "stdafx.h"
#include "util.h"
#include "CEllipse.h"

IMPLEMENT_SERIAL(CEllipse, CObject, 1)

PREF_WH_SHAPE_PROPERTOR(CEllipse)

#pragma region ¹¹Ôìº¯Êý
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CEllipse, ELLIPSE, width(200), height(100))
SHAPE_CLASS_COPY_CONSTRUCTOR(CEllipse, &width, NULL, &height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CEllipse, int width, int height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(ELLIPSE, width(width), height(height))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CEllipse, int width, int height)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(ELLIPSE, width(width), height(height))
#pragma endregion

bool CEllipse::IsMatched(CPoint pnt)
{
	return
		pow(pnt.x - OrgX, 2) / pow(width / 2, 2)
		+
		pow(pnt.y - OrgY, 2) / pow(height / 2, 2)
		<= 1;
}

void CEllipse::Serialize(CArchive & ar)
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

void CEllipse::ToDraw(CDC * pDC)
{
	pDC->Ellipse(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
