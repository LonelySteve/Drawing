#include "stdafx.h"
#include "util.h"
#include "CTriangle.h"

IMPLEMENT_SERIAL(CTriangle, CObject, 1)

CTriangle::CTriangle() :CShape(TRIANGLE, 0, 0), width(100)
{
}

CTriangle::CTriangle(const CTriangle & triangle) : CShape(triangle)
{
	triangle.GetShapeValue(&Type, &OrgX, &OrgY, &width, NULL, NULL); 
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
	// 这其实就是个线性规划问题...
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

void CTriangle::SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height)
{
	CShape::SetShapeValue(orgX, orgY, widthEtc, text, height);
	this->width = widthEtc;
}
void CTriangle::GetShapeValue(ElementType * type, int * orgX, int * orgY, int * widthEtc, CString * text, int * height) const
{
	CShape::GetShapeValue(type, orgX, orgY, widthEtc, text, height);
	PTR_ASSIGN(widthEtc, this->width);
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
