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
			static PFNGLGENBUFFERSPROC glGenBuffers;
			static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
			static PFNGLBINDBUFFERPROC glBindBuffer;
			static PFNGLBUFFERDATAPROC glBufferData;
			static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
			static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
			static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

			//Shaders
			static PFNGLCREATESHADERPROC glCreateShader;
			static PFNGLDELETESHADERPROC glDeleteShader;
			static PFNGLSHADERSOURCEPROC glShaderSource;
			static PFNGLCOMPILESHADERPROC glCompileShader;
			static PFNGLGETSHADERIVPROC glGetShaderiv;
			static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
			static PFNGLCREATEPROGRAMPROC glCreateProgram;
			static PFNGLDELETEPROGRAMPROC glDeleteProgram;
			static PFNGLATTACHSHADERPROC glAttachShader;
			static PFNGLDETACHSHADERPROC glDetachShader;
			static PFNGLLINKPROGRAMPROC glLinkProgram;
			static PFNGLGETPROGRAMIVPROC glGetProgramiv;
			static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
			static PFNGLUSEPROGRAMPROC glUseProgram;
			static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
			static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		};
	}
}
