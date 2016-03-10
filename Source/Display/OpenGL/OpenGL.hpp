#pragma once
#include "opengl.org/glcorearb.h"

namespace Galatea
{
	namespace Display
	{
		namespace OpenGL
		{
			typedef void*(*GetProcFunc)(const char*);
			void InitializeExtensions(GetProcFunc get_proc_func);

			//Vertex Buffers
			extern PFNGLGENBUFFERSPROC glGenBuffers;
			extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
			extern PFNGLBINDBUFFERPROC glBindBuffer;
			extern PFNGLBUFFERDATAPROC glBufferData;
			extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
			extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
			extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

			//Shaders
			extern PFNGLCREATESHADERPROC glCreateShader;
			extern PFNGLDELETESHADERPROC glDeleteShader;
			extern PFNGLSHADERSOURCEPROC glShaderSource;
			extern PFNGLCOMPILESHADERPROC glCompileShader;
			extern PFNGLGETSHADERIVPROC glGetShaderiv;
			extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
			extern PFNGLCREATEPROGRAMPROC glCreateProgram;
			extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
			extern PFNGLATTACHSHADERPROC glAttachShader;
			extern PFNGLDETACHSHADERPROC glDetachShader;
			extern PFNGLLINKPROGRAMPROC glLinkProgram;
			extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
			extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
			extern PFNGLUSEPROGRAMPROC glUseProgram;
			extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
			extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		};
	}
}
