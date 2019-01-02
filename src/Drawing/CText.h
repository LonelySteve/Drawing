#pragma once
#include"CShape.h"

/*ÎÄ±¾*/
class CText :public CShape
{
public:
	CText();
	CText(const CText & text);
	CText(int orgX, int orgY, CString text, int height, int angle);
	CText(int orgX, int orgY, CString text, int height, int angle, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int angle, CString text, int height);
	virtual void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *angle, CString *text, int *height) const;

protected:
	virtual void ToDraw(CDC* pDC);
private:
	RECT rect;
	CString text;
	int height;
	int angle;
	DECLARE_SERIAL(CText)
};
