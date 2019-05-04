
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

	void DrawBox(GLfloat x, GLfloat y, GLfloat z);
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
private:
	const char* brickVertex =
	"uniform vec3 LightPosition;\
	\
	const float SpecularContribution = 0.3;\
	const float DiffuseContribution = 1.0 - SpecularContribution;\
\
	varying float LightIntensity;\
	varying vec2  MCposition;\
\
	void main(void)\
	{\
		vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);\
		vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);\
		vec3 lightVec = normalize(LightPosition - ecPosition);\
		vec3 reflectVec = reflect(-lightVec, tnorm);\
		vec3 viewVec = normalize(-ecPosition);\
		float diffuse = max(dot(lightVec, tnorm), 0.0);\
		float spec = 0.0;\
\
		if (diffuse > 0.0)\
		{\
			spec = max(dot(reflectVec, viewVec), 0.0);\
			spec = pow(spec, 16.0);\
		}\
\
		LightIntensity = DiffuseContribution * diffuse +\
			SpecularContribution * spec;\
\
		MCposition = gl_Vertex.xy;\
		gl_Position = ftransform();\
	}";
	const char* brickFragment =
	"uniform vec3  BrickColor, MortarColor;\
	uniform vec2  BrickSize;\
	uniform vec2  BrickPct;\
\
	varying vec2  MCposition;\
	varying float LightIntensity;\
\
	void main(void)\
	{\
		vec3  color;\
		vec2  position, useBrick;\
\
		position = MCposition / BrickSize;\
\
		if (fract(position.y * 0.5) > 0.5)\
			position.x += 0.5;\
\
		position = fract(position);\
\
		useBrick = step(position, BrickPct);\
\
		color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);\
		color *= LightIntensity;\
		gl_FragColor = vec4(color, 1.0);\
	}";
};

#ifndef _DEBUG  // debug version in OglView.cpp
inline COglDoc* COglView::GetDocument() const
   { return reinterpret_cast<COglDoc*>(m_pDocument); }
#endif

