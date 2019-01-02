#pragma once
#include "CShape.h"

/*��Բ*/
class CEllipse :public CShape
{
public:
	CEllipse();
	CEllipse(const CEllipse & ellipse);
	CEllipse(int orgX, int orgY, int width, int height);
	CEllipse(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	void SetShapeValue(ElementType type, int orgX, int orgY, int width, int height);
	void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *width, int *height) const;

protected:
	int width;
	int height;
	virtual void ToDraw(CDC* pDC);

private:
	DECLARE_SERIAL(CEllipse)
};
