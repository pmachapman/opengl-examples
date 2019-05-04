#pragma once
#include "stdafx.h"
#include "glext.h"

typedef char GLchar;

void auxWireTeapot(GLdouble);
void auxSolidTeapot(GLdouble);
int installBrickShaders(const GLchar* brickVertex, const GLchar* brickFragment);

void init_opengl();