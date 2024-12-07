#pragma once
#include "Maths.h"
#include "Physical.h"

struct CollisionInfo
{
	friend class DebugWindow;
	Vec2 Normal;	//Points from 1 to 2
	float Depth;
	bool _valid = false;

	Body* Object1 = nullptr;
	Body* Object2 = nullptr;

	void PerformDepenetrationStep(Body* p1, Body* p2);
	void ResolveCollision();

	private:
		static Vec2 DEBUG_PosChangeA;
		static Vec2 DEBUG_PosChangeB;
};
