// CShapeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "CShapeDlg.h"
#include "afxdialogex.h"
#include "CShape.h"
#include "util.h"

// CShapeDlg 对话框

IMPLEMENT_DYNAMIC(CShapeDlg, CDialogEx)

CShapeDlg::CShapeDlg(CShape* pShape, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CSHAPE_DLG, pParent), pShape(pShape)
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
	for (size_t i = 0; i < 6; i++)
	{
		delete pShapes[i];
		pShapes[i] = nullptr;
	}
	pShape = NULL;
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

	// 为每种图元对象建立单独的对象
#define TM_1(index,className) PTR_VAL_ASSIGN(pShapes[index],new className())

	TM_1(0, CSquare);
	TM_1(1, CRectangle);
	TM_1(2, CCircle);
	TM_1(3, CEllipse);
	TM_1(4, CTriangle);
	TM_1(5, CText);

	if (pShape != NULL)    // 这个时候是修改图元对象
	{
		ElementType type = pShape->GetShapeType();
		delete pShapes[type];
		// 调用CShape的动态内存拷贝函数拷贝源指针指向的对象
		pShapes[type] = CShape::DynamicCShapeObj(pShape, true);
	}
	else
	{
		pShape = pShapes[m_Type];
	}
	// 更新值类型数据成员
	SetShapeValueToDlg(pShape);
	// 更新UI启用状态
	UpdateUIEnabledStatus();
	// 更新界面，这个过程可能会触发 OnSelchangeComboShapeType 回调函数
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CShapeDlg::SetShapeValueToDlg(
	const CShape * shape,
	bool setType,
	bool setOrgX,
	bool setOrgY,
	bool setWidthEtc,
	bool setHeight,
	bool setText,
	bool setPenWidth,
	bool setPenType,
	bool setPenColor,
	bool setBrushType,
	bool setBrushColor
)
{
	PTR_NULL_RETURN(shape);
	ElementType type;
	CString text;
	COLORREF penColor, brushColor;
	int orgX, orgY, height = this->m_h, widthEtc, penWidth, penType, brushType;
	shape->GetPen(&penColor, &penWidth, &penType);
	shape->GetBrush(&brushColor, &brushType);

#define TM_0(className,...)  \
{ \
		className & sq = (className &)*shape; \
	sq.GetShapeValue(&type, &orgX, &orgY,##__VA_ARGS__); \
		break; \
}

	switch (shape->GetShapeType())
	{
	case SQUARE:TM_0(CSquare, &widthEtc)
	case RECTANGLE:TM_0(CRectangle, &widthEtc, &height)
	case CIRCLE:TM_0(CCircle, &widthEtc)
	case ELLIPSE:TM_0(CEllipse, &widthEtc, &height)
	case TRIANGLE:TM_0(CTriangle, &widthEtc)
	case TEXT:TM_0(CText, &widthEtc, &text, &height)
	}

#undef TM_0
	IF_ASSIGN(setType, m_Type, type);
	IF_ASSIGN(setOrgX, m_x, orgX);
	IF_ASSIGN(setOrgY, m_y, orgY);
	IF_ASSIGN(setWidthEtc, m_wra, widthEtc);
	IF_ASSIGN(setHeight, m_h, height);
	IF_ASSIGN(setText, m_text, text);
	IF_ASSIGN(setPenWidth, m_w, penWidth);
	IF_ASSIGN(setPenType, m_pen_type, penType);
	IF_ASSIGN(setPenColor, m_pen_color, penColor);
	IF_ASSIGN(setBrushType, m_brush_type, brushType);
	IF_ASSIGN(setBrushColor, m_brush_color, brushColor);
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

CShape* CShapeDlg::GetCurShapeValueFromDlg()
{
	pShapes[m_Type]->SetBrush(m_brush_color, m_brush_type);
	pShapes[m_Type]->SetPen(m_pen_color, m_w, m_pen_type);

#define TM_2(className,index,...) \
	PTR_CALL_METHOD(((className*)pShapes[index]), SetShapeValue(m_Type, m_x, m_y, m_wra,##__VA_ARGS__))

	switch (m_Type)
	{
	case SQUARE:
		TM_2(CSquare, 0);
		break;
	case RECTANGLE:
		TM_2(CRectangle, 1, m_h);
		break;
	case CIRCLE:
		TM_2(CCircle, 2);
		break;
	case ELLIPSE:
		TM_2(CEllipse, 3, m_h);
		break;
	case TRIANGLE:
		TM_2(CTriangle, 4);
		break;
	case TEXT:
		TM_2(CText, 5, m_text, m_h);
		break;
	}
#undef TM_2
	return pShapes[m_Type];
}

void CShapeDlg::UpdateUIEnabledStatus()
{
	// 根据不同的图元类型启用或禁用部分控件
	m_edit_widthRadiusAngle.EnableWindow(TRUE);
	m_edit_height.EnableWindow(TRUE);
	m_edit_text.EnableWindow(TRUE);
	m_edit_penWidth.EnableWindow(TRUE);
	m_listBox_brushType.EnableWindow(TRUE);
	m_listBox_penType.EnableWindow(TRUE);
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
		m_listBox_brushType.EnableWindow(FALSE);
		m_listBox_penType.EnableWindow(FALSE);
		m_edit_penWidth.EnableWindow(FALSE);
		break;
	}
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
	int oldType = m_Type;
	UpdateData(TRUE);
	m_Type = (ElementType)oldType;
	GetCurShapeValueFromDlg();
	// 从控件中交换数据到值类型数据成员
	// 这里主要是为了刷新当前ComboBox的索引，即 m_Type
	UpdateData(TRUE);
	UpdateUIEnabledStatus();
	// 取当前图元对象的值到对话框的数据成员中
	SetShapeValueToDlg(pShapes[m_Type], true, false, false, true, true, true, false, false, false, false, false);
	// 刷新界面元素
	UpdateData(FALSE);
	m_edit_penColor.Invalidate();
	// 立即发生重绘
	m_edit_penColor.UpdateWindow();
	m_edit_brushColor.Invalidate();
	// 立即发生重绘
	m_edit_brushColor.UpdateWindow();
}

