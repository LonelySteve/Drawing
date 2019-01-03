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

#pragma region ���캯��
SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(CText, TEXT, text("����һ��ʾ���ı�"), height(25), angle(0), rect())
SHAPE_CLASS_COPY_CONSTRUCTOR(CText, &angle, &this->text, &height)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(CText, CString text, int height, int angle)
SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(TEXT, text(text), height(height), angle(angle))
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(CText, CString text, int height, int angle)
SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(TEXT, text(text), height(height), angle(angle))
#pragma endregion

bool CText::IsMatched(CPoint pnt)
{
	// ��ȡ����תʱ��TEXT��ռ�õľ��������ĵ�
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
		_T("΢���ź�"));
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
	// FIX:�޷��޸�������ɫ
	COLORREF oldTxColor = pDC->SetTextColor(BorderColor);
	// �޸ı�����ɫ
	COLORREF oldBkColor = pDC->SetBkColor(FillColor);
	// ��ԭ����л����ı�
	pDC->TextOutW(x, y, text);
	pDC->SelectObject(OldFont);
	pDC->SetTextColor(oldTxColor);
	// ��Ҫ�������ûر�����ɫ��
	pDC->SetBkColor(oldBkColor);
}
