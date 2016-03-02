#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "opengl.org/glcorearb.h"
#include "opengl.org/glext.h"
#include "opengl.org/wglext.h"

namespace Galatea
{
	namespace Display
	{
		class GLExt
		{
			private:
			GLExt();

			public:
			static const GLExt* Create();
			virtual ~GLExt();

			//Initialization
			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

			//Vertex Buffers
			PFNGLGENBUFFERSPROC glGenBuffers;
			PFNGLDELETEBUFFERSPROC glDeleteBuffers;
			PFNGLBINDBUFFERPROC glBindBuffer;
			PFNGLBUFFERDATAPROC glBufferData;
			PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
			PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
			PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

			//Shaders
			PFNGLCREATESHADERPROC glCreateShader;
			PFNGLDELETESHADERPROC glDeleteShader;
			PFNGLSHADERSOURCEPROC glShaderSource;
			PFNGLCOMPILESHADERPROC glCompileShader;
			PFNGLGETSHADERIVPROC glGetShaderiv;
			PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
			PFNGLCREATEPROGRAMPROC glCreateProgram;
			PFNGLDELETEPROGRAMPROC glDeleteProgram;
			PFNGLATTACHSHADERPROC glAttachShader;
			PFNGLDETACHSHADERPROC glDetachShader;
			PFNGLLINKPROGRAMPROC glLinkProgram;
			PFNGLGETPROGRAMIVPROC glGetProgramiv;
			PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
			PFNGLUSEPROGRAMPROC glUseProgram;
			PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
			PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		};
	}
}
