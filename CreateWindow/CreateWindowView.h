
// CreateWindowView.h: CCreateWindowView 클래스의 인터페이스
//

#pragma once


class CCreateWindowView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCreateWindowView() noexcept;
	DECLARE_DYNCREATE(CCreateWindowView)

// 특성입니다.
public:
	CCreateWindowDoc* GetDocument() const;

// 작업입니다.
public:
	int x, y, w, h, color;
	CWnd m_wndChild;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCreateWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // CreateWindowView.cpp의 디버그 버전
inline CCreateWindowDoc* CCreateWindowView::GetDocument() const
   { return reinterpret_cast<CCreateWindowDoc*>(m_pDocument); }
#endif

