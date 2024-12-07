#pragma once
#include "Poly.h"

class Box : public Physical {

public:

	Box();
	Box(int x, int y, int w, int h);

	void Update(float delta) override;
	void Draw(LineRenderer* renderer) override;
	void DebugDraw(LineRenderer* renderer) override;

	inline void SetSize(Vec2 size) { m_Size = size; };
	inline const Vec2 GetSize() const override { return m_Size; }

	inline const float GetMass() const { return m_Size.x * m_Size.y; }

	virtual const bool IsInside(const Vec2 point) const override;

	BODY_TYPE(Box)

private:
	void DrawDebugGUI() override;

	Vec2 m_Size = Vec2(1,1);
};
