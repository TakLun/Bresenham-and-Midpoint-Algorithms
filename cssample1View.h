// cssample1View.h : interface of the CCssample1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_)
#define AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample1View : public CView
{
protected: // create from serialization only
	CCssample1View();
	DECLARE_DYNCREATE(CCssample1View)

// Attributes
public:
	CCssample1Doc* GetDocument();

// Operations
public:
	int height;
	int width;
	bool LmouseDown;
	bool RmouseDown;
	CPoint tracking;
	CPoint current;
	CPoint start;
//	void Init();

	//0 : OpenGL
	//1 : Bresenham Algorithm
	//2 : Midpoint Algorithm
	int implementationFlag;

	HDC m_hDC;
	HGLRC m_hGLContext;
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;


	void OpenGL();
	void BresenhamAlgorithm(int x1, int y1, int x2, int y2);
	void MidpointAlgorithm(int x1, int y1, int x2, int y2);

	void BresenhamWake();
	void MidpointWake();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCssample1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL dblBuf;
	CPoint m_LDownPos;
	CPoint m_RPos;
	CPoint m_RPos2;
	bool refresh;
	virtual ~CCssample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCssample1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblBuf();
	afx_msg void OnNoDblBuf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenglWake();
	afx_msg void OnBresenhamalgorithmWake();
	afx_msg void OnDrawWake();
	afx_msg void OnMidpointalgorithmLinedraw();
	afx_msg void OnNextPane();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in cssample1View.cpp
inline CCssample1Doc* CCssample1View::GetDocument()
   { return (CCssample1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSsample1VIEW_H__C6C32F57_5FBE_4F63_841C_74E2F1DDEDF4__INCLUDED_)
