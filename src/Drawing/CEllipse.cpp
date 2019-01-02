#include "stdafx.h"
#include "util.h"
#include "CEllipse.h"

IMPLEMENT_SERIAL(CEllipse, CObject, 1)

CEllipse::CEllipse()
	: CShape(ELLIPSE, 0, 0), width(200), height(100)
{
}

CEllipse::CEllipse(const CEllipse & ellipse) : CShape(ellipse)
{
	ellipse.GetShapeValue(NULL, NULL, NULL, &width, &height);
}

CEllipse::CEllipse(int orgX, int orgY, int width, int height)
	: CShape(ELLIPSE, orgX, orgY), width(width), height(height)
{
}

CEllipse::CEllipse(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(ELLIPSE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(width), height(height)
{
}

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
void CEllipse::SetShapeValue(ElementType type, int orgX, int orgY, int width, int height)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->width = width;
	this->height = height;
}
void CEllipse::GetShapeValue(ElementType * type, int * orgX, int * orgY, int * width, int * height) const
{
	CShape::GetShapeValue(type, orgX, orgY);
	PTR_ASSIGN(width, this->width);
	PTR_ASSIGN(height, this->height);
}
void CEllipse::ToDraw(CDC * pDC)
{
	pDC->Ellipse(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
 