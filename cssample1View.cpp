// cssample1View.cpp : implementation of the CCssample1View class
//

#include "stdafx.h"
#include "cssample1.h"

#include "cssample1Doc.h"
#include "cssample1View.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample1View

IMPLEMENT_DYNCREATE(CCssample1View, CView)

BEGIN_MESSAGE_MAP(CCssample1View, CView)
	//{{AFX_MSG_MAP(CCssample1View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_DBL_BUF, OnDblBuf)
	ON_COMMAND(ID_NO_DBL_BUF, OnNoDblBuf)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPENGL_WAKE, &CCssample1View::OnOpenglWake)
	ON_COMMAND(ID_BRESENHAMALGORITHM_WAKE, &CCssample1View::OnBresenhamalgorithmWake)
//	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_WAKE, &CCssample1View::OnDrawWake)
	ON_COMMAND(ID_MIDPOINTALGORITHM_LINEDRAW, &CCssample1View::OnMidpointalgorithmLinedraw)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample1View construction/destruction

CCssample1View::CCssample1View()
{
	LmouseDown=false;
	RmouseDown=false;
	refresh = false;
	width=0; height=0;
	dblBuf=true;
	implementationFlag = -1;
}

CCssample1View::~CCssample1View()
{
}

BOOL CCssample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View drawing

