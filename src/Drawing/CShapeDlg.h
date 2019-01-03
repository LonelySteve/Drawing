#pragma once
#include "CShapes.h"

// CShapeDlg 对话框

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

  public:
	CShapeDlg(CShape *cur_pShape, CWnd *pParent = nullptr); // 标准构造函数
	virtual ~CShapeDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_CSHAPE_DLG
	};
#endif

  protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
  protected:
	//===================控件类型=======================
	// 选择图元类型的ComboBox
	CComboBox m_comboBox_shapeType;
	// 原点X的编辑框
	CEdit m_edit_orgX;
	// 原点Y的编辑框对象
	CEdit m_edit_orgY;
	// 宽度、半径、角度的编辑框
	CEdit m_edit_widthRadiusAngle;
	// 高度的编辑框
	CEdit m_edit_height;
	// 文字的编辑框
	CEdit m_edit_text;
	// 线宽的编辑框
	CEdit m_edit_penWidth;
	// 线型的ListBox
	CListBox m_listBox_penType;
	// 钢笔颜色的按钮
	CButton m_btn_penColor;
	// 画刷类型的ListBox
	CListBox m_listBox_brushType;
	// 画刷颜色的按钮
	CButton m_btn_brushColor;
	// 展示钢笔的颜色的编辑框
	CEdit m_edit_penColor;
	// 展示笔刷的颜色的编辑框
	CEdit m_edit_brushColor;

  protected:
	// 当前对话框选择的形状类型
	ElementType m_Type;
	// 原点 X 值
	int m_x;
	// 原点 Y 值
	int m_y;
	// 宽度，半径或旋转角度
	int m_w;
	// 高度
	int m_h;
	// 文本
	CString m_text;
	// 钢笔笔宽
	int m_pen_width;
	// 钢笔类型
	int m_pen_type;
	// 笔刷类型
	int m_brush_type;

  protected:
	// 边框颜色
	COLORREF m_borderColor;
	// 填充颜色
	COLORREF m_fillColor;

  protected:
	// 对话框类内部维护的图元基类指针，在调用GetCurShape函数之后将会指向当前形状类型的图元对象
	CShape *cur_pShape;
	// 对话框内部用来为维护每种形状类型的图元对象的指针数组
	CShape *pShapes[SHAPE_TYPE_COUNT]{NULL};

  protected:
	// 初始化对话框的事件处理程序
	virtual BOOL OnInitDialog();
	// 将图元对象的指定属性设置到对话框值类型的数据成员中
	void CShapeDlg::SetShapeValueToDlg(
		const CShape *shape,
		bool setType = true,
		bool setOrgX = true,
		bool setOrgY = true,
		bool setWidthEtc = true,
		bool setHeight = true,
		bool setText = true,
		bool setPenWidth = true,
		bool setPenType = true,
		bool setPenColor = true,
		bool setBrushType = true,
		bool setBrushColo = true);
	// 边框颜色按钮点击事件处理程序
	afx_msg void OnClickedBorderColorButton();
	// 填充颜色按钮点击事件处理程序
	afx_msg void OnClickedFillColorButton();
	// 形状类型下拉列表框索引改变后的事件处理程序
	afx_msg void OnSelchangeComboShapeType();
	// 绘制控件颜色时的事件处理程序
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);

  public:
	// 获取当前选择的图元对象指针
	// 注意：该指针将会随本对话框对象的析构而无效
	CShape *GetCurShape();
	// 更新界面上控件启用状态
	void UpdateCtlEnabledStatus();
};
