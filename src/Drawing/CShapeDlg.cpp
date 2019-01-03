// CShapeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Drawing.h"
#include "afxdialogex.h"
#include "CShapeDlg.h"
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
#define NEW_SHAPE(index,className) PTR_VAL_ASSIGN(pShapes[index],new className())

	NEW_SHAPE(0, CSquare);
	NEW_SHAPE(1, CRectangle);
	NEW_SHAPE(2, CCircle);
	NEW_SHAPE(3, CEllipse);
	NEW_SHAPE(4, CTriangle);
	NEW_SHAPE(5, CText);

	if (pShape != NULL)    // 这个时候是修改图元对象
	{
		ElementType type = pShape->GetShapeType();
		delete pShapes[type];
		// 调用CShape的动态内存拷贝函数拷贝源指针指向的对象
		pShapes[type] = CShape::DynamicCShapeObj(pShape);
	}
	else
	{
		pShape = pShapes[m_Type];
	}
	// 更新值类型数据成员
	SetShapeValueToDlg(pShape);
	// 更新UI启用状态
	UpdateUIEnabledStatus();

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
	int orgX = this->m_x, orgY = this->m_y,
		height = this->m_h, widthEtc = this->m_wra,
		penWidth = this->m_w, penType = this->m_pen_type,
		brushType = this->m_brush_type;

	shape->GetPen(&penColor, &penWidth, &penType);
	shape->GetBrush(&brushColor, &brushType);
	shape->GetShapeValue(&type, &orgX, &orgY, &widthEtc, &text, &height);

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

	int id = pWnd->GetDlgCtrlID();
	if (id == IDC_EDIT7)
	{
		return CreateSolidBrush(m_pen_color);
	}
	else if (id == IDC_EDIT8)
	{
		return CreateSolidBrush(m_brush_color);
	}
	return hbr;
}

CShape* CShapeDlg::GetCurShapeValueFromDlg()
{
	pShapes[m_Type]->SetBrush(m_brush_color, m_brush_type);
	pShapes[m_Type]->SetPen(m_pen_color, m_w, m_pen_type);
	pShapes[m_Type]->SetShapeValue(m_x, m_y, m_wra, m_text, m_h);

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
#pragma region 储存索引变化前的图元类型对象信息
	// 临时储存一下旧的图元类型指示值
	ElementType oldType = m_Type;
	// 更新数据到数据成员
	UpdateData(TRUE);
	// 临时储存一下新的图元类型指示值
	ElementType newType = m_Type;
	// 让当前图元值类型指示值临时赋值为旧的图元类型
	m_Type = oldType;
	// 将索引变化之前的数据储存至对应类型的图元对象中
	GetCurShapeValueFromDlg();
#pragma endregion
#pragma region 更新控件状态或值
	// 恢复当前图元类型指示值
	m_Type = newType;
	// 更改相应的UI启用状态
	UpdateUIEnabledStatus();
	// 更新当前图元对象的值到对话框的数据成员中（仅更新图元类型，宽度等，高度以及文字属性）
	SetShapeValueToDlg(pShapes[m_Type], true, false, false, true, true, true, false, false, false, false, false);
	// 刷新界面元素
	UpdateData(FALSE);
	// 重绘用于呈现颜色的编辑框
	m_edit_penColor.Invalidate();
	m_edit_penColor.UpdateWindow();
	m_edit_brushColor.Invalidate();
	m_edit_brushColor.UpdateWindow();
#pragma endregion
}

