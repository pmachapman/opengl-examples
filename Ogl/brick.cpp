#include "stdafx.h"
#include "glaux.h"

PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLGETUNIFORMLOCATIONPROC getUniLoc;

void init_opengl()
{
	//In an initialization routine
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	getUniLoc = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
}

int installBrickShaders(const GLchar* brickVertex,
	const GLchar* brickFragment)
{
	GLuint brickVS, brickFS, brickProg;   // handles to objects
	GLint  vertCompiled, fragCompiled;    // status values
	GLint  linked;

	// Create a vertex shader object and a fragment shader object

	brickVS = glCreateShader(GL_VERTEX_SHADER);
	brickFS = glCreateShader(GL_FRAGMENT_SHADER);

	// Load source code strings into shaders

	glShaderSource(brickVS, 1, &brickVertex, NULL);
	glShaderSource(brickFS, 1, &brickFragment, NULL);

	// Compile the brick vertex shader, and print out
	// the compiler log file.

	glCompileShader(brickVS);
	glGetShaderiv(brickVS, GL_COMPILE_STATUS, &vertCompiled);

	// Compile the brick vertex shader, and print out
	// the compiler log file.

	glCompileShader(brickFS);
	glGetShaderiv(brickFS, GL_COMPILE_STATUS, &fragCompiled);

	if (!vertCompiled || !fragCompiled)
		return 0;

	// Create a program object and attach the two compiled shaders

	brickProg = glCreateProgram();
	glAttachShader(brickProg, brickVS);
	glAttachShader(brickProg, brickFS);

	// Link the program object and print out the info log

	glLinkProgram(brickProg);
	glGetProgramiv(brickProg, GL_LINK_STATUS, &linked);

	if (!linked)
		return 0;

	// Install program object as part of current state

	glUseProgram(brickProg);

	// Set up initial uniform values

	glUniform3f(getUniLoc(brickProg, "BrickColor"), 1.0, 0.3, 0.2);
	glUniform3f(getUniLoc(brickProg, "MortarColor"), 0.85, 0.86, 0.84);
	glUniform2f(getUniLoc(brickProg, "BrickSize"), 0.30, 0.15);
	glUniform2f(getUniLoc(brickProg, "BrickPct"), 0.90, 0.85);
	glUniform3f(getUniLoc(brickProg, "LightPosition"), 0.0, 0.0, 4.0);

	return 1;
}