#pragma once
#include "CShape.h"

/*т╡пн*/
class CCircle :public CShape
{
public:
	CCircle();
	CCircle(const CCircle & circle);
	CCircle(int orgX, int orgY, int radius);
	CCircle(int orgX, int orgY, int radius, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);

	void SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height);
	void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const;

protected:
	int radius;
	virtual void ToDraw(CDC* pDC);

private:
	DECLARE_SERIAL(CCircle)
};
