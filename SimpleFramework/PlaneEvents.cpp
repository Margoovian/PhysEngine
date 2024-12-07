#include "PlaneEvents.h"

#include "CollisionInfo.h"

#include "Plane.h"
#include "Box.h"
#include "Poly.h"

bool PlaneToBox(Plane& plane, Box& box, CollisionInfo& info)
{

	info.Object1 = &plane;
	info.Object2 = &box;
	info._valid = true;

	float xMin = box.GetPosition().x - box.GetSize().x / 2.0f;
	float xMax = box.GetPosition().x + box.GetSize().x / 2.0f;
	float yMin = box.GetPosition().y - box.GetSize().y / 2.0f;
	float yMax = box.GetPosition().y + box.GetSize().y / 2.0f;

	Vec2 points[4]{
	
		Vec2(xMin, yMin),
		Vec2(xMin, yMax),
		Vec2(xMax, yMin),
		Vec2(xMax, yMax)
	
	};

	int closestPos = SmallestNumberPosition(
		plane.GetDistance(points[0]),
		plane.GetDistance(points[1]),
		plane.GetDistance(points[2]),
		plane.GetDistance(points[3]) 
	);

	float clostestDistance = plane.GetDistance(points[closestPos]);
	float distanceToPlane = plane.GetDistance(box.GetPosition());
	float squidward = distanceToPlane - clostestDistance;
	float depth = squidward - distanceToPlane;

	info.Depth = depth ;
	info.Normal = plane.GetNormal();

	return true;
}

bool PlaneToPoly(Plane& plane, Poly& poly, CollisionInfo& info)
{
	return false;
}
