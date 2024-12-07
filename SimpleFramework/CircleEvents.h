#pragma once

struct CollisionInfo;

class Circle;
class Plane;
class Box;
class Poly;

bool CircleToCircle	(Circle& circleA, Circle&	circleB	, CollisionInfo& info);
bool CircleToPlane	(Circle& circle , Plane&	plane	, CollisionInfo& info);
bool CircleToBox	(Circle& circle , Box&		box		, CollisionInfo& info);
bool CircleToPoly	(Circle& circle , Poly&		poly	, CollisionInfo& info);