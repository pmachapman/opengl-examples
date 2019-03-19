
// OglView.cpp : implementation of the COglView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ogl.h"
#endif

#include "OglDoc.h"
#include "OglView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COglView

IMPLEMENT_DYNCREATE(COglView, CView)

BEGIN_MESSAGE_MAP(COglView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COglView construction/destruction

COglView::COglView() noexcept
{
	// TODO: add construction code here
	m_pixelformat = 0;
	m_hglRendContext = NULL;
	theta = 5.0;

	vdColor1[0] = 1.0;
	vdColor1[1] = 0.0;
	vdColor1[2] = 0.0;
	vdColor2[0] = 0.0;
	vdColor2[1] = 1.0;
	vdColor2[2] = 0.0;
	vdColor3[0] = 1.0;
	vdColor3[1] = 1.0;
	vdColor3[2] = 0.0;
	vdColor4[0] = 0.0;
	vdColor4[1] = 1.0;
	vdColor4[2] = 1.0;
	vdColor5[0] = 1.0;
	vdColor5[1] = 0.0;
	vdColor5[2] = 1.0;
	vdColor6[0] = 0.0;
	vdColor6[1] = 0.0;
	vdColor6[2] = 1.0;
	vdColor7[0] = 1.0;
	vdColor7[1] = 1.0;
	vdColor7[2] = 1.0;
	vdColor8[0] = 0.0;
	vdColor8[1] = 0.0;
	vdColor8[2] = 0.0;

	clrArray[0] = vdColor1;
	clrArray[1] = vdColor2;
	clrArray[2] = vdColor3;
	clrArray[3] = vdColor4;
	clrArray[4] = vdColor5;
	clrArray[5] = vdColor6;
	clrArray[6] = vdColor7;
	clrArray[7] = vdColor8;
}

COglView::~COglView()
{
}

BOOL COglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

// COglView drawing

void COglView::OnDraw(CDC* /*pDC*/)
{
	COglDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// COglView diagnostics

#ifdef _DEBUG
void COglView::AssertValid() const
{
	CView::AssertValid();
}

void COglView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COglDoc* COglView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COglDoc)));
	return (COglDoc*)m_pDocument;
}
#endif //_DEBUG

// COglView message handlers

int COglView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	HDC hDC = ::GetDC(GetSafeHwnd());
	if (InitPixelFormat(hDC) == FALSE)
		return 0;
	m_hglRendContext = wglCreateContext(hDC);
	wglMakeCurrent(hDC, m_hglRendContext);
	return 0;
}

void COglView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	HGLRC hRC;

	hRC = ::wglGetCurrentContext();
	::wglMakeCurrent(NULL, NULL);
	if (hRC)
	{
		::wglDeleteContext(hRC);
	}
}

void COglView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GLfloat *glfTemp;
	glfTemp = clrArray[0];
	for (int j = 0; j < 7; j++)
	{
		clrArray[j] = clrArray[j + 1];
	}

	clrArray[7] = glfTemp;
	theta += 5.0;
	Invalidate(FALSE);

	CView::OnMouseMove(nFlags, point);
}

void COglView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		glRotated(theta, 0.0, 0.0, 1.0);
		//glTranslated(100.0, 100.0, 0);
		glBegin(GL_POLYGON);
			glColor3fv(clrArray[0]);
			glVertex2f(20.0f, 20.0f);
			glColor3fv(clrArray[1]);
			glVertex2f(175.0f, 20.0f);
			glColor3fv(clrArray[2]);
			glVertex2f(90.0f, 200.0f);
		glEnd();
	glPopMatrix();
	glBegin(GL_POLYGON);
		glColor3fv(clrArray[3]);
		glVertex2f(250.0f, 20.0f);
		glColor3fv(clrArray[4]);
		glVertex2f(400.0f, 20.0f);
		glColor3fv(clrArray[5]);
		glVertex2f(400.0f, 220.0f);
		glColor3fv(clrArray[6]);
		glVertex2f(250.0f, 220.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3fv(clrArray[7]);
		glVertex2f(150.0f, 250.0f);
		glColor3fv(clrArray[0]);
		glVertex2f(350.0f, 250.0f);
		glColor3fv(clrArray[1]);
		glVertex2f(400.0f, 375.0f);
		glColor3fv(clrArray[2]);
		glVertex2f(250.0f, 450.0f);
		glColor3fv(clrArray[3]);
		glVertex2f(100.0f, 375.0f);
	glEnd();
	glFlush();
#if 1
	SwapBuffers(wglGetCurrentDC());
#endif;
	// Do not call CView::OnPaint() for painting messages
}

void COglView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	glViewport(0, 0, cx, cy);
	if (cy == 0)
	{
		cy = 1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)500.0*(cx / cy), 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_BACK);
}

// COglView custom methods

BOOL COglView::InitPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR PixForDesc;

	InitPFDStruct(&PixForDesc);
	m_pixelformat = ChoosePixelFormat(hDC, &PixForDesc);
	if (m_pixelformat == 0)
	{
		m_pixelformat = 1;
		if (DescribePixelFormat(hDC, m_pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &PixForDesc) == 0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(hDC, m_pixelformat, &PixForDesc) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

void COglView::InitPFDStruct(PIXELFORMATDESCRIPTOR * ppfd)
{
	memset(ppfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
#if 1
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
#else
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_BITMAP;
#endif
	ppfd->iPixelType = PFD_TYPE_RGBA;
	ppfd->cColorBits = 24;
	ppfd->cDepthBits = 16;
	ppfd->iLayerType = PFD_MAIN_PLANE;
}
