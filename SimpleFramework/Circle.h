#pragma once
#include "Physical.h"

class Circle : public Physical {

public:

	Circle() {};
	Circle(int x, int y, float radius = 1.0f, Vec2 velocity = {0.0f,0.0f}) :
		Physical(x, y), m_Radius(radius) {
		SetVelocity(velocity);
	}

	void Update(float delta) override;
	void Draw(LineRenderer* renderer) override;
	void DebugDraw(LineRenderer* renderer) override;

	inline void SetRadius(float rad) { m_Radius = rad; };
	inline float GetRadius() const { return m_Radius; }
	inline const Vec2 GetSize() const override { return { m_Radius, m_Radius }; }

	inline const float GetMass() const { return m_Radius * m_Radius; }

	virtual const bool IsInside(const Vec2 point) const override;

	BODY_TYPE(Circle)

private:
	void DrawDebugGUI() override;

	float m_Radius = 1.0f;
};
