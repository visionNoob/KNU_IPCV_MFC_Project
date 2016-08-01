
// 2016SummerMFCImgToolView.cpp : CMy2016SummerMFCImgToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2016SummerMFCImgTool.h"
#endif

#include "2016SummerMFCImgToolDoc.h"
#include "2016SummerMFCImgToolView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2016SummerMFCImgToolView

IMPLEMENT_DYNCREATE(CMy2016SummerMFCImgToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMy2016SummerMFCImgToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2016SummerMFCImgToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CMy2016SummerMFCImgToolView::OnViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CMy2016SummerMFCImgToolView::OnUpdateViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CMy2016SummerMFCImgToolView::OnViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CMy2016SummerMFCImgToolView::OnUpdateViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CMy2016SummerMFCImgToolView::OnViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CMy2016SummerMFCImgToolView::OnUpdateViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CMy2016SummerMFCImgToolView::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CMy2016SummerMFCImgToolView::OnUpdateViewZoom4)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMy2016SummerMFCImgToolView 생성/소멸

CMy2016SummerMFCImgToolView::CMy2016SummerMFCImgToolView()
	: m_nZoom(1)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy2016SummerMFCImgToolView::~CMy2016SummerMFCImgToolView()
{
}

BOOL CMy2016SummerMFCImgToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMy2016SummerMFCImgToolView 그리기

void CMy2016SummerMFCImgToolView::OnDraw(CDC* pDC)
{
	CMy2016SummerMFCImgToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	if (pDoc->m_Dib.IsValid())	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC,0,0,w*m_nZoom,h*m_nZoom);
	}


	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CMy2016SummerMFCImgToolView::SetScrollSizeToFit(){
	
	CSize sizeTotal;
	CMy2016SummerMFCImgToolDoc* pDoc = GetDocument();

	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w*m_nZoom;
		sizeTotal.cy = h*m_nZoom;
	}
	else
	sizeTotal.cx = sizeTotal.cy = 100;


	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}
void CMy2016SummerMFCImgToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizeToFit();


}




// CMy2016SummerMFCImgToolView 인쇄


void CMy2016SummerMFCImgToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2016SummerMFCImgToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy2016SummerMFCImgToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy2016SummerMFCImgToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy2016SummerMFCImgToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2016SummerMFCImgToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2016SummerMFCImgToolView 진단

#ifdef _DEBUG
void CMy2016SummerMFCImgToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy2016SummerMFCImgToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy2016SummerMFCImgToolDoc* CMy2016SummerMFCImgToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2016SummerMFCImgToolDoc)));
	return (CMy2016SummerMFCImgToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2016SummerMFCImgToolView 메시지 처리기


BOOL CMy2016SummerMFCImgToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);
	return TRUE;
}


void CMy2016SummerMFCImgToolView::OnViewZoom1()
{
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(FALSE);
}


void CMy2016SummerMFCImgToolView::OnUpdateViewZoom1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 1);
}


void CMy2016SummerMFCImgToolView::OnViewZoom2()
{
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(FALSE);
}


void CMy2016SummerMFCImgToolView::OnUpdateViewZoom2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 2);
}


void CMy2016SummerMFCImgToolView::OnViewZoom3()
{
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(FALSE);
}


void CMy2016SummerMFCImgToolView::OnUpdateViewZoom3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 3);
}


void CMy2016SummerMFCImgToolView::OnViewZoom4()
{
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(FALSE);
}


void CMy2016SummerMFCImgToolView::OnUpdateViewZoom4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nZoom == 4);
}


void CMy2016SummerMFCImgToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint pt = point + GetScrollPosition();
	pt.x /= m_nZoom;
	pt.y /= m_nZoom;
	ShowImageInfo(pt);
									  
	CScrollView::OnMouseMove(nFlags, point);
}

void CMy2016SummerMFCImgToolView::ShowImageInfo(CPoint point){
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2016SummerMFCImgToolDoc* pDoc = GetDocument();
	int w = pDoc->m_Dib.GetWidth();
	int h = pDoc->m_Dib.GetHeight();
	int c = pDoc->m_Dib.GetPaletteNums();

	CString strText;

	if (point.x >= 0 && point.y >= 0 && point.x < w && point.y < h){
		strText.Format(_T("(%d, %d)"), point.x, point.y);
		pFrame->m_wndStatusBar.SetPaneText(0, strText);
	}

	if (c == 0)
	{
		strText.Format(_T("w:%d h:%d c:16M"), w, h);
	}
	else
		strText.Format(_T("w:%d h:%d c:%d"), w, h, c);

	pFrame->m_wndStatusBar.SetPaneText(1, strText);
}
