#pragma once
#include<afx.h>
#include<afxwin.h>

enum ElementType { SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };

/*≥ÈœÛ¿‡ CShape*/
class CShape : public CObject
{
public:
	static CShape * DynamicCShapeObj(const CShape * shape, bool copy = true);

	CShape(const CShape& shape);
	CShape(ElementType type, int orgX, int orgY);
	CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	ElementType GetShapeType() const;
	void SetPen(COLORREF color, int width, int type);
	bool GetPen(CPen &pen) const;
	void GetPen(COLORREF *color, int *width, int *type) const;
	void SetBrush(COLORREF color, int type);
	bool GetBrush(CBrush &brush) const;
	void GetBrush(COLORREF *color, int *type) const;
	virtual void Draw(CDC *pDC);
	virtual bool IsMatched(CPoint pnt) = 0;
	virtual void SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height);
	virtual void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const;

protected:
	ElementType Type;
	int OrgX;
	int OrgY;
	COLORREF BorderColor = RGB(0, 0, 0);
	int BorderType = 0;
	int BorderWidth = 0;
	COLORREF FillColor = RGB(255, 255, 255);
	int FillType = 0;

	virtual void ToDraw(CDC *pDC) = 0;
	virtual void Serialize(CArchive &ar);
};
