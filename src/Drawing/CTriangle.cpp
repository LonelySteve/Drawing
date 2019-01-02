#include "stdafx.h"
#include "util.h"
#include "CTriangle.h"

IMPLEMENT_SERIAL(CTriangle, CObject, 1)

CTriangle::CTriangle() :CShape(TRIANGLE, 0, 0), width(100)
{
}

CTriangle::CTriangle(const CTriangle & triangle) : CShape(triangle)
{
	triangle.GetShapeValue(NULL, NULL, NULL, &width);
}

CTriangle::CTriangle(int orgX, int orgY, int width)
	: CShape(TRIANGLE, orgX, orgY), width(width)
{
}

CTriangle::CTriangle(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(TRIANGLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(width)
{
}

bool CTriangle::IsMatched(CPoint pnt)
{
	// ����ʵ���Ǹ����Թ滮����...
	double sqrt_3 = sqrt(3);

	double b1 = OrgY - width / sqrt_3 + OrgX * sqrt_3;
	double b2 = OrgY - OrgX * sqrt_3 - sqrt_3 * width / 3;

	return pnt.y >= -sqrt_3 * pnt.x + b1
		&& pnt.y >= sqrt_3 * pnt.x + b2
		&& pnt.y <= OrgY + sqrt_3 * width / 6;

}

void CTriangle::Serialize(CArchive & ar)
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
void CTriangle::SetShapeValue(ElementType type, int orgX, int orgY, int width)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->width = width;
}
void CTriangle::GetShapeValue(ElementType * type, int * orgX, int * orgY, int * width) const
{
	CShape::GetShapeValue(type, orgX, orgY);
	PTR_ASSIGN(width, this->width);
}
void CTriangle::ToDraw(CDC * pDC)
{
	POINT ps[3]{
		POINT{OrgX - width / 2, long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX + width / 2,long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX,long(OrgY - width / sqrt(3))}
	};

	pDC->Polygon(ps, 3);
}
