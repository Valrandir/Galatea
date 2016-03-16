#include "../../Assert/Assert.hpp"
#include "OpenGL.hpp"
#include "WindowGL.hpp"
#include "Matrix4.hpp"

namespace Galatea
{
	namespace Display
	{
		namespace OpenGL
		{
			#include <gl/GL.h>

			GLuint create_shader(GLenum type, const char* shader_code)
			{
				GLuint shader_id = glCreateShader(type);
				glShaderSource(shader_id, 1, &shader_code, NULL);
				glCompileShader(shader_id);
				GLint info_log_length;
				glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
				if(info_log_length > 1)
				{
					GLsizei length;
					GLchar* buffer = new GLchar[info_log_length];
					glGetShaderInfoLog(shader_id, info_log_length, &length, buffer);
					String msg = String::ToCStr(buffer).get();
					delete buffer;
					ASSERT_MSG(info_log_length == 0, msg);
				}

				return shader_id;
			}

			void destroy_shader(GLuint shader_id)
			{
				glDeleteShader(shader_id);
			}

			GLuint create_program(const GLuint* vec_shader_id, int count)
			{
				const GLuint* it, *end = vec_shader_id + count;

				GLuint program_id = glCreateProgram();

				it = vec_shader_id;
				while(it < end)
					glAttachShader(program_id, *it++);

				glLinkProgram(program_id);

				GLint info_log_length;
				glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
				if(info_log_length > 1)
				{
					GLsizei length;
					GLchar* buffer = new GLchar[info_log_length];
					glGetProgramInfoLog(program_id, info_log_length, &length, buffer);
					String msg = String::ToCStr(buffer).get();
					delete buffer;
					ASSERT_MSG(info_log_length == 0, msg);
				}

				it = vec_shader_id;
				while(it < end)
					glDetachShader(program_id, *it++);

				return program_id;
			}

			void destroy_program(GLuint program_id)
			{
				glDeleteProgram(program_id);
			}

			GLuint shaders_init()
			{
				GLuint idv[] =
				{
					create_shader
					(
						GL_VERTEX_SHADER,
						"#version 330 core\n"
						"in vec3 in_vec;"
						"in vec3 in_color;"
						"in vec2 in_tex_coord;"
						"out vec3 color;"
						"out vec2 tex_coord;"
						"uniform mat4 mat_transformation;"
						"void main()"
						"{"
						"	gl_Position = vec4(in_vec, 1) * mat_transformation;"
						"	color = in_color;"
						"	tex_coord = in_tex_coord;"
						"}"
						),
					create_shader
					(
						GL_FRAGMENT_SHADER,
						"#version 330 core\n"
						"in vec3 color;"
						"in vec2 tex_coord;"
						"out vec4 out_color;"
						"uniform sampler2D tex;"
						"void main()"
						"{"
						"	out_color = /*texture(tex, tex_coord) * */vec4(color, 1.0);"
						"}"
						)
				};

				GLuint program_id = create_program(idv, 2);

				for(GLuint* it = idv, *end = idv + 2; it < end; ++it)
					destroy_shader(*it);

				glUseProgram(program_id);

				return program_id;
			}

			void shaders_destroy(GLuint program_id)
			{
				glDeleteProgram(program_id);
			}
		}

		WindowGL::WindowGL(CStr title, int width, int height) : ImageGL(width, height, &_vec_drawitem)
		{
		}

		WindowGL::~WindowGL()
		{
			OpenGL::shaders_destroy(_program_id);
			_program_id = 0;
		}

		void WindowGL::Initialize()
		{
			_program_id = OpenGL::shaders_init();

			glClearColor(.0f, .0f, .0f, 1.f);
			OpenGL::glGenBuffers(1, &_vertex_buffer);
		}

		Image* WindowGL::CreateImage(int width, int height) const
		{
			return new ImageGL(width, height, nullptr);
		}

		Image* WindowGL::CreateImage(const char* file) const
		{
			int width{32}, height{32};
			return new ImageGL(width, height, nullptr);
		}

		Image* WindowGL::CreateImage(const void* memory, Int size) const
		{
			int width{32}, height{32};
			return new ImageGL(width, height, nullptr);
		}

		void WindowGL::BeginDraw(bool clear)
		{
		}

		void WindowGL::EndDraw()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			GLint uniform = OpenGL::glGetUniformLocation(_program_id, "mat_transformation");
			Matrix4 view = mat4_make_identity();
			OpenGL::glUniformMatrix4fv(uniform, 1, GL_FALSE, view.v);

			float rectangle[] =
			{
				//  x      y     z,    r,    g,    b    tx,   ty
				-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			};

			OpenGL::glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
			const GLsizei stride = sizeof(float) * 8;
			OpenGL::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, 0);
			OpenGL::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3));
			OpenGL::glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 6));

			for(auto& di : _vec_drawitem)
			{
				double conv_x{2.0 / Width()}, conv_y{2.0 / Height()};
				double x1 = di.rect.x1 * conv_x - 1.0;
				double y1 = di.rect.y1 * conv_y - 1.0;
				double x2 = di.rect.x2 * conv_x - 1.0;
				double y2 = di.rect.y2 * conv_y - 1.0;

				//x1 = -0.5; y1 =  0.5;
				//x2 =  0.5; y2 = -0.5;
				rectangle[0]  = x1; rectangle[1]  = -y1;
				rectangle[8]  = x2; rectangle[9]  = -y1;
				rectangle[16] = x2; rectangle[17] = -y2;
				rectangle[24] = x1; rectangle[25] = -y1;
				rectangle[32] = x1; rectangle[33] = -y2;

				//for(int i = 0, j = 3; i < 5; ++i)
				//{
				//	rectangle[j] = di.color.red / 255.0;
				//	rectangle[j + 1] = di.color.green / 255.0;
				//	rectangle[j + 2] = di.color.blue / 255.0;
				//	j += 8;
				//}

				OpenGL::glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
				OpenGL::glEnableVertexAttribArray(0);
				OpenGL::glEnableVertexAttribArray(1);
				OpenGL::glEnableVertexAttribArray(2);

				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
			}

			_vec_drawitem.clear();
			Sleep(5);
		}

		bool WindowGL::Update()
		{
			return true;
		}

		void WindowGL::Close()
		{
			OpenGL::glDisableVertexAttribArray(2);
			OpenGL::glDisableVertexAttribArray(1);
			OpenGL::glDisableVertexAttribArray(0);

			OpenGL::glDeleteBuffers(1, &_vertex_buffer);
		}
	}
}
