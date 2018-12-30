#include "stdafx.h"
#include "CShape.h"
#include <math.h>
#include "util.h"

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

void CShape::SetPen(COLORREF color, int width, int type)
{
	BorderColor = color;
	BorderWidth = width;
	BorderType = type;
}

bool CShape::GetPen(CPen & pen)
{
	return pen.CreatePen(BorderType, BorderWidth, BorderColor);
}

void CShape::GetPen(COLORREF & color, int & width, int & type)
{
	color = this->BorderColor;
	width = this->BorderWidth;
	type = this->BorderType;
}

void CShape::SetBrush(COLORREF color, int type)
{
	FillColor = color;
	FillType = type;
}

bool CShape::GetBrush(CBrush & brush)
{
	return FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS ?
		brush.CreateHatchBrush(FillType, FillColor) : brush.CreateSolidBrush(FillColor);
}

void CShape::GetBrush(COLORREF & color, int & type)
{
	color = this->FillColor;
	type = this->FillType;
}

void CShape::Draw(CDC * pDC)
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
}

void CShape::SetShapeValue(ElementType type, int orgX, int orgY)
{
	Type = type;
	OrgX = orgX;
	OrgY = orgY;
}

void CShape::GetShapeValue(ElementType & type, int & orgX, int & orgY)
{
	type = Type;
	orgX = OrgX;
	orgY = OrgY;
}

void CShape::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;   // 图元类型
		ar << OrgX << OrgY; // 原点坐标
		ar << BorderColor;  // 边界颜色
		ar << BorderType;   // 边框类型
		ar << BorderWidth;  // 边界宽度
		ar << FillColor;    // 填充颜色
		ar << FillType;     // 填充类型
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

bool CSquare::IsMatched(CPoint pnt)
{
	// X 轴方向的绝对偏移量计算
	long abs_offsetX = abs(pnt.x - OrgX);
	// Y 轴方向的绝对偏移量计算
	long abs_offsetY = abs(pnt.y - OrgY);

	double half_of_width = width / 2.0;

	return abs_offsetX <= half_of_width && abs_offsetY <= half_of_width;
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

void CSquare::SetShapeValue(ElementType type, int orgX, int orgY, int width)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->width = width;
}

void CSquare::GetShapeValue(ElementType & type, int & orgX, int & orgY, int &width)
{
	CShape::GetShapeValue(type, orgX, orgY);
	width = this->width;
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

void CCircle::GetShapeValue(ElementType & type, int & orgX, int & orgY, int & radius)
{
	CShape::GetShapeValue(type, orgX, orgY);
	radius = this->radius;
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
void CRectangle::SetShapeValue(ElementType type, int orgX, int orgY, int width, int height)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->width = width;
	this->height = height;
}
void CRectangle::GetShapeValue(ElementType & type, int & orgX, int & orgY, int & width, int & height)
{
	CShape::GetShapeValue(type, orgX, orgY);
	width = this->width;
	height = this->height;
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
void CTriangle::SetShapeValue(ElementType type, int orgX, int orgY, int width)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->width = width;
}
void CTriangle::GetShapeValue(ElementType & type, int & orgX, int & orgY, int & width)
{
	CShape::GetShapeValue(type, orgX, orgY);
	width = this->width;
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

bool CText::IsMatched(CPoint pnt)
{
	// 获取不旋转时，TEXT所占用的矩形区域四点
	POINT lt{ rect.left,rect.top };
	POINT lb{ rect.left,rect.bottom };
	POINT rt{ rect.right,rect.top };
	POINT rb{ rect.right,rect.bottom };

	POINT point[4]{
		RotationPoint(lt,lt,angle),
		RotationPoint(lt,rt,angle),
		RotationPoint(lt,rb,angle),
		RotationPoint(lt,lb,angle)
	};

	CRgn rgn;
	rgn.CreatePolygonRgn(point, 4, ALTERNATE);
	return rgn.PtInRegion(pnt);
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

void CText::SetShapeValue(ElementType type, int orgX, int orgY, CString text, int height, int angle)
{
	CShape::SetShapeValue(type, orgX, orgY);
	this->text = text;
	this->height = height;
	this->angle = angle;
}

void CText::GetShapeValue(ElementType & type, int & orgX, int & orgY, CString & text, int & height, int & angle)
{
	CShape::GetShapeValue(type, orgX, orgY);
	text = this->text;
	height = this->height;
	angle = this->angle;
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
		_T("微软雅黑"));
	OldFont = pDC->SelectObject(F);

	CSize size = pDC->GetTextExtent(text);
	rect.left = OrgX ;
	rect.top = OrgY ;
	rect.right = OrgX + size.cx;
	rect.bottom = OrgY + size.cy;
	// FIX:无法修改字体颜色
	pDC->SetTextColor(BorderColor);
	// 修改背景颜色
	pDC->SetBkColor(FillColor);
	// TODO 以原点居中绘制文本
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
void CEllipse::GetShapeValue(ElementType & type, int & orgX, int & orgY, int & width, int & height)
{
	CShape::GetShapeValue(type, orgX, orgY);
	width = this->width;
	height = this->height;
}
void CEllipse::ToDraw(CDC * pDC)
{
	pDC->Ellipse(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
}
#pragma endregion

#pragma endregion