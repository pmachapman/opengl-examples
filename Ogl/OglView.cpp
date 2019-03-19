
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
END_MESSAGE_MAP()

// COglView construction/destruction

COglView::COglView() noexcept
{
	// TODO: add construction code here

}

COglView::~COglView()
{
}

BOOL COglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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
