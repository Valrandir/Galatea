#include "../../Assert/Assert.hpp"
#include "OpenGL.hpp"
#include "WindowGL.hpp"
#include "Matrix4.hpp"
float* get_texture_data(int* width, int* height);

namespace Galatea
{
	namespace Display
	{
		namespace OpenGL
		{
			#include <gl/GL.h>

			GLuint _vertex_buffer;
			GLuint _texture_data;

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
						"	out_color = texture(tex, tex_coord) * vec4(color, 1.0);"
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

			void scene_init()
			{
				glClearColor(.2f, .2f, .2f, 1.f);
				//glEnable(GL_DEPTH_TEST);

				const float texx = 1.f;
				const float texy = 1.f;

				const float rectangle[] =
				{
					//  x      y     z,    r,    g,    b    tx,   ty
					-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, texx, 0.0f,
					0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, texx, texy,
					-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, texy,
				};

				glGenBuffers(1, &_vertex_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

				glGenTextures(1, &_texture_data);
				glBindTexture(GL_TEXTURE_2D, _texture_data);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				int width, height;
				float* float_data = get_texture_data(&width, &height);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, float_data);

				const GLsizei stride = sizeof(float) * 8;
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, 0);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3));
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 6));
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);
			}

			void scene_destroy()
			{
				glDisableVertexAttribArray(2);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(0);
				glDeleteTextures(1, &_texture_data);
				glDeleteBuffers(1, &_vertex_buffer);
			}

			void scene_render(GLuint program_id)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				GLint uniform = glGetUniformLocation(program_id, "mat_transformation");

				static float degree = 0.f;
				degree += 0.5f;

				Matrix4 final;
				Matrix4 view = mat4_make_identity();
				view = mat4_mul(mat4_make_rotation_z(degree), view);
				view = mat4_mul(mat4_make_scale(0.5f, 0.5f, 0.0f), view);

				Matrix4 model;

				model = mat4_make_scale(2.0f, 2.0f, 0.0f);
				glUniformMatrix4fv(uniform, 1, GL_FALSE, model.v);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

				model = mat4_make_identity();
				model = mat4_mul(mat4_make_rotation_x(-degree), model);
				model = mat4_mul(mat4_make_rotation_y(-degree), model);
				model = mat4_mul(mat4_make_translation(-0.5f, 0.5f, 0.0f), model);
				final = mat4_mul(view, model);
				glUniformMatrix4fv(uniform, 1, GL_FALSE, final.v);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

				model = mat4_make_identity();
				model = mat4_mul(mat4_make_rotation_x(-degree), model);
				model = mat4_mul(mat4_make_rotation_y(-degree + 180), model);
				model = mat4_mul(mat4_make_translation(0.5f, 0.5f, 0.0f), model);
				final = mat4_mul(view, model);
				glUniformMatrix4fv(uniform, 1, GL_FALSE, final.v);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

				model = mat4_make_identity();
				model = mat4_mul(mat4_make_rotation_x(degree + 180), model);
				model = mat4_mul(mat4_make_rotation_y(degree + 180), model);
				model = mat4_mul(mat4_make_translation(0.5f, -0.5f, 0.0f), model);
				final = mat4_mul(view, model);
				glUniformMatrix4fv(uniform, 1, GL_FALSE, final.v);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

				model = mat4_make_identity();
				model = mat4_mul(mat4_make_rotation_x(degree + 180), model);
				model = mat4_mul(mat4_make_rotation_y(degree), model);
				model = mat4_mul(mat4_make_translation(-0.5f, -0.5f, 0.0f), model);
				final = mat4_mul(view, model);
				glUniformMatrix4fv(uniform, 1, GL_FALSE, final.v);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

				Sleep(5);
			}
		}

		WindowGL::WindowGL()
		{
		}

		WindowGL::~WindowGL()
		{
			OpenGL::scene_destroy();
			OpenGL::shaders_destroy(_program_id);
			_program_id = 0;
		}

		void WindowGL::Initialize()
		{
			_program_id = OpenGL::shaders_init();
			OpenGL::scene_init();
		}

		void WindowGL::BeginDraw(bool clear)
		{
			OpenGL::scene_render(_program_id);
		}

		void WindowGL::EndDraw()
		{
		}

		bool WindowGL::Update()
		{
			return true;
		}

		void WindowGL::Close()
		{

		}
	}
}

