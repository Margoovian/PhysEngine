#pragma once

#include "CollisionInfo.h"
#include "CollisionEvents.h"

#include <typeinfo>
#include <unordered_map>
#include <functional>
#include "Observer.h"

#define VALIDATE_ASSIGN(typeA, typeB) if (info._valid) return true;\
auto result = CheckValidCollision<typeA, typeB>(Body1, Body2);\
if (!result.Outcome) { return false; }\
typeA& object1 = *result.Shape1;\
typeB& object2 = *result.Shape2;


CollisionInfo GetCollision(Body * Body1, Body * Body2);

static bool WrapFunction(Body & body1, Body & body2, CollisionInfo & info) {
	return ((bool(*)(Body&, Body&, CollisionInfo&)) Observer::s_Observer.GetFunction(&body2, &body1))(body2, body1, info);
}



