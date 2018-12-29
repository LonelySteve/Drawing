// CShapeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "CShapeDlg.h"
#include "afxdialogex.h"
#include "CShape.h"

// CShapeDlg 对话框

IMPLEMENT_DYNAMIC(CShapeDlg, CDialogEx)

CShapeDlg::CShapeDlg(CShape& shape, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSHAPE_DLG, pParent), shape(shape)
	, m_x(0)
	, m_y(0)
	, m_wra(0)
	, m_h(0)
	, m_text(_T(""))
	, m_w(0)
	, m_pen_type(0)
	, m_brush_type(0)
{

}

CShapeDlg::~CShapeDlg()
{
}

void CShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox_shapeType);
	DDX_Control(pDX, IDC_EDIT2, m_edit_orgX);
	DDX_Control(pDX, IDC_EDIT4, m_edit_orgY);
	DDX_Control(pDX, IDC_EDIT3, m_edit_widthRadiusAngle);
	DDX_Control(pDX, IDC_EDIT5, m_edit_height);
	DDX_Control(pDX, IDC_EDIT6, m_edit_text);
	DDX_Control(pDX, IDC_EDIT1, m_edit_penWidth);
	DDX_Control(pDX, IDC_LIST1, m_listBox_penType);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_pen_color);
	DDX_Control(pDX, IDC_LIST2, m_listBox_brushType);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_brushColor);
	// 转换一下类型，利用一下数据交换来完成数据绑定
	int tmp = (int)m_Type;
	DDX_CBIndex(pDX, IDC_COMBO1, tmp);
	m_Type = (ElementType)tmp;
	DDX_Text(pDX, IDC_EDIT2, m_x);
	DDX_Text(pDX, IDC_EDIT4, m_y);
	DDX_Text(pDX, IDC_EDIT3, m_wra);
	DDX_Text(pDX, IDC_EDIT5, m_h);
	DDX_Text(pDX, IDC_EDIT6, m_text);
	DDX_Text(pDX, IDC_EDIT1, m_w);
	DDX_LBIndex(pDX, IDC_LIST1, m_pen_type);
	DDX_LBIndex(pDX, IDC_LIST2, m_brush_type);
	DDX_Control(pDX, IDC_EDIT7, m_edit_penColor);
	DDX_Control(pDX, IDC_EDIT8, m_edit_brushColor);
}


BEGIN_MESSAGE_MAP(CShapeDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CShapeDlg::OnClickedPenColorButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CShapeDlg::OnClickedBrushColorButton)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CShapeDlg::OnSelchangeComboShapeType)
END_MESSAGE_MAP()


// CShapeDlg 消息处理程序
BOOL CShapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	// 初始化 m_listBox_penType
	m_listBox_penType.AddString(_T("PS_SOLID"));
	m_listBox_penType.AddString(_T("PS_DASH"));
	m_listBox_penType.AddString(_T("PS_DOT"));
	m_listBox_penType.AddString(_T("PS_DASHDOT"));
	m_listBox_penType.AddString(_T("PS_DASHDOTDOT"));
	m_listBox_penType.AddString(_T("PS_NULL"));
	m_listBox_penType.AddString(_T("PS_INSIDEFRAME"));
	// 初始化 m_listBox_brushType
	m_listBox_brushType.AddString(_T("HS_HORIZONTAL"));
	m_listBox_brushType.AddString(_T("HS_VERTICAL"));
	m_listBox_brushType.AddString(_T("HS_FDIAGONAL"));
	m_listBox_brushType.AddString(_T("HS_BDIAGONAL"));
	m_listBox_brushType.AddString(_T("HS_CROSS"));
	m_listBox_brushType.AddString(_T("HS_DIAGCROSS"));
	m_listBox_brushType.AddString(_T("HS_SOLID"));

	// 初始化值类型数据成员
	shape.GetShapeValue(m_Type, m_x, m_y);
	shape.GetPen(m_pen_color, m_w, m_pen_type);
	shape.GetBrush(m_brush_color, m_brush_type);

	switch (m_Type)
	{
	case SQUARE:
	{
		CSquare & sq = (CSquare &)shape;
		sq.GetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case RECTANGLE:
	{
		CRectangle & re = (CRectangle &)shape;
		re.GetShapeValue(m_Type, m_x, m_y, m_wra, m_h);
		break;
	}
	case CIRCLE:
	{
		CCircle & ci = (CCircle&)shape;
		ci.GetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case ELLIPSE:
	{
		CEllipse & el = (CEllipse &)shape;
		el.GetShapeValue(m_Type, m_x, m_y, m_wra, m_h);
		break;
	}
	case TRIANGLE:
	{
		CTriangle & tr = (CTriangle &)shape;
		tr.GetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case TEXT:
	{
		CText & te = (CText &)shape;
		te.GetShapeValue(m_Type, m_x, m_y, m_text, m_h, m_wra);
		break;
	}

	}

	UpdateData(FALSE);
	OnSelchangeComboShapeType();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

HBRUSH CShapeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	int id = pWnd->GetDlgCtrlID();
	if (id == IDC_EDIT7)
	{
		return CreateSolidBrush(m_pen_color);
	}
	else if (id == IDC_EDIT8)
	{
		return CreateSolidBrush(m_brush_color);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

CShape* CShapeDlg::GetShapeValueFromDlg()
{
	CShape* ps = nullptr;
	
	switch (m_Type)
	{
	case SQUARE:
	{
		ps = new CSquare();
		((CSquare*)ps)->SetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case RECTANGLE:
	{
		ps = new CRectangle();
		((CRectangle*)ps)->SetShapeValue(m_Type, m_x, m_y, m_wra, m_h);
		break;
	}
	case CIRCLE:
	{
		ps = new CCircle();
		((CCircle*)ps)->SetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case ELLIPSE:
	{
		ps = new CEllipse();
		((CEllipse*)ps)->SetShapeValue(m_Type, m_x, m_y, m_wra, m_h);
		break;
	}
	case TRIANGLE:
	{
		ps = new CTriangle();
		((CTriangle*)ps)->SetShapeValue(m_Type, m_x, m_y, m_wra);
		break;
	}
	case TEXT:
	{
		ps = new CText();
		((CText*)ps)->SetShapeValue(m_Type, m_x, m_y, m_text, m_h, m_wra);
		break;
	}

	}

	ps->SetBrush(m_brush_color, m_brush_type);
	ps->SetPen(m_pen_color, m_w, m_pen_type);

	return ps;
}

void CShapeDlg::OnClickedPenColorButton()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_pen_color = dlg.GetColor();
		m_edit_penColor.Invalidate();
		// 立即发生重绘
		m_edit_penColor.UpdateWindow();
	}
}

void CShapeDlg::OnClickedBrushColorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_brush_color = dlg.GetColor();
		m_edit_brushColor.Invalidate();
		// 立即发生重绘
		m_edit_brushColor.UpdateWindow();
	}
}

void CShapeDlg::OnSelchangeComboShapeType()
{
	m_edit_widthRadiusAngle.EnableWindow(TRUE);
	m_edit_height.EnableWindow(TRUE);
	m_edit_text.EnableWindow(TRUE);
	m_edit_penWidth.EnableWindow(TRUE);
	UpdateData(TRUE);
	switch (m_Type)
	{
	case RECTANGLE:
	case ELLIPSE:
		m_edit_text.EnableWindow(FALSE);
		break;
	case CIRCLE:
	case SQUARE:
	case TRIANGLE:
		m_edit_height.EnableWindow(FALSE);
		m_edit_text.EnableWindow(FALSE);
		break;
	case TEXT:
		break;
	}
}