float* get_texture_data(int* width, int* height)
{
	*width = 32;
	*height = 32;

	//Grayscale Clouds Mosaic - 32x32 RGB
	static float texture_data[] =
	{
		0.53f,0.53f,0.53f, 0.53f,0.53f,0.53f, 0.44f,0.44f,0.44f, 0.31f,0.31f,0.31f, 0.21f,0.21f,0.21f, 0.17f,0.17f,0.17f, 0.18f,0.18f,0.18f, 0.22f,0.22f,0.22f, 0.32f,0.32f,0.32f, 0.41f,0.41f,0.41f, 0.41f,0.41f,0.41f, 0.36f,0.36f,0.36f, 0.33f,0.33f,0.33f, 0.35f,0.35f,0.35f, 0.31f,0.31f,0.31f, 0.26f,0.26f,0.26f, 0.26f,0.26f,0.26f, 0.31f,0.31f,0.31f, 0.35f,0.35f,0.35f, 0.33f,0.33f,0.33f, 0.36f,0.36f,0.36f, 0.41f,0.41f,0.41f, 0.41f,0.41f,0.41f, 0.32f,0.32f,0.32f, 0.22f,0.22f,0.22f, 0.18f,0.18f,0.18f, 0.17f,0.17f,0.17f, 0.21f,0.21f,0.21f, 0.31f,0.31f,0.31f, 0.44f,0.44f,0.44f, 0.53f,0.53f,0.53f, 0.53f,0.53f,0.53f,
		0.52f,0.52f,0.52f, 0.49f,0.49f,0.49f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.21f,0.21f,0.21f, 0.15f,0.15f,0.15f, 0.13f,0.13f,0.13f, 0.17f,0.17f,0.17f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.37f,0.37f,0.37f, 0.28f,0.28f,0.28f, 0.26f,0.26f,0.26f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.22f,0.22f,0.22f, 0.22f,0.22f,0.22f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.26f,0.26f,0.26f, 0.28f,0.28f,0.28f, 0.37f,0.37f,0.37f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.17f,0.17f,0.17f, 0.13f,0.13f,0.13f, 0.15f,0.15f,0.15f, 0.21f,0.21f,0.21f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.49f,0.49f,0.49f, 0.52f,0.52f,0.52f,
		0.52f,0.52f,0.52f, 0.45f,0.45f,0.45f, 0.37f,0.37f,0.37f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.19f,0.19f,0.19f, 0.17f,0.17f,0.17f, 0.21f,0.21f,0.21f, 0.31f,0.31f,0.31f, 0.33f,0.33f,0.33f, 0.33f,0.33f,0.33f, 0.26f,0.26f,0.26f, 0.24f,0.24f,0.24f, 0.24f,0.24f,0.24f, 0.23f,0.23f,0.23f, 0.18f,0.18f,0.18f, 0.18f,0.18f,0.18f, 0.23f,0.23f,0.23f, 0.24f,0.24f,0.24f, 0.24f,0.24f,0.24f, 0.26f,0.26f,0.26f, 0.33f,0.33f,0.33f, 0.33f,0.33f,0.33f, 0.31f,0.31f,0.31f, 0.21f,0.21f,0.21f, 0.17f,0.17f,0.17f, 0.19f,0.19f,0.19f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.37f,0.37f,0.37f, 0.45f,0.45f,0.45f, 0.52f,0.52f,0.52f,
		0.57f,0.57f,0.57f, 0.53f,0.53f,0.53f, 0.44f,0.44f,0.44f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.23f,0.23f,0.23f, 0.22f,0.22f,0.22f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.29f,0.29f,0.29f, 0.33f,0.33f,0.33f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.21f,0.21f,0.21f, 0.21f,0.21f,0.21f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.33f,0.33f,0.33f, 0.29f,0.29f,0.29f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.22f,0.22f,0.22f, 0.23f,0.23f,0.23f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.44f,0.44f,0.44f, 0.53f,0.53f,0.53f, 0.57f,0.57f,0.57f,
		0.61f,0.61f,0.61f, 0.57f,0.57f,0.57f, 0.55f,0.55f,0.55f, 0.45f,0.45f,0.45f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.27f,0.27f,0.27f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.16f,0.16f,0.16f, 0.17f,0.17f,0.17f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.17f,0.17f,0.17f, 0.16f,0.16f,0.16f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.27f,0.27f,0.27f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.45f,0.45f,0.45f, 0.55f,0.55f,0.55f, 0.57f,0.57f,0.57f, 0.61f,0.61f,0.61f,
		0.61f,0.61f,0.61f, 0.60f,0.60f,0.60f, 0.62f,0.62f,0.62f, 0.50f,0.50f,0.50f, 0.37f,0.37f,0.37f, 0.30f,0.30f,0.30f, 0.31f,0.31f,0.31f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.33f,0.33f,0.33f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.27f,0.27f,0.27f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.17f,0.17f,0.17f, 0.17f,0.17f,0.17f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.27f,0.27f,0.27f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.33f,0.33f,0.33f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.31f,0.31f,0.31f, 0.30f,0.30f,0.30f, 0.37f,0.37f,0.37f, 0.50f,0.50f,0.50f, 0.62f,0.62f,0.62f, 0.60f,0.60f,0.60f, 0.61f,0.61f,0.61f,
		0.64f,0.64f,0.64f, 0.59f,0.59f,0.59f, 0.62f,0.62f,0.62f, 0.51f,0.51f,0.51f, 0.40f,0.40f,0.40f, 0.34f,0.34f,0.34f, 0.38f,0.38f,0.38f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.42f,0.42f,0.42f, 0.37f,0.37f,0.37f, 0.38f,0.38f,0.38f, 0.32f,0.32f,0.32f, 0.24f,0.24f,0.24f, 0.20f,0.20f,0.20f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.20f,0.20f,0.20f, 0.24f,0.24f,0.24f, 0.32f,0.32f,0.32f, 0.38f,0.38f,0.38f, 0.37f,0.37f,0.37f, 0.42f,0.42f,0.42f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.38f,0.38f,0.38f, 0.34f,0.34f,0.34f, 0.40f,0.40f,0.40f, 0.51f,0.51f,0.51f, 0.62f,0.62f,0.62f, 0.59f,0.59f,0.59f, 0.64f,0.64f,0.64f,
		0.65f,0.65f,0.65f, 0.62f,0.62f,0.62f, 0.61f,0.61f,0.61f, 0.52f,0.52f,0.52f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.46f,0.46f,0.46f, 0.50f,0.50f,0.50f, 0.51f,0.51f,0.51f, 0.47f,0.47f,0.47f, 0.47f,0.47f,0.47f, 0.41f,0.41f,0.41f, 0.32f,0.32f,0.32f, 0.31f,0.31f,0.31f, 0.30f,0.30f,0.30f, 0.30f,0.30f,0.30f, 0.31f,0.31f,0.31f, 0.32f,0.32f,0.32f, 0.41f,0.41f,0.41f, 0.47f,0.47f,0.47f, 0.47f,0.47f,0.47f, 0.51f,0.51f,0.51f, 0.50f,0.50f,0.50f, 0.46f,0.46f,0.46f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.52f,0.52f,0.52f, 0.61f,0.61f,0.61f, 0.62f,0.62f,0.62f, 0.65f,0.65f,0.65f,
		0.63f,0.63f,0.63f, 0.60f,0.60f,0.60f, 0.58f,0.58f,0.58f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.49f,0.49f,0.49f, 0.48f,0.48f,0.48f, 0.52f,0.52f,0.52f, 0.51f,0.51f,0.51f, 0.53f,0.53f,0.53f, 0.57f,0.57f,0.57f, 0.54f,0.54f,0.54f, 0.45f,0.45f,0.45f, 0.41f,0.41f,0.41f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.41f,0.41f,0.41f, 0.45f,0.45f,0.45f, 0.54f,0.54f,0.54f, 0.57f,0.57f,0.57f, 0.53f,0.53f,0.53f, 0.51f,0.51f,0.51f, 0.52f,0.52f,0.52f, 0.48f,0.48f,0.48f, 0.49f,0.49f,0.49f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.58f,0.58f,0.58f, 0.60f,0.60f,0.60f, 0.63f,0.63f,0.63f,
		0.62f,0.62f,0.62f, 0.58f,0.58f,0.58f, 0.52f,0.52f,0.52f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.54f,0.54f,0.54f, 0.54f,0.54f,0.54f, 0.50f,0.50f,0.50f, 0.54f,0.54f,0.54f, 0.58f,0.58f,0.58f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.55f,0.55f,0.55f, 0.52f,0.52f,0.52f, 0.44f,0.44f,0.44f, 0.44f,0.44f,0.44f, 0.52f,0.52f,0.52f, 0.55f,0.55f,0.55f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.58f,0.58f,0.58f, 0.54f,0.54f,0.54f, 0.50f,0.50f,0.50f, 0.54f,0.54f,0.54f, 0.54f,0.54f,0.54f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.52f,0.52f,0.52f, 0.58f,0.58f,0.58f, 0.62f,0.62f,0.62f,
		0.60f,0.60f,0.60f, 0.57f,0.57f,0.57f, 0.52f,0.52f,0.52f, 0.49f,0.49f,0.49f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.62f,0.62f,0.62f, 0.66f,0.66f,0.66f, 0.70f,0.70f,0.70f, 0.68f,0.68f,0.68f, 0.65f,0.65f,0.65f, 0.60f,0.60f,0.60f, 0.56f,0.56f,0.56f, 0.46f,0.46f,0.46f, 0.46f,0.46f,0.46f, 0.56f,0.56f,0.56f, 0.60f,0.60f,0.60f, 0.65f,0.65f,0.65f, 0.68f,0.68f,0.68f, 0.70f,0.70f,0.70f, 0.66f,0.66f,0.66f, 0.62f,0.62f,0.62f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.49f,0.49f,0.49f, 0.52f,0.52f,0.52f, 0.57f,0.57f,0.57f, 0.60f,0.60f,0.60f,
		0.67f,0.67f,0.67f, 0.60f,0.60f,0.60f, 0.55f,0.55f,0.55f, 0.51f,0.51f,0.51f, 0.59f,0.59f,0.59f, 0.66f,0.66f,0.66f, 0.75f,0.75f,0.75f, 0.77f,0.77f,0.77f, 0.74f,0.74f,0.74f, 0.72f,0.72f,0.72f, 0.73f,0.73f,0.73f, 0.70f,0.70f,0.70f, 0.64f,0.64f,0.64f, 0.59f,0.59f,0.59f, 0.53f,0.53f,0.53f, 0.45f,0.45f,0.45f, 0.45f,0.45f,0.45f, 0.53f,0.53f,0.53f, 0.59f,0.59f,0.59f, 0.64f,0.64f,0.64f, 0.70f,0.70f,0.70f, 0.73f,0.73f,0.73f, 0.72f,0.72f,0.72f, 0.74f,0.74f,0.74f, 0.77f,0.77f,0.77f, 0.75f,0.75f,0.75f, 0.66f,0.66f,0.66f, 0.59f,0.59f,0.59f, 0.51f,0.51f,0.51f, 0.55f,0.55f,0.55f, 0.60f,0.60f,0.60f, 0.67f,0.67f,0.67f,
		0.72f,0.72f,0.72f, 0.69f,0.69f,0.69f, 0.64f,0.64f,0.64f, 0.60f,0.60f,0.60f, 0.64f,0.64f,0.64f, 0.71f,0.71f,0.71f, 0.76f,0.76f,0.76f, 0.78f,0.78f,0.78f, 0.78f,0.78f,0.78f, 0.76f,0.76f,0.76f, 0.72f,0.72f,0.72f, 0.68f,0.68f,0.68f, 0.62f,0.62f,0.62f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.44f,0.44f,0.44f, 0.44f,0.44f,0.44f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.62f,0.62f,0.62f, 0.68f,0.68f,0.68f, 0.72f,0.72f,0.72f, 0.76f,0.76f,0.76f, 0.78f,0.78f,0.78f, 0.78f,0.78f,0.78f, 0.76f,0.76f,0.76f, 0.71f,0.71f,0.71f, 0.64f,0.64f,0.64f, 0.60f,0.60f,0.60f, 0.64f,0.64f,0.64f, 0.69f,0.69f,0.69f, 0.72f,0.72f,0.72f,
		0.75f,0.75f,0.75f, 0.73f,0.73f,0.73f, 0.70f,0.70f,0.70f, 0.66f,0.66f,0.66f, 0.66f,0.66f,0.66f, 0.67f,0.67f,0.67f, 0.71f,0.71f,0.71f, 0.74f,0.74f,0.74f, 0.76f,0.76f,0.76f, 0.77f,0.77f,0.77f, 0.70f,0.70f,0.70f, 0.65f,0.65f,0.65f, 0.62f,0.62f,0.62f, 0.55f,0.55f,0.55f, 0.44f,0.44f,0.44f, 0.39f,0.39f,0.39f, 0.39f,0.39f,0.39f, 0.44f,0.44f,0.44f, 0.55f,0.55f,0.55f, 0.62f,0.62f,0.62f, 0.65f,0.65f,0.65f, 0.70f,0.70f,0.70f, 0.77f,0.77f,0.77f, 0.76f,0.76f,0.76f, 0.74f,0.74f,0.74f, 0.71f,0.71f,0.71f, 0.67f,0.67f,0.67f, 0.66f,0.66f,0.66f, 0.66f,0.66f,0.66f, 0.70f,0.70f,0.70f, 0.73f,0.73f,0.73f, 0.75f,0.75f,0.75f,
		0.80f,0.80f,0.80f, 0.78f,0.78f,0.78f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.70f,0.70f,0.70f, 0.68f,0.68f,0.68f, 0.71f,0.71f,0.71f, 0.74f,0.74f,0.74f, 0.77f,0.77f,0.77f, 0.77f,0.77f,0.77f, 0.71f,0.71f,0.71f, 0.65f,0.65f,0.65f, 0.58f,0.58f,0.58f, 0.50f,0.50f,0.50f, 0.38f,0.38f,0.38f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.38f,0.38f,0.38f, 0.50f,0.50f,0.50f, 0.58f,0.58f,0.58f, 0.65f,0.65f,0.65f, 0.71f,0.71f,0.71f, 0.77f,0.77f,0.77f, 0.77f,0.77f,0.77f, 0.74f,0.74f,0.74f, 0.71f,0.71f,0.71f, 0.68f,0.68f,0.68f, 0.70f,0.70f,0.70f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.78f,0.78f,0.78f, 0.80f,0.80f,0.80f,
		0.81f,0.81f,0.81f, 0.75f,0.75f,0.75f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.70f,0.70f,0.70f, 0.69f,0.69f,0.69f, 0.69f,0.69f,0.69f, 0.67f,0.67f,0.67f, 0.62f,0.62f,0.62f, 0.54f,0.54f,0.54f, 0.42f,0.42f,0.42f, 0.30f,0.30f,0.30f, 0.26f,0.26f,0.26f, 0.26f,0.26f,0.26f, 0.30f,0.30f,0.30f, 0.42f,0.42f,0.42f, 0.54f,0.54f,0.54f, 0.62f,0.62f,0.62f, 0.67f,0.67f,0.67f, 0.69f,0.69f,0.69f, 0.69f,0.69f,0.69f, 0.70f,0.70f,0.70f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.75f,0.75f,0.75f, 0.81f,0.81f,0.81f,
		0.81f,0.81f,0.81f, 0.75f,0.75f,0.75f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.70f,0.70f,0.70f, 0.69f,0.69f,0.69f, 0.69f,0.69f,0.69f, 0.67f,0.67f,0.67f, 0.62f,0.62f,0.62f, 0.54f,0.54f,0.54f, 0.42f,0.42f,0.42f, 0.30f,0.30f,0.30f, 0.26f,0.26f,0.26f, 0.26f,0.26f,0.26f, 0.30f,0.30f,0.30f, 0.42f,0.42f,0.42f, 0.54f,0.54f,0.54f, 0.62f,0.62f,0.62f, 0.67f,0.67f,0.67f, 0.69f,0.69f,0.69f, 0.69f,0.69f,0.69f, 0.70f,0.70f,0.70f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.71f,0.71f,0.71f, 0.75f,0.75f,0.75f, 0.81f,0.81f,0.81f,
		0.80f,0.80f,0.80f, 0.78f,0.78f,0.78f, 0.73f,0.73f,0.73f, 0.71f,0.71f,0.71f, 0.70f,0.70f,0.70f, 0.68f,0.68f,0.68f, 0.71f,0.71f,0.71f, 0.74f,0.74f,0.74f, 0.77f,0.77f,0.77f, 0.77f,0.77f,0.77f, 0.71f,0.71f,0.71f, 0.65f,0.65f,0.65f, 0.58f,0.58f,0.58f, 0.50f,0.50f,0.50f, 0.38f,0.38f,0.38f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.38f,0.38f,0.38f, 0.50f,0.50f,0.50f, 0.58f,0.58f,0.58f, 0.65f,0.65f,0.65f, 0.71f,0.71f,0.71f, 0.77f,0.77f,0.77f, 0.77f,0.77f,0.77f, 0.74f,0.74f,0.74f, 0.71f,0.71f,0.71f, 0.68f,0.68f,0.68f, 0.70f,0.70f,0.70f, 0.71f,0.71f,0.71f, 0.73f,0.73f,0.73f, 0.78f,0.78f,0.78f, 0.80f,0.80f,0.80f,
		0.75f,0.75f,0.75f, 0.73f,0.73f,0.73f, 0.70f,0.70f,0.70f, 0.66f,0.66f,0.66f, 0.66f,0.66f,0.66f, 0.67f,0.67f,0.67f, 0.71f,0.71f,0.71f, 0.74f,0.74f,0.74f, 0.76f,0.76f,0.76f, 0.77f,0.77f,0.77f, 0.70f,0.70f,0.70f, 0.65f,0.65f,0.65f, 0.62f,0.62f,0.62f, 0.55f,0.55f,0.55f, 0.44f,0.44f,0.44f, 0.39f,0.39f,0.39f, 0.39f,0.39f,0.39f, 0.44f,0.44f,0.44f, 0.55f,0.55f,0.55f, 0.62f,0.62f,0.62f, 0.65f,0.65f,0.65f, 0.70f,0.70f,0.70f, 0.77f,0.77f,0.77f, 0.76f,0.76f,0.76f, 0.74f,0.74f,0.74f, 0.71f,0.71f,0.71f, 0.67f,0.67f,0.67f, 0.66f,0.66f,0.66f, 0.66f,0.66f,0.66f, 0.70f,0.70f,0.70f, 0.73f,0.73f,0.73f, 0.75f,0.75f,0.75f,
		0.72f,0.72f,0.72f, 0.69f,0.69f,0.69f, 0.64f,0.64f,0.64f, 0.60f,0.60f,0.60f, 0.64f,0.64f,0.64f, 0.71f,0.71f,0.71f, 0.76f,0.76f,0.76f, 0.78f,0.78f,0.78f, 0.78f,0.78f,0.78f, 0.76f,0.76f,0.76f, 0.72f,0.72f,0.72f, 0.68f,0.68f,0.68f, 0.62f,0.62f,0.62f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.44f,0.44f,0.44f, 0.44f,0.44f,0.44f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.62f,0.62f,0.62f, 0.68f,0.68f,0.68f, 0.72f,0.72f,0.72f, 0.76f,0.76f,0.76f, 0.78f,0.78f,0.78f, 0.78f,0.78f,0.78f, 0.76f,0.76f,0.76f, 0.71f,0.71f,0.71f, 0.64f,0.64f,0.64f, 0.60f,0.60f,0.60f, 0.64f,0.64f,0.64f, 0.69f,0.69f,0.69f, 0.72f,0.72f,0.72f,
		0.67f,0.67f,0.67f, 0.60f,0.60f,0.60f, 0.55f,0.55f,0.55f, 0.51f,0.51f,0.51f, 0.59f,0.59f,0.59f, 0.66f,0.66f,0.66f, 0.75f,0.75f,0.75f, 0.77f,0.77f,0.77f, 0.74f,0.74f,0.74f, 0.72f,0.72f,0.72f, 0.73f,0.73f,0.73f, 0.70f,0.70f,0.70f, 0.64f,0.64f,0.64f, 0.59f,0.59f,0.59f, 0.53f,0.53f,0.53f, 0.45f,0.45f,0.45f, 0.45f,0.45f,0.45f, 0.53f,0.53f,0.53f, 0.59f,0.59f,0.59f, 0.64f,0.64f,0.64f, 0.70f,0.70f,0.70f, 0.73f,0.73f,0.73f, 0.72f,0.72f,0.72f, 0.74f,0.74f,0.74f, 0.77f,0.77f,0.77f, 0.75f,0.75f,0.75f, 0.66f,0.66f,0.66f, 0.59f,0.59f,0.59f, 0.51f,0.51f,0.51f, 0.55f,0.55f,0.55f, 0.60f,0.60f,0.60f, 0.67f,0.67f,0.67f,
		0.60f,0.60f,0.60f, 0.57f,0.57f,0.57f, 0.52f,0.52f,0.52f, 0.49f,0.49f,0.49f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.62f,0.62f,0.62f, 0.66f,0.66f,0.66f, 0.70f,0.70f,0.70f, 0.68f,0.68f,0.68f, 0.65f,0.65f,0.65f, 0.60f,0.60f,0.60f, 0.56f,0.56f,0.56f, 0.46f,0.46f,0.46f, 0.46f,0.46f,0.46f, 0.56f,0.56f,0.56f, 0.60f,0.60f,0.60f, 0.65f,0.65f,0.65f, 0.68f,0.68f,0.68f, 0.70f,0.70f,0.70f, 0.66f,0.66f,0.66f, 0.62f,0.62f,0.62f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.49f,0.49f,0.49f, 0.52f,0.52f,0.52f, 0.57f,0.57f,0.57f, 0.60f,0.60f,0.60f,
		0.62f,0.62f,0.62f, 0.58f,0.58f,0.58f, 0.52f,0.52f,0.52f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.54f,0.54f,0.54f, 0.54f,0.54f,0.54f, 0.50f,0.50f,0.50f, 0.54f,0.54f,0.54f, 0.58f,0.58f,0.58f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.55f,0.55f,0.55f, 0.52f,0.52f,0.52f, 0.44f,0.44f,0.44f, 0.44f,0.44f,0.44f, 0.52f,0.52f,0.52f, 0.55f,0.55f,0.55f, 0.62f,0.62f,0.62f, 0.64f,0.64f,0.64f, 0.62f,0.62f,0.62f, 0.58f,0.58f,0.58f, 0.54f,0.54f,0.54f, 0.50f,0.50f,0.50f, 0.54f,0.54f,0.54f, 0.54f,0.54f,0.54f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.52f,0.52f,0.52f, 0.58f,0.58f,0.58f, 0.62f,0.62f,0.62f,
		0.63f,0.63f,0.63f, 0.60f,0.60f,0.60f, 0.58f,0.58f,0.58f, 0.56f,0.56f,0.56f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.49f,0.49f,0.49f, 0.48f,0.48f,0.48f, 0.52f,0.52f,0.52f, 0.51f,0.51f,0.51f, 0.53f,0.53f,0.53f, 0.57f,0.57f,0.57f, 0.54f,0.54f,0.54f, 0.45f,0.45f,0.45f, 0.41f,0.41f,0.41f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.41f,0.41f,0.41f, 0.45f,0.45f,0.45f, 0.54f,0.54f,0.54f, 0.57f,0.57f,0.57f, 0.53f,0.53f,0.53f, 0.51f,0.51f,0.51f, 0.52f,0.52f,0.52f, 0.48f,0.48f,0.48f, 0.49f,0.49f,0.49f, 0.51f,0.51f,0.51f, 0.51f,0.51f,0.51f, 0.56f,0.56f,0.56f, 0.58f,0.58f,0.58f, 0.60f,0.60f,0.60f, 0.63f,0.63f,0.63f,
		0.65f,0.65f,0.65f, 0.62f,0.62f,0.62f, 0.61f,0.61f,0.61f, 0.52f,0.52f,0.52f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.46f,0.46f,0.46f, 0.50f,0.50f,0.50f, 0.51f,0.51f,0.51f, 0.47f,0.47f,0.47f, 0.47f,0.47f,0.47f, 0.41f,0.41f,0.41f, 0.32f,0.32f,0.32f, 0.31f,0.31f,0.31f, 0.30f,0.30f,0.30f, 0.30f,0.30f,0.30f, 0.31f,0.31f,0.31f, 0.32f,0.32f,0.32f, 0.41f,0.41f,0.41f, 0.47f,0.47f,0.47f, 0.47f,0.47f,0.47f, 0.51f,0.51f,0.51f, 0.50f,0.50f,0.50f, 0.46f,0.46f,0.46f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.52f,0.52f,0.52f, 0.61f,0.61f,0.61f, 0.62f,0.62f,0.62f, 0.65f,0.65f,0.65f,
		0.64f,0.64f,0.64f, 0.59f,0.59f,0.59f, 0.62f,0.62f,0.62f, 0.51f,0.51f,0.51f, 0.40f,0.40f,0.40f, 0.34f,0.34f,0.34f, 0.38f,0.38f,0.38f, 0.44f,0.44f,0.44f, 0.45f,0.45f,0.45f, 0.42f,0.42f,0.42f, 0.37f,0.37f,0.37f, 0.38f,0.38f,0.38f, 0.32f,0.32f,0.32f, 0.24f,0.24f,0.24f, 0.20f,0.20f,0.20f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.20f,0.20f,0.20f, 0.24f,0.24f,0.24f, 0.32f,0.32f,0.32f, 0.38f,0.38f,0.38f, 0.37f,0.37f,0.37f, 0.42f,0.42f,0.42f, 0.45f,0.45f,0.45f, 0.44f,0.44f,0.44f, 0.38f,0.38f,0.38f, 0.34f,0.34f,0.34f, 0.40f,0.40f,0.40f, 0.51f,0.51f,0.51f, 0.62f,0.62f,0.62f, 0.59f,0.59f,0.59f, 0.64f,0.64f,0.64f,
		0.61f,0.61f,0.61f, 0.60f,0.60f,0.60f, 0.62f,0.62f,0.62f, 0.50f,0.50f,0.50f, 0.37f,0.37f,0.37f, 0.30f,0.30f,0.30f, 0.31f,0.31f,0.31f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.33f,0.33f,0.33f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.27f,0.27f,0.27f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.17f,0.17f,0.17f, 0.17f,0.17f,0.17f, 0.19f,0.19f,0.19f, 0.19f,0.19f,0.19f, 0.27f,0.27f,0.27f, 0.32f,0.32f,0.32f, 0.32f,0.32f,0.32f, 0.33f,0.33f,0.33f, 0.35f,0.35f,0.35f, 0.35f,0.35f,0.35f, 0.31f,0.31f,0.31f, 0.30f,0.30f,0.30f, 0.37f,0.37f,0.37f, 0.50f,0.50f,0.50f, 0.62f,0.62f,0.62f, 0.60f,0.60f,0.60f, 0.61f,0.61f,0.61f,
		0.61f,0.61f,0.61f, 0.57f,0.57f,0.57f, 0.55f,0.55f,0.55f, 0.45f,0.45f,0.45f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.27f,0.27f,0.27f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.16f,0.16f,0.16f, 0.17f,0.17f,0.17f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.17f,0.17f,0.17f, 0.16f,0.16f,0.16f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.27f,0.27f,0.27f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.45f,0.45f,0.45f, 0.55f,0.55f,0.55f, 0.57f,0.57f,0.57f, 0.61f,0.61f,0.61f,
		0.57f,0.57f,0.57f, 0.53f,0.53f,0.53f, 0.44f,0.44f,0.44f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.23f,0.23f,0.23f, 0.22f,0.22f,0.22f, 0.24f,0.24f,0.24f, 0.25f,0.25f,0.25f, 0.29f,0.29f,0.29f, 0.33f,0.33f,0.33f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.21f,0.21f,0.21f, 0.21f,0.21f,0.21f, 0.20f,0.20f,0.20f, 0.20f,0.20f,0.20f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.33f,0.33f,0.33f, 0.29f,0.29f,0.29f, 0.25f,0.25f,0.25f, 0.24f,0.24f,0.24f, 0.22f,0.22f,0.22f, 0.23f,0.23f,0.23f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.44f,0.44f,0.44f, 0.53f,0.53f,0.53f, 0.57f,0.57f,0.57f,
		0.52f,0.52f,0.52f, 0.45f,0.45f,0.45f, 0.37f,0.37f,0.37f, 0.31f,0.31f,0.31f, 0.25f,0.25f,0.25f, 0.19f,0.19f,0.19f, 0.17f,0.17f,0.17f, 0.21f,0.21f,0.21f, 0.31f,0.31f,0.31f, 0.33f,0.33f,0.33f, 0.33f,0.33f,0.33f, 0.26f,0.26f,0.26f, 0.24f,0.24f,0.24f, 0.24f,0.24f,0.24f, 0.23f,0.23f,0.23f, 0.18f,0.18f,0.18f, 0.18f,0.18f,0.18f, 0.23f,0.23f,0.23f, 0.24f,0.24f,0.24f, 0.24f,0.24f,0.24f, 0.26f,0.26f,0.26f, 0.33f,0.33f,0.33f, 0.33f,0.33f,0.33f, 0.31f,0.31f,0.31f, 0.21f,0.21f,0.21f, 0.17f,0.17f,0.17f, 0.19f,0.19f,0.19f, 0.25f,0.25f,0.25f, 0.31f,0.31f,0.31f, 0.37f,0.37f,0.37f, 0.45f,0.45f,0.45f, 0.52f,0.52f,0.52f,
		0.52f,0.52f,0.52f, 0.49f,0.49f,0.49f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.21f,0.21f,0.21f, 0.15f,0.15f,0.15f, 0.13f,0.13f,0.13f, 0.17f,0.17f,0.17f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.37f,0.37f,0.37f, 0.28f,0.28f,0.28f, 0.26f,0.26f,0.26f, 0.28f,0.28f,0.28f, 0.25f,0.25f,0.25f, 0.22f,0.22f,0.22f, 0.22f,0.22f,0.22f, 0.25f,0.25f,0.25f, 0.28f,0.28f,0.28f, 0.26f,0.26f,0.26f, 0.28f,0.28f,0.28f, 0.37f,0.37f,0.37f, 0.38f,0.38f,0.38f, 0.29f,0.29f,0.29f, 0.17f,0.17f,0.17f, 0.13f,0.13f,0.13f, 0.15f,0.15f,0.15f, 0.21f,0.21f,0.21f, 0.29f,0.29f,0.29f, 0.38f,0.38f,0.38f, 0.49f,0.49f,0.49f, 0.52f,0.52f,0.52f,
		0.53f,0.53f,0.53f, 0.53f,0.53f,0.53f, 0.44f,0.44f,0.44f, 0.31f,0.31f,0.31f, 0.21f,0.21f,0.21f, 0.17f,0.17f,0.17f, 0.18f,0.18f,0.18f, 0.22f,0.22f,0.22f, 0.32f,0.32f,0.32f, 0.41f,0.41f,0.41f, 0.41f,0.41f,0.41f, 0.36f,0.36f,0.36f, 0.33f,0.33f,0.33f, 0.35f,0.35f,0.35f, 0.31f,0.31f,0.31f, 0.26f,0.26f,0.26f, 0.26f,0.26f,0.26f, 0.31f,0.31f,0.31f, 0.35f,0.35f,0.35f, 0.33f,0.33f,0.33f, 0.36f,0.36f,0.36f, 0.41f,0.41f,0.41f, 0.41f,0.41f,0.41f, 0.32f,0.32f,0.32f, 0.22f,0.22f,0.22f, 0.18f,0.18f,0.18f, 0.17f,0.17f,0.17f, 0.21f,0.21f,0.21f, 0.31f,0.31f,0.31f, 0.44f,0.44f,0.44f, 0.53f,0.53f,0.53f, 0.53f,0.53f,0.53f,
	};

	return texture_data;
}
