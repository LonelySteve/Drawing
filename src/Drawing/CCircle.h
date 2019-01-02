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
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int radius);
	virtual void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *radius) const;

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int radius;
	DECLARE_SERIAL(CCircle)
};
