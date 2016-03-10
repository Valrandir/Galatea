#include "../../Types.hpp"
#include "OpenGL.hpp"

namespace Galatea
{
	namespace Display
	{
		namespace OpenGL
		{
			void InitializeExtensions(GetProcFunc get_proc_func)
			{
				static bool is_initialized = false;

				if(is_initialized)
					return;

				#define GL_GETPROC(type, name) name = (type)(get_proc_func(#name))

				//Vertex Buffers
				GL_GETPROC(PFNGLGENBUFFERSPROC, glGenBuffers);
				GL_GETPROC(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
				GL_GETPROC(PFNGLBINDBUFFERPROC, glBindBuffer);
				GL_GETPROC(PFNGLBUFFERDATAPROC, glBufferData);
				GL_GETPROC(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
				GL_GETPROC(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
				GL_GETPROC(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);

				//Shaders
				GL_GETPROC(PFNGLCREATESHADERPROC, glCreateShader);
				GL_GETPROC(PFNGLDELETESHADERPROC, glDeleteShader);
				GL_GETPROC(PFNGLSHADERSOURCEPROC, glShaderSource);
				GL_GETPROC(PFNGLCOMPILESHADERPROC, glCompileShader);
				GL_GETPROC(PFNGLGETSHADERIVPROC, glGetShaderiv);
				GL_GETPROC(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
				GL_GETPROC(PFNGLCREATEPROGRAMPROC, glCreateProgram);
				GL_GETPROC(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
				GL_GETPROC(PFNGLATTACHSHADERPROC, glAttachShader);
				GL_GETPROC(PFNGLDETACHSHADERPROC, glDetachShader);
				GL_GETPROC(PFNGLLINKPROGRAMPROC, glLinkProgram);
				GL_GETPROC(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
				GL_GETPROC(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
				GL_GETPROC(PFNGLUSEPROGRAMPROC, glUseProgram);
				GL_GETPROC(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
				GL_GETPROC(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);

				is_initialized = true;
			}
		}

	}
}
