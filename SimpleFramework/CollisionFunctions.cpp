#include "CollisionFunctions.h"

#include "Circle.h"
#include "Plane.h"
#include "Box.h"

Observer Observer::s_Observer = Observer();

typedef bool(*CollisionFunction)(Body&, Body&, CollisionInfo&);

CollisionInfo GetCollision(Body* Body1, Body* Body2)
{
	CollisionInfo data;

	if (Body1 == nullptr || Body2 == nullptr) return data;

	data.Object1 = Body1;
	data.Object2 = Body2;	

	auto f = (CollisionFunction) Observer::s_Observer.GetFunction(Body1, Body2);
	f(*Body1, *Body2, data);

	//s_Observer.GetCollisionType<Circle, Circle>(Body1, Body2, data);
	//s_Observer.GetCollisionType<Circle, Plane>(Body1, Body2, data);
	//s_Observer.GetCollisionType<Circle, Box>(Body1, Body2, data);
	//s_Observer.GetCollisionType<Plane, Box>(Body1, Body2, data);
	//s_Observer.GetCollisionType<Box, Box>(Body1, Body2, data);

	if (data.Depth <= 0) {
		data._valid = false; return data;
	}

	if (!data._valid) {
		// ! Collision type not implemented !
		__debugbreak();
	}

	return data;
}
