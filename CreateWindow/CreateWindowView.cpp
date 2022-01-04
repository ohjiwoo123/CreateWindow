
// CreateWindowView.cpp: CCreateWindowView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CreateWindow.h"
#endif

#include "CreateWindowDoc.h"
#include "CreateWindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreateWindowView

IMPLEMENT_DYNCREATE(CCreateWindowView, CView)

BEGIN_MESSAGE_MAP(CCreateWindowView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CCreateWindowView 생성/소멸

CCreateWindowView::CCreateWindowView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCreateWindowView::~CCreateWindowView()
{
}

BOOL CCreateWindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCreateWindowView 그리기

void CCreateWindowView::OnDraw(CDC* /*pDC*/)
{
	CCreateWindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCreateWindowView 인쇄

BOOL CCreateWindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCreateWindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCreateWindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCreateWindowView 진단

#ifdef _DEBUG
void CCreateWindowView::AssertValid() const
{
	CView::AssertValid();
}

void CCreateWindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCreateWindowDoc* CCreateWindowView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCreateWindowDoc)));
	return (CCreateWindowDoc*)m_pDocument;
}
#endif //_DEBUG


// CCreateWindowView 메시지 처리기


int CCreateWindowView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndChild.Create(_T("BUTTON"), _T("눌러봐"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(30,30,150,150),this, 1234);
	return 0;
}


void CCreateWindowView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 1. 버튼의 위치를 구한다
	CRect rectChild; // 지역변수
	// this = View 
	this->m_wndChild.GetWindowRect(&rectChild);

	int x = rectChild.left;
	int y = rectChild.top;
	int w = rectChild.Width();
	int h = rectChild.Height();
	// 2. 그 위치에서 -/+ 10씩 계산한다.
	/*x = x + 10;
	y = y + 10;*/
	// 3. 버튼을 새로운 위치에 놓는다.
	//SetWindowPos();
	//SetWindowPos();
	//AfxMessageBox(_T("안녕"));

	
	// SetWindowPos();
	CView::OnLButtonDown(nFlags, point);
}


void CCreateWindowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 1. 버튼의 위치를 구한다
	CRect rectChild; // 지역변수
	// this = View 
	// 스크린 좌표 
	m_wndChild.GetWindowRect(&rectChild);
	// 클라이언트 좌표 
	ScreenToClient(&rectChild);

	int x = rectChild.left;
	int y = rectChild.top;
	int w = rectChild.Width();
	int h = rectChild.Height();

	// 2. 그 위치에서 -/+ 10씩 계산한다.
	if (nChar == VK_LEFT) {
		x = x - 10;
		w = w - 10;
	}
	else if (nChar == VK_RIGHT) {
		x = x + 10;
		w = w + 10;
	}

	// 3. 버튼을 새로운 위치에 놓는다.
	m_wndChild.SetWindowPos(NULL, x, y, w, h, SWP_SHOWWINDOW|SWP_NOZORDER);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCreateWindowView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	strTemp.Format(_T("눌린키: %d,%c"),nChar,nChar);
	// AfxMessageBox(strTemp);
	m_wndChild.SetWindowText(strTemp); // 버튼 
	this->SetWindowText(strTemp); // 뷰 , this = CCreateWindowView
	AfxGetMainWnd()->SetWindowText(strTemp); // 액자 

	CView::OnChar(nChar, nRepCnt, nFlags);
}
