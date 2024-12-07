#include "CircleEvents.h"

#include "CollisionInfo.h"

#include "Circle.h"
#include "Plane.h"
#include "Box.h"
#include "Poly.h"

bool CircleToCircle(Circle& circleA, Circle& circleB, CollisionInfo& info) {
	
	Vec2 displacement = circleB.GetPosition() - circleA.GetPosition();
	float centreDistances = glm::length(displacement);
	float overlapAmount = -centreDistances + circleA.GetRadius() + circleB.GetRadius();

	info.Depth = overlapAmount;
	info.Normal = glm::normalize(displacement);
	info.Object1 = &circleA;
	info.Object2 = &circleB;
	info._valid = true;

	if (info.Depth < 0) { return false; }

	return true;
}

bool CircleToPlane(Circle& circle, Plane& plane, CollisionInfo& info)
{

	info.Depth = circle.GetRadius() - plane.GetDistance(circle.GetPosition());
	info.Normal = -plane.GetNormal();
	info.Object1 = &circle;
	info.Object2 = &plane;
	info._valid = true;

	return true;
}

bool CircleToBox(Circle& circle, Box& box, CollisionInfo& info)
{

	float xMin = box.GetPosition().x - box.GetSize().x / 2.0f;
	float xMax = box.GetPosition().x + box.GetSize().x / 2.0f;
	float yMin = box.GetPosition().y - box.GetSize().y / 2.0f;
	float yMax = box.GetPosition().y + box.GetSize().y / 2.0f;

	Vec2 clostestPoint = glm::clamp(circle.GetPosition(), Vec2(xMin, yMin), Vec2(xMax, yMax));
	Vec2 displacement =  clostestPoint - circle.GetPosition();
	float depth = circle.GetRadius() - glm::length(displacement) ;

	info.Depth = depth;
	info.Normal = glm::normalize(displacement);
	info.Object1 = &circle;
	info.Object2 = &box;
	info._valid = true;

	return true;
}

bool CircleToPoly(Circle& circle, Poly& poly, CollisionInfo& info)
{
	return false;
}
