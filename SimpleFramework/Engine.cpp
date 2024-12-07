#include "Engine.h"

#include "imgui.h"
#include "DebugWindow.h"

#include "Style.h"

#include "CollisionFunctions.h"

#include "Circle.h"
#include "Box.h"
#include "Plane.h"

#include "Maths.h"

#include <iostream>
#include <sstream>

Engine::Engine()
{

	AddObject<Plane, Vec2, float>({ 0,1 }, -10);
	AddObject<Plane, Vec2, float>({ 1,0 }, -10);
	AddObject<Plane, Vec2, float>({ 0,-1 }, -10);
	AddObject<Plane, Vec2, float>({ -1,0}, -10);

	//for (float r = 0; r < 6.28; r += 0.027) {
	//	AddObject<Plane, Vec2, float>(RotatePoint(Vec2(1, 0), Vec2(0, 0), r), -10.0f);
	//}
}


void Engine::SolveCollision() {
	//
	// Quad tree stuff
	// 
	//m_Tree.Clear();
	//
	//for (Body* body : m_Objects) {
	//	if (body->GetType() == BodyType::Plane) continue;
	//	m_Tree.Insert({ body->GetPositionRef().x, body->GetPositionRef().y, body });
	//}
	//
	//for (int iteration = 0; iteration < 10; iteration++)
	//{
	//
	//	std::vector<CollisionInfo> collisionData;
	//
	//
	//
	//	for (Body* body : m_Objects) {
	//		auto others = m_Tree.Query({ body->GetPosition().x,body->GetPosition().y, body->GetSize().x * 2.0f, body->GetSize().y * 2.0f }, m_Objects.size());
	//		for (const QuadPoint<Body>& other : others) {
	//
	//			if (body->GetType() == BodyType::Plane && other.Object->GetType() == BodyType::Plane || body == other.Object) continue;
	//			CollisionInfo info = GetCollision(body, other.Object); // Get the collision info
	//			if (!info._valid) continue; // If collision is not valid, continue
	//			collisionData.push_back(info); // Add collision info
	//		}
	//
	//
	//	}
	//
	//	for (CollisionInfo& thisData : collisionData)
	//	{
	//		thisData.ResolveCollision();
	//	}
	//}
	//
	//m_Tree.Draw(lines);

	for (int iteration = 0; iteration < 10; iteration++)
	{
		std::vector<CollisionInfo> collisionData;
		for (int i = 0; i < m_Objects.size(); i++)
		{
			for (int j = i+1; j < m_Objects.size(); j++)
			{
				if (m_Objects[i]->GetType() == BodyType::Plane && m_Objects[j]->GetType() == BodyType::Plane) continue;
				CollisionInfo info = GetCollision(m_Objects[i], m_Objects[j]); // Get the collision info
				if (!info._valid) continue; // If collision is not valid, continue
	
	
				collisionData.push_back(info); // Add collision info
			}
		}
		for (CollisionInfo& thisData : collisionData)
		{
			thisData.ResolveCollision();
		}
	}
}

void Engine::Update(float delta)
{

	SolveCollision();
	
	for (Body* Object : m_Objects)
	{
		Object->Update(delta);
	}
	
	for (Body* Object : m_Objects)
	{
		Object->Draw(lines);
	
		if (DRAW_DEBUG) Object->DebugDraw(lines);
	}	
	
	if(DRAW_DEBUG) DebugWindow::Draw(*this, &m_DebugOpen);

	for (Body* Object : m_Objects)
	{
		if (Object->IsStatic()) { continue; }
		Vec2 toCursor = Vec2(0, 0) - ((Physical*)Object)->GetPosition();
		toCursor = glm::normalize(toCursor);
		((Physical*)Object)->AddImpulse(toCursor * 0.0f);
	}
	
}

void Engine::OnLeftClick()
{
	for (Body* Object : m_Objects)
	{
		if (Object->IsStatic()) { continue; }
		Vec2 toCursor = cursorPos - ((Physical*)Object)->GetPosition();
		toCursor = glm::normalize(toCursor);
		((Physical*)Object)->AddImpulse(toCursor * 2.0f);
	}
}

void Engine::OnRightClick()
{
	//AddObject<Circle, int, int, float, Vec2>(-8, 16, 2.0f, { 0.0f,0.0f });
	DebugSpawnPacket packet = DebugWindow::GetSpawnPacket();
	switch (packet.Type) {
	case DebugSpawnType::Circle: AddObject<Circle, int, int, float, Vec2>(cursorPos.x, cursorPos.y, packet.Radius, packet.Velocity); break;
	case DebugSpawnType::Box: AddObject<Box, int, int, int, int>(cursorPos.x, cursorPos.y, packet.Size.x, packet.Size.y); break;
	case DebugSpawnType::Plane: AddObject <Plane, Vec2, float>(packet.Normal, packet.Displacement); break;
	default: break;
	}
	
}

void Engine::OnKeyReleased(int key)
{
	if (key == 69) { // Key ->  E

		if (m_Objects.size() <= 0) return;
		Physical* closest = nullptr;

		for (Body* Object : m_Objects) // Get closest object
		{
			Physical* obj = dynamic_cast<Physical*>(Object);

			if (obj == nullptr) continue; 
			if (!obj->IsInside(cursorPos)) continue;

			Vec2 toCursor = cursorPos - obj->GetPosition();
			
			if (closest == nullptr) { closest = obj; continue; }

			if (glm::length(cursorPos - closest->GetPosition()) > glm::length(toCursor)) closest = dynamic_cast<Physical*>(Object);

		}

		if (closest != nullptr) {
			closest->ToggleAnchor();
		}

	}
}
