#pragma once

#include "LineRenderer.h"
#include "imgui.h"

#define SET_STATIC_COLOUR if (IsStatic()) renderer->SetColour({ ANCHORED_COLOUR });\
	else renderer->SetColour({ OBJECT_COLOUR });

#define BODY_TYPE(t) inline const BodyType GetType() const override { return BodyType::t; }

enum class BodyType {
	None = 0,
	Circle, Box, Plane, Poly 
};


class Body {
	friend struct CollisionInfo;
	friend class DebugWindow;
public:
	virtual void Update(float delta) {};
	virtual void Draw(LineRenderer* renderer) = 0;

	inline const bool IsStatic() const { return m_Static || m_Anchored; }

	inline void ToggleAnchor() { m_Anchored = !m_Anchored; }
	inline void Anchor() { m_Anchored = true; }
	inline void UnAnchor() { m_Anchored = false; }

	inline virtual const float GetInvMass() const { return 0.0f; }
	virtual void DebugDraw(LineRenderer* renderer) {};
	inline virtual const Vec2 GetPosition() const { return {0.0f,0.0f}; }
	inline virtual const Vec2 GetSize() const { return {0.0f,0.0f}; }
	inline virtual const Vec2& GetPositionRef() const { return Vec2(0, 0); };
	inline virtual const Vec2 GetVelocity() const { return { 0.0f,0.0f }; }

	virtual inline const BodyType GetType() const { return BodyType::None; }

protected:

	virtual void DrawDebugGUI() {}

	Vec2 m_Position = Vec2(0, 0);
	Vec2 m_Velocity = Vec2(0, 0);
	bool m_Static = true;
	bool m_Anchored = false;

};