#pragma once
#include "CShapes.h"

// CShapeDlg 对话框

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

  public:
	CShapeDlg(CShape *pShape, CWnd *pParent = nullptr); // 标准构造函数
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
	// 对话框类内部维护的图元基类指针
	CShape *pShape;
	// 对话框内部用来为维护每个类型的图元对象的指针数组
	CShape *pShapes[6]{NULL};

  protected:
	virtual BOOL OnInitDialog();

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

	afx_msg void OnClickedPenColorButton();
	afx_msg void OnClickedBrushColorButton();
	afx_msg void OnSelchangeComboShapeType();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  public:
	// 获取图元基类对象指针，该指针将会随对话框对象的析构而无效
	CShape *GetCurShapeValueFromDlg();
	void UpdateUIEnabledStatus();
};
