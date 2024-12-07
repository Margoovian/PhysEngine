#include "Poly.h"

void Poly::Update(float delta)
{
	Calc(delta);
}

void Poly::Draw(LineRenderer* renderer)
{

	if (m_Points.size() < 2) { return; }

	for (int i = 0; i < m_Points.size() - 1; i++) {

		Vec2 pointA = m_Points[i];
		Vec2 pointB = m_Points[i+1];;

		RotatePoint(pointA, GetCenterPoint(), m_Rotation);
		RotatePoint(pointB, GetCenterPoint(), m_Rotation);

		renderer->AddPointToLine(pointA + GetPosition());
		renderer->AddPointToLine(pointB + GetPosition());

	}

	Vec2 start = m_Points[0];
	RotatePoint(start, GetCenterPoint(), m_Rotation);

	renderer->AddPointToLine(start + GetPosition());
	renderer->FinishLineLoop();

	renderer->DrawCross(GetCenterPoint() + GetPosition(), 0.1f, {1,0,0});
}

const std::vector<Vec2> Poly::GetPoints() const
{
	std::vector<Vec2> transformed;
	for (int i = 0; i < m_Points.size(); i++) {
		Vec2 v = m_Points[i];
		RotatePoint(v, GetCenterPoint(), m_Rotation);
		transformed.push_back(v);
	}

	return transformed;
}

const bool Poly::IsInside(const Vec2 point) const
{
	return false;
}

void Poly::CalculateCenter()
{
	float x = 0.0f;
	float y = 0.0f;

	for (int i = 0; i < m_Points.size(); i++) {
		x += m_Points[i].x;
		y += m_Points[i].y;
	}

	m_Center = { x / m_Points.size(), y / m_Points.size() };
}
