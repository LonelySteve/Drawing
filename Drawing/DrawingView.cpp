
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


// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDrawingView 构造/析构

CDrawingView::CDrawingView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CDrawingView 绘图

void CDrawingView::OnDraw(CDC* /*pDC*/)
{
	CDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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

BOOL CDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDrawingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDrawingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawingView 诊断

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawingDoc* CDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingView 消息处理程序
