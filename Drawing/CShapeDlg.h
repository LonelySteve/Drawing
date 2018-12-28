#pragma once


// CShapeDlg 对话框

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

public:
	CShapeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShapeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSHAPE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
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
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
