#pragma once

struct CollisionInfo;

class Plane;
class Box;
class Poly;

// Not needed
// * bool PlaneToPlane(Plane& plane1, Plane& plane2, CollisionInfo& CollisionInfo); * //
bool PlaneToBox	 (Plane& plane, Box&   box, CollisionInfo& info);
bool PlaneToPoly (Plane& plane, Poly& poly, CollisionInfo& info);