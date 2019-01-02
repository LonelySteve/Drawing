#pragma once
#include"CShape.h"

/*正方形类*/
class CSquare :public CShape
{
public:
	CSquare();
	CSquare(const CSquare & square);
	CSquare(int orgX, int orgY, int width);
	CSquare(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width);
	virtual void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *width) const;

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	DECLARE_SERIAL(CSquare)
};