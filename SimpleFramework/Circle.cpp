#include "Circle.h"
#include "Style.h"

void Circle::Update(float delta)
{
	Calc(delta);
}

void Circle::Draw(LineRenderer* renderer)
{

	SET_STATIC_COLOUR

	renderer->DrawCircle(GetPosition(), m_Radius, 64);	
	renderer->SetColour(Vec3(PRIMARY_COLOUR));
}

void Circle::DebugDraw(LineRenderer* renderer)
{

	SET_STATIC_COLOUR

	renderer->SetColour(Vec3(VELOCITY_COLOUR));
	renderer->DrawLineSegment(glm::normalize(GetVelocity()) + GetPosition(), GetPosition());
	renderer->SetColour(Vec3(PRIMARY_COLOUR));
}

const bool Circle::IsInside(const Vec2 point) const
{
	return glm::length(GetPosition() - point) < GetRadius();
}

void Circle::DrawDebugGUI()
{
	ImGui::DragFloat("Radius", &m_Radius, 0.05f, 1.0f, 10.0f);
}
