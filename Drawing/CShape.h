#pragma once
#include<afx.h>
#include<afxwin.h>

enum ElementType { NOTSET, SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };

/*≥ÈœÛ¿‡ CShape*/
class CShape : public CObject
{
public:
	CShape(ElementType type, int orgX, int orgY, COLORREF borderColor, int borderType, int borderWidth, COLORREF fillColor, int fillType);
	~CShape();
	virtual void Draw(CDC * pDC) = 0;
	virtual bool IsMatched(CPoint pnt) = 0;

protected:
	ElementType Type;
	int OrgX;
	int OrgY;
	COLORREF BorderColor;
	int BorderType;
	int BorderWidth;
	COLORREF FillColor;
	int FillType;

private:

};

class CSquare :public CShape
{
public:
	CSquare();
	CSquare(int orgX, int orgY, int width);
	CSquare(int orgX, int orgY, int width, COLORREF borderColor, int borderType, int borderWidth, COLORREF fillColor, int fillType);
	~CSquare();
	void Draw(CDC * pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive &ar);
private:
	int width;
	DECLARE_SERIAL(CSquare)
};

