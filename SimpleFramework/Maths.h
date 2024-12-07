#pragma once

#include <math.h>
#include <complex>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "gtx/norm.hpp"

#define GLM_CONFIG_XYZW_ONLY

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

#define PI 3.14159265f

static Vec2 RotatePoint(const Vec2 point, const Vec2 origin, const float rad) {
	Vec2 p = point;
	float s = glm::sin(rad);
	float c = glm::cos(rad);
	Vec2 t = point;
	p.x = (t.x - origin.x) * c - (t.y - origin.y) * s + origin.x;
	p.y = (t.x - origin.x) * s + (t.y - origin.y) * c + origin.y;
	return p;
}

static int SmallestNumberPosition(float a, float b, float c, float d) {
	if (a < b && a < c && a < d) return 0;
	if (b < c && b < d ) return 1;
	if (c < d) return 2;
	return 3;
}