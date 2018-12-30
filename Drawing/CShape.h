#pragma once
#include<afx.h>
#include<afxwin.h>

enum ElementType { SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };

/*抽象类 CShape*/
class CShape : public CObject
{
public:
	CShape(ElementType type, int orgX, int orgY);
	CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	void SetPen(COLORREF color, int width, int type);
	bool GetPen(CPen &pen);
	void GetPen(COLORREF &color, int &width, int &type);
	void SetBrush(COLORREF color, int type);
	bool GetBrush(CBrush &brush);
	void GetBrush(COLORREF &color, int &type);
	virtual void Draw(CDC *pDC);
	virtual bool IsMatched(CPoint pnt) = 0;
	virtual void SetShapeValue(ElementType type, int orgX, int orgY);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY);

protected:
	ElementType Type;
	int OrgX;
	int OrgY;
	COLORREF BorderColor = RGB(0, 0, 0);
	int BorderType = 0;
	int BorderWidth = 0;
	COLORREF FillColor = RGB(0, 0, 0);
	int FillType = 0;

	virtual void ToDraw(CDC *pDC) = 0;
	virtual void Serialize(CArchive &ar);
};

/*正方形类*/
class CSquare :public CShape
{
public:
	CSquare();
	CSquare(int orgX, int orgY, int width);
	CSquare(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, int &width);

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	DECLARE_SERIAL(CSquare)
};

/*圆形*/
class CCircle :public CShape
{
public:
	CCircle();
	CCircle(int orgX, int orgY, int radius);
	CCircle(int orgX, int orgY, int radius, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int radius);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, int &radius);

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int radius;
	DECLARE_SERIAL(CCircle)
};

/*矩形*/
class CRectangle :public CShape
{
public:
	CRectangle();
	CRectangle(int orgX, int orgY, int width, int height);
	CRectangle(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width, int height);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, int &width, int &height);

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	int height;
	DECLARE_SERIAL(CRectangle)
};

/*三角形*/
class CTriangle :public CShape
{
public:
	CTriangle();
	CTriangle(int orgX, int orgY, int width);
	CTriangle(int orgX, int orgY, int width, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, int &width);

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	DECLARE_SERIAL(CTriangle)
};

/*文本*/
class CText :public CShape
{
public:
	CText();
	CText(int orgX, int orgY, CString text, int height, int angle);
	CText(int orgX, int orgY, CString text, int height, int angle, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, CString text, int height, int angle);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, CString &text, int &height, int &angle);

protected:
	virtual void ToDraw(CDC* pDC);
private:
	RECT rect;
	CString text;
	int height;
	int angle;
	DECLARE_SERIAL(CText)
};


/*椭圆*/
class CEllipse :public CShape
{
public:
	CEllipse();
	CEllipse(int orgX, int orgY, int width, int height);
	CEllipse(int orgX, int orgY, int width, int height, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive &ar);
	virtual void SetShapeValue(ElementType type, int orgX, int orgY, int width, int height);
	virtual void GetShapeValue(ElementType &type, int &orgX, int &orgY, int &width, int &height);

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	int height;
	DECLARE_SERIAL(CEllipse)
};

