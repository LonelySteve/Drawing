#pragma once
#include "CShape.h"

/*Õ÷‘≤*/
class CEllipse :public CShape
{
public:
	CEllipse();
	CEllipse(const CEllipse & ellipse);
	CEllipse(int orgX, int orgY, int width, int height);
	CEllipse(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);

	void SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height);
	void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const;

protected:
	int width;
	int height;
	virtual void ToDraw(CDC* pDC);

private:
	DECLARE_SERIAL(CEllipse)
};
