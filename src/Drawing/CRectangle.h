#pragma once
#include"CShape.h"

/*¾ØÐÎ*/
class CRectangle :public CShape
{
public:
	CRectangle();
	CRectangle(const CRectangle & rectangle);
	CRectangle(int orgX, int orgY, int width, int height);
	CRectangle(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width, int height);
	virtual void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *width, int *height) const;

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	int height;
	DECLARE_SERIAL(CRectangle)
};