
// OglView.h : interface of the COglView class
//

#pragma once


class COglView : public CView
{
protected: // create from serialization only
	COglView() noexcept;
	DECLARE_DYNCREATE(COglView)

// Attributes
public:
	COglDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~COglView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_pixelformat;
	HGLRC m_hglRendContext;

	GLfloat vdColor1[3];
	GLfloat vdColor2[3];
	GLfloat vdColor3[3];
	GLfloat vdColor4[3];
	GLfloat vdColor5[3];
	GLfloat vdColor6[3];
	GLfloat vdColor7[3];
	GLfloat vdColor8[3];

	GLfloat *clrArray[8];

	GLdouble theta;

	BOOL InitPixelFormat(HDC hDC);
	void InitPFDStruct(PIXELFORMATDESCRIPTOR *ppfd);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in OglView.cpp
inline COglDoc* COglView::GetDocument() const
   { return reinterpret_cast<COglDoc*>(m_pDocument); }
#endif

