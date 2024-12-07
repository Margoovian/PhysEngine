#include "BoxEvents.h"

#include "CollisionInfo.h"

#include "Box.h"
#include "Poly.h"

bool BoxToBox(Box& boxA, Box& boxB, CollisionInfo& info)
{

	float xMinA = boxA.GetPosition().x - boxA.GetSize().x / 2.0f;
	float xMaxA = boxA.GetPosition().x + boxA.GetSize().x / 2.0f;
	float yMinA = boxA.GetPosition().y - boxA.GetSize().y / 2.0f;
	float yMaxA = boxA.GetPosition().y + boxA.GetSize().y / 2.0f;

	float xMinB = boxB.GetPosition().x - boxB.GetSize().x / 2.0f;
	float xMaxB = boxB.GetPosition().x + boxB.GetSize().x / 2.0f;
	float yMinB = boxB.GetPosition().y - boxB.GetSize().y / 2.0f;
	float yMaxB = boxB.GetPosition().y + boxB.GetSize().y / 2.0f;

	float directions[4] { 
		xMaxB - xMinA, // Horizontal A
		yMaxB - yMinA, // Vertical A
		xMaxA - xMinB, // Horizontal B
		yMaxA - yMinB  // Vertical B
	};

	int index = SmallestNumberPosition(directions[0], directions[1], directions[2], directions[3]);
	

	info.Depth = directions[index];

	if(index == 0)			info.Normal = Vec2(-1,0);
	else if (index == 1)	info.Normal = Vec2(0,-1);
	else if (index == 2)	info.Normal = Vec2(1,0);
	else					info.Normal = Vec2(0,1);

	info.Object1 = &boxA;
	info.Object2 = &boxB;
	info._valid = true;

	return true;
}

bool BoxToPoly(Box& box, Poly& poly, CollisionInfo& info)
{
	return false;
}
