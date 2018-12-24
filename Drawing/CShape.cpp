#include "stdafx.h"
#include "CShape.h"
 

CSquare::CSquare(int orgX, int orgY, int width):CShape(SQUARE,orgX,orgY,RGB(0,0,0), PS_SOLID, 0 ,RGB(0,0,0), 6), width(width)
{

}

CSquare::CSquare(int orgX, int orgY, int width, COLORREF borderColor, int borderType, int borderWidth, COLORREF fillColor, int fillType)
	: CShape(SQUARE, orgX, orgY, borderColor, borderType, borderWidth,fillColor,fillType), width(width)
{
}

CSquare::~CSquare()
{
}

void CSquare::Draw(CDC * pDC)
{
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush, *pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	pDC->Rectangle(OrgX - width / 2, OrgY - width / 2, OrgX + width / 2, OrgY + width / 2);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

}

bool CSquare::IsMatched(CPoint pnt)
{
	return false;
}

void CSquare::Serialize(CArchive & ar)
{
}


CShape::CShape(ElementType type , int orgX, int orgY, COLORREF borderColor, int borderType, int borderWidth, COLORREF fillColor, int fillType)
	:Type(type),OrgX(orgX),OrgY(orgY),BorderColor(borderColor),BorderType(borderType),BorderWidth(borderWidth),FillColor(fillColor),FillType(fillType)
{
}

CShape::~CShape()
{
}
