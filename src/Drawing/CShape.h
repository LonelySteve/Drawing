#pragma once
#include <afx.h>
#include <afxwin.h>

/*元素类型枚举定义*/
enum ElementType
{
	/*正方形*/
	SQUARE,
	/*矩形*/
	RECTANGLE,
	/*圆形*/
	CIRCLE,
	/*椭圆*/
	ELLIPSE,
	/*正三角形*/
	TRIANGLE,
	/*文本*/
	TEXT
};

/*抽象类 CShape*/
class CShape : public CObject
{
  public:
	// 获取图元类型的拷贝【需手动释放内存】
	virtual CShape *Clone() = 0; // 子类必须实现相应的拷贝函数

	CShape(const CShape &shape);
	CShape(ElementType type, int orgX, int orgY);
	CShape(ElementType type, int orgX, int orgY, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType);
	// CObject 中的析构函数是纯虚的，这里保留虚特性并期望子类重写实现相应的析构函数
	virtual ~CShape(); // 空实现的析构函数，保留虚特性
	// 获取形状类型
	ElementType GetShapeType() const;
	void SetPen(COLORREF color, int width, int type);
	bool GetPen(CPen &pen) const;
	void GetPen(COLORREF *color, int *width, int *type) const;
	void SetBrush(COLORREF color, int type);
	bool GetBrush(CBrush &brush) const;
	void GetBrush(COLORREF *color, int *type) const;
	// 进行绘制
	virtual void Draw(CDC *pDC); // 一般情况下，子类不需要重写该函数，而是重写 ToDraw 函数来完成核心绘制。
								 // 本函数会进行钢笔和笔刷的对象维护工作，子类只需关心 ToDraw 函数的实现。
	// 指定的点是否能匹配到该图元
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
	// 进行绘制工作的核心部分
	virtual void ToDraw(CDC *pDC) = 0;
	// 序列化图元对象
	virtual void Serialize(CArchive &ar);
};

// 图元类宏定义开头
#define SHAPE_CLASS_START(className, ...)                                                                                                      \
	class className : public CShape                                                                                                            \
	{                                                                                                                                          \
	  private:                                                                                                                                 \
		DECLARE_SERIAL(className)                                                                                                              \
	  public:                                                                                                                                  \
		className();                                                                                                                           \
		CShape *Clone();                                                                                                                       \
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
// 图元类宏定义结尾
#define SHAPE_CLASS_END \
	}                   \
	;
// 图元Setter的宏定义开头
#define SHAPE_SETTER_START(className)                                                         \
	void className::SetShapeValue(int orgX, int orgY, int widthEtc, CString text, int height) \
	{                                                                                         \
		CShape::SetShapeValue(orgX, orgY, widthEtc, text, height);
// 图元Getter的宏定义开头
#define SHAPE_GETTER_START(className)                                                                                       \
	void className::GetShapeValue(ElementType *type, int *orgX, int *orgY, int *widthEtc, CString *text, int *height) const \
	{                                                                                                                       \
		CShape::GetShapeValue(type, orgX, orgY, widthEtc, text, height);
// 图元属性宏定义结尾
#define SHAPE_PROPERTY_END }
// 图元属性【半径】
#define SHAPE_PROPERTY_RADIUS int radius
// 图元属性【宽度】
#define SHAPE_PROPERTY_WIDTH int width
// 图元属性【高度】
#define SHAPE_PROPERTY_HEIGHT int height
// 图元属性【角度】
#define SHAPE_PROPERTY_ANGLE int angle
// 图元属性【文本】
#define SHAPE_PROPERTY_TEXT CString text
// 预置仅具有宽的图元类
#define PREF_W_SHAPE_CLASS(className)                  \
	SHAPE_CLASS_START(className, SHAPE_PROPERTY_WIDTH) \
  protected:                                           \
	SHAPE_PROPERTY_WIDTH;                              \
	SHAPE_CLASS_END
// 预置仅具有宽和高的图元类
#define PREF_WH_SHAPE_CLASS(className)                                        \
	SHAPE_CLASS_START(className, SHAPE_PROPERTY_WIDTH, SHAPE_PROPERTY_HEIGHT) \
  protected:                                                                  \
	SHAPE_PROPERTY_WIDTH;                                                     \
	SHAPE_PROPERTY_HEIGHT;                                                    \
	SHAPE_CLASS_END
// 预置的仅具有宽度的属性器
#define PREF_W_SHAPE_PROPERTOR(className, w_name) \
	SHAPE_GETTER_START(className)                 \
	PTR_ASSIGN(widthEtc, this->w_name);           \
	SHAPE_PROPERTY_END                            \
	SHAPE_SETTER_START(className)                 \
	this->w_name = widthEtc;                      \
	SHAPE_PROPERTY_END
// 预置的仅具有宽度和高度的属性器
#define PREF_WH_SHAPE_PROPERTOR(className) \
	SHAPE_GETTER_START(className)          \
	PTR_ASSIGN(widthEtc, this->width);     \
	PTR_ASSIGN(height, this->height);      \
	SHAPE_PROPERTY_END                     \
	SHAPE_SETTER_START(className)          \
	this->width = widthEtc;                \
	this->height = height;                 \
	SHAPE_PROPERTY_END
// 无参的图元类构造函数宏定义
#define SHAPE_CLASS_NO_ARGS_CONSTRUCTOR(className, shapeType, ...) \
	className::className() : CShape(shapeType, 0, 0), ##__VA_ARGS__ {}
// 图元类拷贝构造函数宏定义
#define SHAPE_CLASS_COPY_CONSTRUCTOR(className, ...)                               \
	className::className(const className &className##Obj) : CShape(className##Obj) \
	{                                                                              \
		className##Obj.GetShapeValue(&Type, &OrgX, &OrgY, ##__VA_ARGS__);          \
	}
// 图元类简单参数构造函数宏定义
#define SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_START(className, ...) \
	className::className(int orgX, int orgY, ##__VA_ARGS__) :
#define SHAPE_CLASS_SAMPLE_ARGS_CONSTRUCTOR_END(shapeType, ...) \
	CShape(shapeType, orgX, orgY), ##__VA_ARGS__ {}
// 图元类全参数构造函数宏定义
#define SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_START(className, ...) \
	className::className(int orgX, int orgY, ##__VA_ARGS__, COLORREF fillColor, int fillType, COLORREF borderColor, int borderWidth, int borderType)
#define SHAPE_CLASS_FULL_ARGS_CONSTRUCTOR_END(shapeType, ...) \
: CShape(shapeType, orgX, orgY, fillColor, fillType, borderColor, borderWidth, borderType),##__VA_ARGS__ {}
// 图元类克隆函数定义宏
#define SHAPE_CLONE(className)       \
	CShape *className::Clone()       \
	{                                \
		return new className(*this); \
	}