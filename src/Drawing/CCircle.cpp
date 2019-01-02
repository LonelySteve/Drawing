#include "stdafx.h"
#include "util.h"
#include "CCircle.h"

IMPLEMENT_SERIAL(CCircle, CObject, 1)

CCircle::CCircle()
	:CShape(CIRCLE, 0, 0), radius(100)
{
}

CCircle::CCircle(const CCircle & circle) : CShape(circle)
{
	circle.GetShapeValue(NULL, NULL, NULL, &radius);
}

CCircle::CCircle(int orgX, int orgY, int radius)
	: CShape(CIRCLE, orgX, orgY), radius(radius)
{
}

CCircle::CCircle(int orgX, int orgY, int radius, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(CIRCLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), radius(radius)
{
}

bool CCircle::IsMatched(CPoint pnt)
{
	// 计算点到原点的距离
	double dist = sqrt(pow(pnt.x - OrgX, 2) + pow(pnt.y - OrgY, 2));
	return dist <= radius;
}

void CCircle::Serialize(CArchive & ar)
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

void CCircle::SetShapeValue(ElementType type, int orgX, int orgY, int radius)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->radius = radius;
}

void CCircle::GetShapeValue(ElementType * type, int * orgX, int * orgY, int * radius) const
{
	CShape::GetShapeValue(type, orgX, orgY);
	PTR_ASSIGN(radius, this->radius);
}

void CCircle::ToDraw(CDC * pDC)
{
	pDC->Ellipse(OrgX - radius, OrgY - radius, OrgX + radius, OrgY + radius);
}
