#include "CollisionInfo.h"
#include "Body.h"
#include "Physical.h"


Vec2 CollisionInfo::DEBUG_PosChangeA = Vec2(0, 0);
Vec2 CollisionInfo::DEBUG_PosChangeB = Vec2(0, 0);

void CollisionInfo::PerformDepenetrationStep(Body* b1, Body* b2)
{

		float totalInvMass = b1->GetInvMass() + b2->GetInvMass();

		DEBUG_PosChangeA = Normal * Depth * (b2->GetInvMass() / totalInvMass);
		DEBUG_PosChangeB = Normal * Depth * (b1->GetInvMass() / totalInvMass);

		b1->m_Position -= Normal * Depth * ( b1->GetInvMass() / totalInvMass);
		b2->m_Position += Normal * Depth * ( b2->GetInvMass() / totalInvMass);

}

void CollisionInfo::ResolveCollision()
{

	Physical* p1 = dynamic_cast<Physical*>(Object1); // Object 1
	Physical* p2 = dynamic_cast<Physical*>(Object2); // Object 2

	PerformDepenetrationStep(Object1, Object2);

	float elasticity = Environment::s_Elasticity;
	float j = 0.0f; 
	float totalInvMass = Object1->GetInvMass() + Object2->GetInvMass();
	Vec2 relativeVelocity = { 0,0 }; 
	Vec2 impulse = { 0.0f, 0.0f };
	
	relativeVelocity = Object1->m_Velocity - Object2->m_Velocity;
	j = (1 + elasticity) * glm::dot(relativeVelocity, Normal) / totalInvMass;
	impulse = Normal * j;

	if (j < 0) return;

	if(!Object2->IsStatic()) p2->AddImpulse(impulse);
	if(!Object1->IsStatic()) p1->AddImpulse(-impulse);


}
