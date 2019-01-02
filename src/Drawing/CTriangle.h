#pragma once
#include"CShape.h"

/*Èý½ÇÐÎ*/
class CTriangle :public CShape
{
public:
	CTriangle();
	CTriangle(const CTriangle& triangle);
	CTriangle(int orgX, int orgY, int width);
	CTriangle(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	void SetShapeValue(ElementType type, int orgX, int orgY, int width);
	void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *width) const;

protected:
	int width;
	virtual void ToDraw(CDC* pDC);
private:
	DECLARE_SERIAL(CTriangle)
};