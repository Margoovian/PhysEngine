#include "Plane.h"
#include "Style.h"

Plane::Plane(Vec2 normal, float displacement)
	: m_Normal(glm::normalize(normal)), m_Displacement(displacement)
{}

void Plane::Draw(LineRenderer* renderer)
{
	Vec2 tangent = Vec2(m_Normal.y, -m_Normal.x);

	renderer->SetColour(Vec3(SECONDARY_COLOUR));
	renderer->DrawLineSegment( 
		m_Normal * m_Displacement + tangent * m_VisualSize,
		m_Normal * m_Displacement - tangent * m_VisualSize
	);

	renderer->SetColour(Vec3(NORMAL_COLOUR));
}

void Plane::DebugDraw(LineRenderer* renderer)
{
	renderer->SetColour(Vec3(NORMAL_COLOUR));
	renderer->DrawLineSegment(m_Normal * m_Displacement, m_Normal * m_Displacement + m_Normal);
	renderer->SetColour(Vec3(NORMAL_COLOUR));
}

const float Plane::GetDistance(Vec2 point) const
{
	return glm::dot(point, glm::normalize(m_Normal)) - m_Displacement;
}
const float Plane::GetInverseDistance(Vec2 point) const
{
	return -(glm::dot(point, glm::normalize(m_Normal)) - m_Displacement);
}

void Plane::DrawDebugGUI()
{
	
	ImGui::DragFloat("Visual Length", &m_VisualSize, 0.05f);
	ImGui::DragFloat("Displacement", &m_Displacement, 0.05f);

	m_Rads = atan2(m_Normal.y, m_Normal.x);

	float rotation = m_Rads * (180 / PI);
	if (rotation < 0) rotation += 360;

	ImGui::SliderFloat("Rotation", &rotation, 0,360);

	m_Rads = rotation * (PI / 180);
	SetNormal(RotatePoint(Vec2(1, 0), Vec2(0, 0), m_Rads));

	ImGui::DragFloat2("Normal", &(m_Normal.x),0.01f,-1.0f,1.0f);
	
	SetNormal(m_Normal);
}
