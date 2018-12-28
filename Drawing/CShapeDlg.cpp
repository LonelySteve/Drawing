// CShapeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "CShapeDlg.h"
#include "afxdialogex.h"


// CShapeDlg 对话框

IMPLEMENT_DYNAMIC(CShapeDlg, CDialogEx)

CShapeDlg::CShapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSHAPE_DLG, pParent)
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
}


BEGIN_MESSAGE_MAP(CShapeDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CShapeDlg 消息处理程序


BOOL CShapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 初始化 m_comboBox_shapeType
	// 选中第一项
	m_comboBox_shapeType.SetCurSel(0);
	// 初始化 m_listBox_penType
	m_listBox_penType.AddString(_T("PS_SOLID"));
	m_listBox_penType.AddString(_T("PS_DASH"));
	m_listBox_penType.AddString(_T("PS_DOT"));
	m_listBox_penType.AddString(_T("PS_DASHDOT"));
	m_listBox_penType.AddString(_T("PS_DASHDOTDOT"));
	m_listBox_penType.AddString(_T("PS_NULL"));
	m_listBox_penType.AddString(_T("PS_INSIDEFRAME"));
	// 选中第一项
	m_listBox_penType.SetCurSel(0);
	// 初始化 m_listBox_brushType
	m_listBox_brushType.AddString(_T("HS_HORIZONTAL"));
	m_listBox_brushType.AddString(_T("HS_VERTICAL"));
	m_listBox_brushType.AddString(_T("HS_FDIAGONAL"));
	m_listBox_brushType.AddString(_T("HS_BDIAGONAL"));
	m_listBox_brushType.AddString(_T("HS_CROSS"));
	m_listBox_brushType.AddString(_T("HS_DIAGCROSS"));
	m_listBox_brushType.AddString(_T("HS_SOLID"));
	// 选中第一项
	m_listBox_brushType.SetCurSel(0);
	// 初始化 m_edit_orgX
	m_edit_orgX.SetWindowTextW(_T("0"));
	// 初始化 m_edit_orgY
	m_edit_orgY.SetWindowTextW(_T("0"));
	// 初始化 m_edit_widthRadiusAngle
	m_edit_widthRadiusAngle.SetWindowTextW(_T("0"));
	// 初始化 m_edit_penWidth
	m_edit_penWidth.SetWindowTextW(_T("0"));
	// 初始化 m_edit_height
	m_edit_height.SetWindowTextW(_T("0"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CShapeDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}


HBRUSH CShapeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
