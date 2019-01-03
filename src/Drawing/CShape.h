#pragma once
#include <afx.h>
#include <afxwin.h>

/*Ԫ������ö�ٶ���*/
enum ElementType
{
	/*������*/
	SQUARE,
	/*����*/
	RECTANGLE,
	/*Բ��*/
	CIRCLE,
	/*��Բ*/
	ELLIPSE,
	/*������*/
	TRIANGLE,
	/*�ı�*/
	TEXT
};

/*������ CShape*/
class CShape : public CObject
{
  public:
	static CShape *DynamicCShapeObj(const CShape *shape, bool copy = true);

	CShape(const CShape &shape);
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

// ��״��궨�忪ͷ
#define SHAPE_CLASS_START(className, ...)                                                                                                      \
	class className : public CShape                                                                                                            \
	{                                                                                                                                          \
	  private:                                                                                                                                 \
		DECLARE_SERIAL(className)                                                                                                              \
	  public:                                                                                                                                  \
		className();                                                                                                                           \
		className(const className &className##Obj);                                                                                            \
		className(int orgX, int orgY, ##__VA_ARGS__);                                                                                          \
		className(int orgX, int orgY, ##__VA_ARGS__, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType); \
		virtual bool IsMatched(CPoint pnt);                                                                                                    \
		virtual void Serialize(CArchive &ar);                                                                                                  \
		void SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height);                                                        \
		void GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const;                          \
                                                                                                                                               \
	  protected:                                                                                                                               \
		virtual void ToDraw(CDC *pDC);
// ��״��궨���β
#define SHAPE_CLASS_END \
	}                   \
	;

#define SHAPE_PROPERTY_END }

#define SHAPE_SETTER_START(className)                                                         \
	void className::SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height) \
	{                                                                                         \
		CShape::SetShapeValue(orgX, orgY, widthEtc, text, height);

#define SHAPE_GETTER_START(className)                                                                                       \
	void className::GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const \
	{                                                                                                                       \
		CShape::GetShapeValue(type, orgX, orgY, widthEtc, text, height);

#define SHAPE_PROPERTY_END }
// ͼԪ���ԡ��뾶��
#define SHAPE_PROPERTY_RADIUS int radius
// ͼԪ���ԡ���ȡ�
#define SHAPE_PROPERTY_WIDTH int width
// ͼԪ���ԡ��߶ȡ�
#define SHAPE_PROPERTY_HEIGHT int height
// ͼԪ���ԡ��Ƕȡ�
#define SHAPE_PROPERTY_ANGLE int angle
// ͼԪ���ԡ��ı���
#define SHAPE_PROPERTY_TEXT CString text
// Ԥ�ý����п�͸ߵ�ͼԪ��
#define PREF_WH_SHAPE_CLASS(className)                                        \
	SHAPE_CLASS_START(className, SHAPE_PROPERTY_WIDTH, SHAPE_PROPERTY_HEIGHT) \
  protected:                                                                  \
	SHAPE_PROPERTY_WIDTH;                                                     \
	SHAPE_PROPERTY_HEIGHT;                                                    \
	SHAPE_CLASS_END
// Ԥ�ý����п��ͼԪ��
#define PREF_W_SHAPE_CLASS(className)                  \
	SHAPE_CLASS_START(className, SHAPE_PROPERTY_WIDTH) \
  protected:                                           \
	SHAPE_PROPERTY_WIDTH;                              \
	SHAPE_CLASS_END

#define PREF_W_SHAPE_PROPERTOR(className, w_name) \
	SHAPE_GETTER_START(className)                 \
	PTR_ASSIGN(widthEtc, this->w_name);           \
	SHAPE_PROPERTY_END                            \
	SHAPE_SETTER_START(className)                 \
	this->w_name = widthEtc;                      \
	SHAPE_PROPERTY_END

#define PREF_WH_SHAPE_PROPERTOR(className) \
	SHAPE_GETTER_START(className)          \
	PTR_ASSIGN(widthEtc, this->width);     \
	PTR_ASSIGN(height, this->height);      \
	SHAPE_PROPERTY_END                     \
	SHAPE_SETTER_START(className)          \
	this->width = widthEtc;                \
	this->height = height;                 \
	SHAPE_PROPERTY_END

#define SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(className, shapeType, ...) \
	className::className() : CShape(shapeType, 0, 0), ##__VA_ARGS__ {}

#define SHAPE_CLASS_COPY_CONSTRUCTOR(className, ...)                               \
	className::className(const className &className##Obj) : CShape(className##Obj) \
	{                                                                              \
		className##Obj.GetShapeValue(&Type, &OrgX, &OrgY, ##__VA_ARGS__);          \
	}

#define SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(className, ...) \
	className::className(int orgX, int orgY, ##__VA_ARGS__) :
#define SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(shapeType, ...) \
	CShape(shapeType, orgX, orgY), ##__VA_ARGS__ {}

#define SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(className, ...) \
	className::className(int orgX, int orgY, ##__VA_ARGS__, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
#define SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(shapeType, ...) \
: CShape(shapeType, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType),##__VA_ARGS__ {}
