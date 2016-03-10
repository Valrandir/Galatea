#include "Matrix4.hpp"
#include <math.h>

Matrix4 mat4_make_identity()
{
	Matrix4 mat =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	return mat;
}

Matrix4 mat4_make_translation(float x, float y, float z)
{
	Matrix4 mat =
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};
	return mat;
}

Matrix4 mat4_make_scale(float x, float y, float z)
{
	Matrix4 mat =
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1,
	};
	return mat;
}

Matrix4 mat4_make_rotation_x(float angle_degree)
{
	float rad = degree_to_radian(angle_degree);
	float s = sinf(rad);
	float c = cosf(rad);
	Matrix4 mat =
	{
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1,
	};
	return mat;
}

Matrix4 mat4_make_rotation_y(float angle_degree)
{
	float rad = degree_to_radian(angle_degree);
	float s = sinf(rad);
	float c = cosf(rad);
	Matrix4 mat =
	{
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1,
	};
	return mat;
}

Matrix4 mat4_make_rotation_z(float angle_degree)
{
	float rad = degree_to_radian(angle_degree);
	float s = sinf(rad);
	float c = cosf(rad);
	Matrix4 mat =
	{
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	return mat;
}

float degree_to_radian(float degree)
{
	return degree * 0.01745329251994329576923690768489f;
}

Matrix4 mat4_mul(Matrix4 transform, Matrix4 current)
{
	Matrix4 mat;
	const int size = 4;
	for(auto y = 0; y < size; ++y)
		for(auto x = 0; x < size; ++x)
		{
			float sum = 0;
			for(int i = 0; i < size; ++i)
				sum += transform.v[y * size + i] * current.v[i * size + x];
			mat.v[y * size + x] = sum;
		}

	return mat;
}
