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

	void SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height);
	void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const;

protected:
	RECT rect;
	CString text;
	int height;
	int angle;
	virtual void ToDraw(CDC* pDC);
private:
	DECLARE_SERIAL(CText)
};
