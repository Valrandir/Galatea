#pragma once
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif
#include <gl/GL.h>

struct Matrix4
{
	GLfloat v[16];
};

float degree_to_radian(float degree);
Matrix4 mat4_mul(Matrix4 a, Matrix4 b);
Matrix4 mat4_make_identity();
Matrix4 mat4_make_translation(float x, float y, float z);
Matrix4 mat4_make_scale(float x, float y, float z);
Matrix4 mat4_make_rotation_x(float angle_degree);
Matrix4 mat4_make_rotation_y(float angle_degree);
Matrix4 mat4_make_rotation_z(float angle_degree);
