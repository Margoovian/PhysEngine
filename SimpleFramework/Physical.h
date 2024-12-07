#pragma once

#include "Maths.h"
#include "Body.h"
#include "Constants.h"

class Physical : public Body
{
	friend struct CollisionInfo;
	friend class DebugWindow;

public:

	
	Physical() { m_Static = false; }
	Physical(float x, float y) { m_Position = Vec2(x, y); m_Static = false; m_Anchored = false; };

	inline void AddForce(Vec2 force) { m_ForceAccumulator += force; };
	inline void AddImpulse(Vec2 impulse) { m_Velocity += impulse / GetMass(); };

	inline const Vec2 GetPosition() const override { return m_Position; }
	inline const Vec2& GetPositionRef() const override { return m_Position; }
	inline void SetPosition(Vec2 position) { m_Position = position; }

	inline const Vec2 GetVelocity() const override { return m_Velocity;  }
	inline void SetVelocity(Vec2 velocity) { m_Velocity = velocity; }

	inline const Vec2 GetAcceleration() const { return m_Acceleration;  }
	inline void SetAcceleration(Vec2 acceleration ) { m_Acceleration = acceleration;  }

	virtual inline const float GetMass() const = 0;

	inline virtual const float GetInvMass() const override { return  (!IsStatic()) * (1 / GetMass()); }
	virtual const bool IsInside(const Vec2 point) const = 0;

protected:
	void Calc(float delta) {
		if (IsStatic() && !m_PreserveMotion) { 
			m_Velocity = { 0,0 };
			m_ForceAccumulator = { 0, 0 };
			m_Acceleration = { 0,0 };
			return;
		}
		else if (IsStatic()) return;

		Vec2 gravity = { 0.0f, -Environment::s_Gravity };
		m_Acceleration = gravity + m_ForceAccumulator / GetMass();


		Vec2 newVelo = m_Velocity + m_Acceleration * delta;
		m_Position += 0.5f * (m_Velocity + newVelo) * delta;
		m_Velocity = newVelo;

		m_ForceAccumulator = { 0, 0 };
	};

	virtual void DrawDebugGUI() override {}
private:
	bool m_PreserveMotion = false;
	Vec2 m_ForceAccumulator = Vec2(0,0);
	Vec2 m_Acceleration = Vec2(0, 0);
};