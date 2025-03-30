#pragma once
#include <algorithm>

struct vec3 {
	float x, y, z;

	vec3() {};
	vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	vec3 operator + (const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	vec3 operator - (const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
	vec3 operator * (const float& rhs) const { return vec3(x * rhs, y * rhs, z * rhs); }
	vec3 operator / (const float& rhs) const { return vec3(x / rhs, y / rhs, z / rhs); }
	vec3& operator += (const vec3& rhs) { return *this = *this + rhs; }
	vec3& operator -= (const vec3& rhs) { return *this = *this - rhs; }
	vec3& operator *= (const float& rhs) { return *this = *this * rhs; }
	vec3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	vec3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const vec3& rhs) const { return (*this - rhs).Length(); }
};

struct vec4 {
	float x, y, z, w;
};

bool WorldToScreen(vec3 pos, vec3& screen, float matrix[16], int windowWidth, int windowHeight);