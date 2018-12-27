#include "stdafx.h"
#include "CShape.h"
#include <math.h>


IMPLEMENT_SERIAL(CSquare, CObject, 1)
IMPLEMENT_SERIAL(CCircle, CObject, 1)
IMPLEMENT_SERIAL(CRectangle, CObject, 1)
IMPLEMENT_SERIAL(CTriangle, CObject, 1)
IMPLEMENT_SERIAL(CText, CObject, 1)
IMPLEMENT_SERIAL(CEllipse, CObject, 1)

#pragma region CShape
CShape::CShape(ElementType type, int orgX, int orgY)
	:Type(type), OrgX(orgX), OrgY(orgY)
{
}
CShape::CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: Type(type), OrgX(orgX), OrgY(orgY), FillColor(fillColor), FillType(fillType), BorderColor(borderColor), BorderType(borderType), BorderWidth(borderWidth)
{
}

void CShape::Draw(CDC * pDC)
{
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = pDC->SelectObject(&pen);
	CBrush brush, *pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = pDC->SelectObject(&brush);
	// ���þ���Ļ��ƺ���
	ToDraw(pDC);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CShape::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;   // ͼԪ����
		ar << OrgX << OrgY; // ԭ������
		ar << BorderColor;  // �߽���ɫ
		ar << BorderType;   // �߿�����
		ar << BorderWidth;  // �߽���
		ar << FillColor;    // �����ɫ
		ar << FillType;     // �������
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;
		ar >> BorderColor;
		ar >> BorderType;
		ar >> BorderWidth;
		ar >> FillColor;
		ar >> FillType;
	}
}

#pragma endregion


#pragma region ����
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

bool CSquare::IsMatched(CPoint pnt)
{
	return false;
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

bool CCircle::IsMatched(CPoint pnt)
{
	return false;
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

void CCircle::ToDraw(CDC * pDC)
{
	pDC->Ellipse(OrgX - radius, OrgY - radius, OrgX + radius, OrgY + radius);
}

#pragma endregion

#pragma region CRectangle

CRectangle::CRectangle()
	: CShape(RECTANGLE, 0, 0), width(0), height(0)
{
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
	return false;
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
void CRectangle::ToDraw(CDC * pDC)
{
	pDC->Rectangle(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
#pragma endregion

#pragma region CTriangle

CTriangle::CTriangle() :CShape(TRIANGLE, 0, 0, 0, 0, 0, 0, 0)
{
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
	return false;
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
void CTriangle::ToDraw(CDC * pDC)
{
	POINT ps[3]{
		POINT{OrgX - width / 2, long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX + width / 2,long(OrgY + width / (2 * sqrt(3)))},
		POINT{OrgX,long(OrgY - width / sqrt(3))}
	};

	pDC->Polygon(ps, 3);
}
#pragma endregion

#pragma region CText
CText::CText()
	: CShape(TEXT, 0, 0), text("String �ַ��� 123"), height(0), angle(0)
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

bool CText::IsMatched(CPoint pnt)
{
	return false;
}

void CText::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << text;
		ar << height;
		ar << angle;
	}
	else
	{
		ar >> text;
		ar >> height;
		ar >> angle;
	}
	CShape::Serialize(ar);
}

void CText::ToDraw(CDC * pDC)
{
	CFont *OldFont, *F = new CFont;
	F->CreateFontW(
		height,
		0,
		angle * 10,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		GB2312_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("΢���ź�"));
	OldFont = pDC->SelectObject(F);
	pDC->TextOutW(OrgX, OrgY, text);
	pDC->SelectObject(OldFont);
	delete F;
}

#pragma endregion

#pragma region CEllipse
CEllipse::CEllipse()
	: CShape(ELLIPSE, 0, 0), width(0), height(0)
{
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
	return false;
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
#pragma endregion

#pragma endregion