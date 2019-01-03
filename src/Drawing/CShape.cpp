#include "stdafx.h"
#include "CShapes.h"
#include <math.h>
#include "util.h"

CShape *CShape::DynamicCShapeObj(const CShape *shape, bool copy)
{
#define TM_0(className) copy ? new className((className &)*shape) : new className()
	PTR_NULL_RETURN(shape, NULL);
	switch (shape->GetShapeType())
	{
	case SQUARE:
		return TM_0(CSquare);
	case RECTANGLE:
		return TM_0(CRectangle);
	case CIRCLE:
		return TM_0(CCircle);
	case ELLIPSE:
		return TM_0(CEllipse);
	case TRIANGLE:
		return TM_0(CTriangle);
	case TEXT:
		return TM_0(CText);
	}
#undef TM_0
	return NULL;
}

CShape::CShape(const CShape &shape)
{
	shape.GetBrush(&FillColor, &FillType);
	shape.GetPen(&BorderColor, &BorderWidth, &BorderType);
	shape.GetShapeValue(&Type, &OrgX, &OrgY, NULL, NULL, NULL);
}

CShape::CShape(ElementType type, int orgX, int orgY)
	: Type(type), OrgX(orgX), OrgY(orgY)
{
}

CShape::CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
	: Type(type), OrgX(orgX), OrgY(orgY), FillColor(fillColor), FillType(fillType), BorderColor(borderColor), BorderType(borderType), BorderWidth(borderWidth)
{
}

void CShape::SetPen(COLORREF color, int width, int type)
{
	BorderColor = color;
	BorderWidth = width;
	BorderType = type;
}

bool CShape::GetPen(CPen &pen) const
{
	return pen.CreatePen(BorderType, BorderWidth, BorderColor);
}

void CShape::GetPen(COLORREF *color, int *width, int *type) const
{
	PTR_ASSIGN(color, this->BorderColor);
	PTR_ASSIGN(width, this->BorderWidth);
	PTR_ASSIGN(type, this->BorderType);
}

void CShape::SetBrush(COLORREF color, int type)
{
	FillColor = color;
	FillType = type;
}

bool CShape::GetBrush(CBrush &brush) const
{
	return FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS ? brush.CreateHatchBrush(FillType, FillColor) : brush.CreateSolidBrush(FillColor);
}

void CShape::GetBrush(COLORREF *color, int *type) const
{
	PTR_ASSIGN(color, this->FillColor);
	PTR_ASSIGN(type, this->FillType);
}

ElementType CShape::GetShapeType() const
{
	return Type;
}

void CShape::Draw(CDC *pDC)
{
	CPen pen, *pOldPen;
	GetPen(pen);
	pOldPen = pDC->SelectObject(&pen);
	CBrush brush, *pOldBrush;
	GetBrush(brush);
	pOldBrush = pDC->SelectObject(&brush);
	// 调用具体的绘制函数
	ToDraw(pDC);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
#ifdef DEBUG
	// 绘制反色原点
	RECT rect{OrgX - 3, OrgY - 3, OrgX + 3, OrgY + 3};
	pDC->InvertRect(&rect);
#endif // DEBUG
}

void CShape::SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height)
{
	OrgX = orgX;
	OrgY = orgY;
}

void CShape::GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const
{
	PTR_ASSIGN(type, Type);
	PTR_ASSIGN(orgX, OrgX);
	PTR_ASSIGN(orgY, OrgY);
}

void CShape::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;   // 图元类型
		ar << OrgX << OrgY; // 原点坐标
		ar << BorderColor;  // 边界颜色
		ar << BorderType;   // 边框类型
		ar << BorderWidth;  // 边界宽度
		ar << FillColor;	// 填充颜色
		ar << FillType;		// 填充类型
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
