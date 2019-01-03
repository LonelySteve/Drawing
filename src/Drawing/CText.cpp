#include "stdafx.h"
#include "util.h"
#include "CText.h"

IMPLEMENT_SERIAL(CText, CObject, 1)

SHAPE_GETTER_START(CText)
PTR_ASSIGN(widthEtc, this->angle);
PTR_ASSIGN(text, this->text);
PTR_ASSIGN(height, this->height);
SHAPE_PROPERTY_END

SHAPE_SETTER_START(CText)
this->text = text;
this->height = height;
this->angle = widthEtc;
SHAPE_PROPERTY_END

#pragma region 构造函数
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CText, TEXT, text("这是一段示例文本"), height(25), angle(0), rect())
SHAPE_CLASS_COPY_CONSTRUCTOR(CText, &angle, &this->text, &height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CText, CString text, int height, int angle)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(TEXT, text(text), height(height), angle(angle))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CText, CString text, int height, int angle)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(TEXT, text(text), height(height), angle(angle))
#pragma endregion

bool CText::IsMatched(CPoint pnt)
{
	// 获取不旋转时，TEXT所占用的矩形区域四点
	POINT lt{rect.left, rect.top};
	POINT lb{rect.left, rect.bottom};
	POINT rt{rect.right, rect.top};
	POINT rb{rect.right, rect.bottom};

	POINT point[4]{
		RotationPoint(lt, lt, angle),
		RotationPoint(lt, rt, angle),
		RotationPoint(lt, rb, angle),
		RotationPoint(lt, lb, angle)};

	CRgn rgn;
	rgn.CreatePolygonRgn(point, 4, ALTERNATE);
	return rgn.PtInRegion(pnt);
}

void CText::Serialize(CArchive &ar)
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

void CText::ToDraw(CDC *pDC)
{
	CFont *OldFont, F;
	F.CreateFontW(
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
	OldFont = pDC->SelectObject(&F);

	CSize size = pDC->GetTextExtent(text);
	double changed_rad = ANG_TO_RAD(angle);
	double offset_rad = changed_rad - atan(double(size.cy) / double(size.cx));
	double offset_z = sqrt(pow(size.cx / 2.0, 2) + pow(size.cy / 2.0, 2));
	double offset_y = sin(offset_rad) * offset_z;
	double offset_x = cos(offset_rad) * offset_z;
	LONG x, y;
	x = static_cast<LONG>(OrgX - offset_x);
	y = static_cast<LONG>(OrgY + offset_y);
	rect.left = x;
	rect.top = y;
	rect.right = x + size.cx;
	rect.bottom = y + size.cy;
	// FIX:无法修改字体颜色
	COLORREF oldTxColor = pDC->SetTextColor(BorderColor);
	// 修改背景颜色
	COLORREF oldBkColor = pDC->SetBkColor(FillColor);
	// 以原点居中绘制文本
	pDC->TextOutW(x, y, text);
	pDC->SelectObject(OldFont);
	pDC->SetTextColor(oldTxColor);
	// 不要忘了设置回背景颜色！
	pDC->SetBkColor(oldBkColor);
}
