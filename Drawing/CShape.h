#pragma once
#include<afx.h>
#include<afxwin.h>

enum ElementType { NOTSET, SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };

/*抽象类 CShape*/
class CShape : public CObject
{
public:
	CShape(ElementType type, int orgX, int orgY);
	CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);

	virtual void Draw(CDC * pDC);
	virtual bool IsMatched(CPoint pnt) = 0;

protected:
	ElementType Type;
	int OrgX;
	int OrgY;
	COLORREF BorderColor = RGB(0, 0, 0);
	int BorderType = 0;
	int BorderWidth = 0;
	COLORREF FillColor = RGB(0, 0, 0);
	int FillType = -1;

	virtual void ToDraw(CDC *pDC) = 0;

private:

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

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int radius;
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

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	int height;
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

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
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

protected:
	virtual void ToDraw(CDC* pDC);

private:
	CString text;
	int height;
	int angle;
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

protected:
	virtual void ToDraw(CDC* pDC);

private:
	int width;
	int height;
};

