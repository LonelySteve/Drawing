
// DrawingView.cpp: CDrawingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawing.h"
#endif

#include "DrawingDoc.h"
#include "DrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShapes
#include "CShapes.h"
// CDrawingView

#include "CShapeDlg.h"

IMPLEMENT_DYNCREATE(CDrawingView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawingView, CScrollView)
// 标准打印命令
ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawingView::OnFilePrintPreview)
ON_WM_RBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawingView 构造/析构

CDrawingView::CDrawingView() noexcept
{
	// TODO: 在此处添加构造代码
}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT &cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CDrawingView 绘图

void CDrawingView::OnDraw(CDC *pDC)
{
	CDrawingDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	for (int i = 0; i < pDoc->m_Elements.GetCount(); i++)
	{
		CShape *p = (CShape *)pDoc->m_Elements[i];
		p->Draw(pDC);
	}
}

void CDrawingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

// CDrawingView 打印

void CDrawingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawingView::OnPreparePrinting(CPrintInfo *pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingView::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

// CDrawingView 诊断

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawingView::Dump(CDumpContext &dc) const
{
	CScrollView::Dump(dc);
}

CDrawingDoc *CDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc *)m_pDocument;
}
#endif //_DEBUG

// CDrawingView 消息处理程序

// 用于安全得到 pDoc 指针以及获取逻辑坐标 pntLogical
#define GET_LOGICAL_POINT_AND_PDOC     \
	CDrawingDoc *pDoc = GetDocument(); \
	ASSERT_VALID(pDoc);                \
	if (!pDoc)                         \
		return;                        \
	CClientDC dc(this);                \
	CPoint pntLogical = point;         \
	OnPrepareDC(&dc);                  \
	dc.DPtoLP(&pntLogical); //DP->LP（设备坐标到逻辑坐标）进行转换

// 左键按下的事件处理程序
// 实现功能：在按住 Ctrl 的前提下，将弹出对话框用以新建图元
void CDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 鼠标消息中，判断鼠标点击时 Ctrl 的按下状态
	if ((nFlags & MK_CONTROL) == MK_CONTROL) //Ctrl键按下
	{
		GET_LOGICAL_POINT_AND_PDOC

		// 默认选择正方形，并传递鼠标坐标
		CSquare sample(pntLogical.x, pntLogical.y, 100);
		// 声明并构造 CShapeDlg 对象
		CShapeDlg dlg(&sample);
		// 弹出对话框，操作结果为 OK 时
		if (dlg.DoModal() == IDOK)
		{
			// 从对话框对象中获取图元对象指针，并通过 CShape::Clone 函数获取一份动态分配内存的拷贝
			CShape *new_pShape = dlg.GetCurShape()->Clone();
			// 将拷贝好的对象指针加入CobArray数组容器
			pDoc->m_Elements.Add(new_pShape);
			// 设置文档已修改标志
			pDoc->SetModifiedFlag();
			// 更新所有视图
			pDoc->UpdateAllViews(NULL);
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

// 左键双击的事件处理程序
// 实现功能：删除当前鼠标指针之处的最上层图元对象
void CDrawingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	GET_LOGICAL_POINT_AND_PDOC

	// 遍历数组对象中每个成员指向的对象
	for (int i = pDoc->m_Elements.GetCount() - 1; i >= 0; i--)
	{
		// 调用当前遍历对象的IsMatched方法判定鼠标坐标是否落在当前图元对象内
		if (((CShape *)pDoc->m_Elements[i])->IsMatched(pntLogical))
		{
			// 释放当前遍历对象
			delete pDoc->m_Elements[i];
			// 从对象数组中移除指向当前遍历对象的指针
			pDoc->m_Elements.RemoveAt(i);
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(NULL);
			break;
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

// 右键双击的事件处理程序
// 实现功能：修改当前鼠标指针之处的最上层图元对象属性
void CDrawingView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	GET_LOGICAL_POINT_AND_PDOC

	for (int i = pDoc->m_Elements.GetCount() - 1; i >= 0; i--)
	{
		if (((CShape *)pDoc->m_Elements[i])->IsMatched(pntLogical))
		{
			CShapeDlg dlg((CShape *)pDoc->m_Elements[i]);
			if (dlg.DoModal() == IDOK)
			{
				// 释放旧的图元对象
				delete pDoc->m_Elements[i];
				// 获取新的图元对象
				CShape *new_pShape = dlg.GetCurShape()->Clone();
				// 将当前遍历的对象指针指向新的图元对象
				pDoc->m_Elements[i] = new_pShape;
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL);
			}
			break;
		}
	}
	CScrollView::OnRButtonDblClk(nFlags, point);
}
