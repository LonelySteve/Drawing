#include "stdafx.h"
#include "CShape.h"



IMPLEMENT_SERIAL(CSquare, CObject, 1)


#pragma region CShape
CShape::CShape(ElementType type, int orgX, int orgY)
	:Type(type), OrgX(orgX), OrgY(orgY)
{
}
CShape::CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: Type(type), OrgX(orgX), OrgY(orgY), FillColor(fillColor), FillType(fillType), BorderColor(borderColor), BorderType(borderType), BorderWidth(borderWidth)
{
}

#pragma endregion


#pragma region 子类
#pragma region CSquare
CSquare::CSquare()
	: CShape(SQUARE, 0, 0), width(0)
{

}

CSquare::CSquare(int orgX, int orgY, int width)
	: CShape(SQUARE, orgX, orgY), width(width)
{
}

CSquare::CSquare(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(SQUARE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(width)
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
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
	}
}

#pragma endregion

#pragma region CCircle
CCircle::CCircle()
	:CShape(CIRCLE, 0, 0), radius(0)
{
}

CCircle::CCircle(int orgX, int orgY, int radius)
	: CShape(CIRCLE, orgX, orgY), radius(radius)
{
}

CCircle::CCircle(int orgX, int orgY, int radius, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(CIRCLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), radius(radius)
{
}

void CCircle::Draw(CDC * pDC)
{
}

bool CCircle::IsMatched(CPoint pnt)
{
	return false;
}

void CCircle::Serialize(CArchive & ar)
{
}

#pragma endregion

#pragma region CRectangle

CRectangle::CRectangle()
	: CShape(RECTANGLE, 0, 0), width(0), height(0)
{
}

CRectangle::CRectangle(int orgX, int orgY, int width, int height)
	: CShape(RECTANGLE, orgX, orgY), width(0), height(0)
{
}

CRectangle::CRectangle(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(RECTANGLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(0), height(0)
{
}

void CRectangle::Draw(CDC * pDC)
{
}

bool CRectangle::IsMatched(CPoint pnt)
{
	return false;
}

void CRectangle::Serialize(CArchive & ar)
{
}
#pragma endregion

#pragma region CTriangle

CTriangle::CTriangle() :CShape(TRIANGLE, 0, 0, 0, 0, 0, 0, 0)
{
}

CTriangle::CTriangle(int orgX, int orgY, int width)
	: CShape(TRIANGLE, orgX, orgY), width(0)
{
}

CTriangle::CTriangle(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(TRIANGLE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(width)
{
}

void CTriangle::Draw(CDC * pDC)
{
}

bool CTriangle::IsMatched(CPoint pnt)
{
	return false;
}

void CTriangle::Serialize(CArchive & ar)
{
}
#pragma endregion

#pragma region CText
CText::CText()
	: CShape(TEXT, 0, 0), text("String 字符串 123"), height(0), angle(0)
{
}

CText::CText(int orgX, int orgY, CString text, int height, int angle)
	: CShape(TEXT, orgX, orgY), text(text), height(height), angle(angle)
{
}

CText::CText(int orgX, int orgY, CString text, int height, int angle, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(TEXT, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), text(text), height(height), angle(angle)
{
}

void CText::Draw(CDC * pDC)
{
}

bool CText::IsMatched(CPoint pnt)
{
	return false;
}

void CText::Serialize(CArchive & ar)
{
}

#pragma endregion

#pragma region CEllipse
CEllipse::CEllipse()
	: CShape(ELLIPSE, 0, 0), width(0), height(0)
{
}

CEllipse::CEllipse(int orgX, int orgY, int width, int height)
	: CShape(ELLIPSE, orgX, orgY), width(0), height(0)
{
}

CEllipse::CEllipse(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: CShape(ELLIPSE, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType), width(0), height(0)
{
}

void CEllipse::Draw(CDC * pDC)
{
}

bool CEllipse::IsMatched(CPoint pnt)
{
	return false;
}

void CEllipse::Serialize(CArchive & ar)
{
}
#pragma endregion

#pragma endregion