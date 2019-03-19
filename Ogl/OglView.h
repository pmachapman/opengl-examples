
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

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OglView.cpp
inline COglDoc* COglView::GetDocument() const
   { return reinterpret_cast<COglDoc*>(m_pDocument); }
#endif

