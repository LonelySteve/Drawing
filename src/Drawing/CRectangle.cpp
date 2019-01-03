#include "stdafx.h"
#include "util.h"
#include "CRectangle.h"

IMPLEMENT_SERIAL(CRectangle, CObject, 1)

CRectangle::CRectangle()
	: CShape(RECTANGLE, 0, 0), width(200), height(100)
{
}

CRectangle::CRectangle(const CRectangle & rectangle) : CShape(rectangle)
{
	rectangle.GetShapeValue(&Type, &OrgX, &OrgY, &width, NULL, &height);
}

CRectangle::CRectangle(int orgX, int orgY, int width, int height)
	: CShape(RECTANGLE, orgX, orgY), width(width), height(height)
{
}

CRectangle::CRectangle(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(RECTANGLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(width), height(height)
{
}

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

void CRectangle::Serialize(CArchive & ar)
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
void CRectangle::SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height)
{
	CShape::SetShapeValue(orgX, orgY, widthEtc, text, height);
	this->width = widthEtc;
	this->height = height;
}
void CRectangle::GetShapeValue(ElementType * type, int * orgX, int * orgY, int * widthEtc, CString * text, int * height) const
{
	CShape::GetShapeValue(type, orgX, orgY, widthEtc, text, height);
	PTR_ASSIGN(widthEtc, this->width);
	PTR_ASSIGN(height, this->height);
}

void CRectangle::ToDraw(CDC * pDC)
{
	pDC->Rectangle(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
