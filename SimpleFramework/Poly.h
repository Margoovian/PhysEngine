#pragma once
#include "Physical.h"

class Poly : public Physical {

public:

	Poly() { 
		CalculateCenter();
		m_Static = false;
	};

	Poly(const std::vector<Vec2> points)
		: m_Points(points)
	{ 
		CalculateCenter();
		m_Static = false;
	};

	Poly(int x, int y) 
		:
		Physical(x, y) {
		CalculateCenter();
		m_Static = false;
	}

	void Update(float delta) override;
	void Draw(LineRenderer* renderer) override;

	inline const float GetRotation() const { return m_Rotation; }
	inline void SetRotation(float rad) { m_Rotation = rad; }

	const std::vector<Vec2> GetPoints() const;
	inline const std::vector<Vec2> GetTruePoints() const { return m_Points; };
	inline const Vec2 GetCenterPoint() const { return m_Center; };

	virtual const bool IsInside(const Vec2 point) const override;

	BODY_TYPE(Poly)

protected:
	inline void AddPoint(const Vec2 point) {
		m_Points.push_back(point);
	}

	inline const float GetMass() const { return 0; }
	void CalculateCenter();
private:
	std::vector<Vec2> m_Points;
	float m_Rotation = 0;
	Vec2 m_Center = Vec2(0, 0);
	//glm::mat4 m_RotMatrix = glm::mat4();
};