void CCssample1View::OnDraw(CDC* pDC)
{
	CCssample1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	width=rcClient.Width();
	height=rcClient.Height();
    
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Clear buffer content, so that no old content remains in the buffer
	//glClear(GL_COLOR_BUFFER_BIT);
	
	
	// for double buffering
	//if(dblBuf)
	//	glDrawBuffer(GL_BACK);
	//else
		glDrawBuffer(GL_FRONT_AND_BACK);

	wglMakeCurrent(m_hDC,m_hGLContext);


    //Add your own stuff here for OpenGL related operations  
	/*
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex3d(start.x, height-start.y, 0);
		glVertex3d(m_LDownPos.x, height-m_LDownPos.y, 0);
	glEnd();
	glFlush();
	glPopMatrix();
	*/

	//My Draw Code Implementation
	if(implementationFlag == 0){
		glLineStipple(1,0x3FFF);
		glEnable(GL_LINE_STIPPLE); 
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		glBegin(GL_LINES);
			OpenGL();	
		glEnd();
		glFlush();
		glPopMatrix();

		wglMakeCurrent(m_hDC,NULL);
		wglMakeCurrent(m_hDC, m_hGLContext);

		::SwapBuffers(m_hDC);
	}

	if(implementationFlag == 1){
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		glBegin(GL_POINTS);
			BresenhamWake();
		glEnd();
		glFlush();
		glPopMatrix();

		wglMakeCurrent(m_hDC,NULL);
		wglMakeCurrent(m_hDC, m_hGLContext);

		::SwapBuffers(m_hDC);

	}

	if(implementationFlag == 2){

		glColor4f(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		glBegin(GL_POINTS);
			MidpointAlgorithm(m_RPos.x, height-m_RPos.y, m_RPos2.x, height-m_RPos2.y);
		glEnd();
		glFlush();
		glPopMatrix();

		wglMakeCurrent(m_hDC,NULL);
		wglMakeCurrent(m_hDC, m_hGLContext);

		::SwapBuffers(m_hDC);
	}

	if(implementationFlag == 3){
		glColor4f(1.0, 1.0, 1.0, 0.0);
		glPushMatrix();
		glBegin(GL_LINES);
			OpenGL();	
		glEnd();
		glBegin(GL_POINTS); 
			BresenhamWake();
		glEnd();
		glFlush();
		glPopMatrix();

		wglMakeCurrent(m_hDC,NULL);
		wglMakeCurrent(m_hDC, m_hGLContext);

		::SwapBuffers(m_hDC);
	}

	wglMakeCurrent(m_hDC,NULL);
	wglMakeCurrent(m_hDC, m_hGLContext);

	::SwapBuffers(m_hDC);
       
}

//Algorithms
void CCssample1View::OpenGL(){
		
	//W
	glVertex3d(800, 200, 0.0);
	glVertex3d(825, 100, 0);

	glVertex3d(825, 100, 0.0);
	glVertex3d(850, 200, 0);

	glVertex3d(850, 200, 0.0);
	glVertex3d(875, 100, 0);

	glVertex3d(875, 100, 0.0);
	glVertex3d(900, 200, 0);

	//A
	glVertex3d(900, 100, 0.0);
	glVertex3d(925, 200, 0);

	glVertex3d(925, 200, 0.0);
	glVertex3d(950, 100, 0);

	glVertex3d((900+925)/2, 150, 0.0);
	glVertex3d((925+950)/2, 150, 0);

	//K
	glVertex3d(953, 200, 0.0);
	glVertex3d(953, 100, 0);

	glVertex3d(997, 200, 0.0);
	glVertex3d(953, 150, 0);

	glVertex3d(953, 150, 0.0);
	glVertex3d(997, 100, 0);

	//E
	glVertex3d(1005, 200, 0.0);
	glVertex3d(1005, 100, 0);

	glVertex3d(1005, 200, 0.0);
	glVertex3d(1040, 200, 0);

	glVertex3d(1005, 150, 0.0);
	glVertex3d(1040, 150, 0);

	glVertex3d(1005, 100, 0.0);
	glVertex3d(1040, 100, 0);

}

void CCssample1View::MidpointAlgorithm(int x1, int y1, int x2, int y2){
	
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x = x1;
	int y = y1;

	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if(dx<0) 
		dx1 = -1; 
	else if(dx>0) 
		dx1 = 1;

	if(dy<0)
		dy1 = -1;
	else if(dy>0) 
		dy1 = 1;

	int longest_len, shortest_len;
	if(abs(dx)>abs(dy)){
		longest_len = abs(dx);
		shortest_len = abs(dy);

		if(dx<0) 
			dx2 = -1; 
		else if(dx>0) 
			dx2 = 1;
	}else{
		longest_len = abs(dy);
		shortest_len = abs(dx);

		if(dy<0)
			dy2 = -1;
		else if(dy>0) 
			dy2 = 1;

	}
	int d = longest_len/2;

	for(int i=0;i<longest_len;i++){
		
		glVertex2i(x, y);
		d = d + shortest_len;
		if(d < longest_len){
			x=x+dx2;
			y=y+dy2;
		}else{
			d = d - longest_len;
			x=x+dx1;
			y=y+dy1;
		}

	}
}

void CCssample1View::BresenhamAlgorithm(int x1, int y1, int x2, int y2){

	int inc_y;

	bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if(steep){
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if(x1 > x2){
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	int dx = x2 - x1;
	int dy = abs(y2 - y1);

	int d = dx / 2;
	if(y1<y2)
		inc_y = 1;
	else
		inc_y=-1;

	int y = y1;

	int longest = x2;

	for(int x=(int)x1; x<longest; x++)
	{
		if(steep)
		{
			glVertex2i(y, x);
		}
		else
		{
			glVertex2i(x, y);
		}
 		d = d-dy;
		if(d < 0)
		{
			y = y+inc_y;
			d = d+dx;
		}
	}
}

void CCssample1View::BresenhamWake(){

		//XYZ
		BresenhamAlgorithm(500, 100, 500, 400);
		BresenhamAlgorithm(500, 100, 50, 5);
		BresenhamAlgorithm(500, 100, 1100, 100);

		//W
		BresenhamAlgorithm(3, 200, 25, 100);
		BresenhamAlgorithm(25, 100, 50, 200);
		BresenhamAlgorithm(50, 200, 75, 100);
		BresenhamAlgorithm(75, 100, 100, 200);

		//A
		BresenhamAlgorithm(100, 100, 125, 200);
		BresenhamAlgorithm(125, 200, 150, 100);
		BresenhamAlgorithm((100+125)/2, 150, (125+150)/2, 150);

		//K
		BresenhamAlgorithm(153, 200, 153, 100);
		BresenhamAlgorithm(197, 200, 153, 150);
		BresenhamAlgorithm(153, 150, 197, 100);

		//E
		BresenhamAlgorithm(205, 200, 205, 100);
		BresenhamAlgorithm(205, 200, 240, 200);
		BresenhamAlgorithm(205, 150, 240, 150);
		BresenhamAlgorithm(205, 100, 240, 100);
}

void CCssample1View::OnOpenglWake()
{
	// TODO: Add your command handler code here
	implementationFlag = 0;
}


void CCssample1View::OnBresenhamalgorithmWake()
{
	// TODO: Add your command handler code here
	implementationFlag = 1;
}

void CCssample1View::OnDrawWake()
{
	// TODO: Add your command handler code here
	implementationFlag = 3;
}

void CCssample1View::OnMidpointalgorithmLinedraw()
{
	// TODO: Add your command handler code here
	implementationFlag = 2;
}
/////////////////////////////////////////////////////////////////////////////
// CCssample1View printing

BOOL CCssample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCssample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCssample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View diagnostics

#ifdef _DEBUG
void CCssample1View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample1Doc* CCssample1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample1Doc)));
	return (CCssample1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample1View message handlers

BOOL CCssample1View::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion	= 1;
	/***************
	pixelDesc.dwFlags=PFD_DRAW_TO_WINDOW | 
					PFD_DRAW_TO_BITMAP | 
					PFD_SUPPORT_OPENGL | 
					PFD_SUPPORT_GDI | 
					PFD_STEREO_DONTCARE;
	*********************/
	//Stuff with double buffering
    pixelDesc.dwFlags =    PFD_DRAW_TO_WINDOW | 
                PFD_SUPPORT_OPENGL | 
                PFD_DOUBLEBUFFER | //set as a double buffer mode. (otherwise, single buffer mode)
                PFD_STEREO_DONTCARE;  
	
	pixelDesc.iPixelType	= PFD_TYPE_RGBA;
	pixelDesc.cColorBits	= 32;
	pixelDesc.cRedBits		= 8;
	pixelDesc.cRedShift		= 16;
	pixelDesc.cGreenBits	= 8;
	pixelDesc.cGreenShift	= 8;
	pixelDesc.cBlueBits		= 8;
	pixelDesc.cBlueShift	= 0;
	pixelDesc.cAlphaBits	= 0;
	pixelDesc.cAlphaShift	= 0;
	pixelDesc.cAccumBits	= 64;	
	pixelDesc.cAccumRedBits	= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved			= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;

	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCssample1View::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(m_hDC);
    if (m_hGLContext == NULL)
    {
        return FALSE;
    }

    if (wglMakeCurrent(m_hDC, m_hGLContext)==FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

int CCssample1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
    m_hDC = ::GetDC(hWnd);

    if (SetWindowPixelFormat(m_hDC)==FALSE)
        return 0;
    if (CreateViewGLContext(m_hDC)==FALSE)
        return 0;
	return 0;
}

void CCssample1View::OnDestroy() 
{
	CView::OnDestroy();
	
	if(wglGetCurrentContext()!=NULL) 
    {
        // make the rendering context not current
        wglMakeCurrent(NULL, NULL) ;
    }
    
    if (m_hGLContext!=NULL)
    {
        wglDeleteContext(m_hGLContext);
        m_hGLContext = NULL;
    }

    // Now the associated DC can be released.
    CView::OnDestroy(); 	
}

void CCssample1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LmouseDown = TRUE;
	m_LDownPos = point;
	m_RPos = point;
	glClear(GL_COLOR_BUFFER_BIT);
	//CView::OnLButtonDown(nFlags, point);
}

void CCssample1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LmouseDown=false;
	//one line has drawn, clear everything
	CView::OnLButtonUp(nFlags, point);
}

void CCssample1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (LmouseDown)
	{
		start=m_LDownPos;
		m_LDownPos = point;
		InvalidateRect(NULL, FALSE);
	}
	m_RPos2= point;

	CView::OnMouseMove(nFlags, point);
}

void CCssample1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
    glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// for double buffering
	glDrawBuffer(GL_BACK);
	
}

void CCssample1View::OnDblBuf() 
{
	dblBuf=true;	
}

void CCssample1View::OnNoDblBuf() 
{
	dblBuf=false;	
}

void CCssample1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_RPos = m_RPos2;
	m_RPos2 = point;
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
}


void CCssample1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	RmouseDown = FALSE;
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonUp(nFlags, point);
}
