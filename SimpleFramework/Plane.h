#pragma once

#include "Body.h"
#include "Maths.h"

class Plane : public Body {

public:

	Plane(Vec2 normal, float displacement = 0.0f);

	void Draw(LineRenderer* renderer) override;
	void DebugDraw(LineRenderer* renderer) override;

	inline const Vec2 GetNormal() const { return glm::normalize(m_Normal); }
	inline void SetNormal(Vec2 normal) { m_Normal = glm::normalize(normal); }
	inline const float GetDisplacement() const { return m_Displacement; }

	const float GetDistance(Vec2 point) const;
	const float GetInverseDistance(Vec2 point) const;

	BODY_TYPE(Plane)

private:
	void DrawDebugGUI() override;

	Vec2 m_Normal;
	float m_Displacement = 0.0f;
	float m_Rads = 0.0f;

	float m_VisualSize = 10.0f;

};