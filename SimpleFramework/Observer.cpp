#include "Observer.h"

#include "CollisionFunctions.h"

#include "Body.h"


Observer::Observer() {
	functionMap[BodyKey(BodyType::Circle, BodyType::Circle)] = &CircleToCircle;

	functionMap[BodyKey(BodyType::Circle, BodyType::Plane)] = &CircleToPlane;
	functionMap[BodyKey(BodyType::Plane, BodyType::Circle)] = &WrapFunction;

	functionMap[BodyKey(BodyType::Circle, BodyType::Box)] = &CircleToBox;
	functionMap[BodyKey(BodyType::Box, BodyType::Circle)] = &WrapFunction;

	functionMap[BodyKey(BodyType::Plane, BodyType::Box)] = &PlaneToBox;
	functionMap[BodyKey(BodyType::Box, BodyType::Plane)] = &WrapFunction;

	functionMap[BodyKey(BodyType::Box, BodyType::Box)] = &BoxToBox;

}

