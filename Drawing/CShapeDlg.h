#pragma once
#include"CShape.h"

// CShapeDlg 对话框

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

public:
	CShapeDlg(CShape&, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShapeDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSHAPE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	CButton m_btn_pen_color;
	// 画刷类型的ListBox
	CListBox m_listBox_brushType;
	// 画刷颜色的按钮
	CButton m_btn_brushColor;
	// 展示钢笔的颜色的编辑框
	CEdit m_edit_penColor;
	// 展示笔刷的颜色的编辑框
	CEdit m_edit_brushColor;
protected:
	ElementType m_Type;
	int m_x;
	int m_y;
	int m_wra;
	int m_h;
	CString m_text;
	int m_w;
	int m_pen_type;
	int m_brush_type;
protected:
	COLORREF m_pen_color;
	COLORREF m_brush_color;
protected:
	// 对话框类内部维护的图元基类引用
	CShape & shape;
protected:
	virtual BOOL OnInitDialog();

	afx_msg void OnClickedPenColorButton();
	afx_msg void OnClickedBrushColorButton();
	afx_msg void OnSelchangeComboShapeType();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	// 获取图元基类值，这个函数产生的图元基类指针需要手动释放内存
	CShape* GetShapeValueFromDlg();
};
