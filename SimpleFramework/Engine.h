#pragma once

#include "Application.h"
#include "Body.h"
#include "Physical.h"

#include "QuadTree.h"

#include <vector>
#include <type_traits>

class DebugWindow;

class Engine : public Application
{
	friend DebugWindow;
public:
	Engine();

	void Update(float delta) override;

	void OnLeftClick() override;
	void OnRightClick() override;
	void OnKeyReleased(int key) override;
private:

	void SolveCollision();

	std::vector<Body*> m_Objects;
	std::vector<int> m_Dynamics; //Position of physicals in m_Objects
	bool m_DebugOpen = false;
	template<typename T, typename... Args>
	void AddObject(Args... construction) {
		static_assert(std::is_base_of<Body, T>::value, "T must inherit from Body!");
		Body* p = new T(construction...);
		if (dynamic_cast<Physical*>(p) != nullptr) m_Dynamics.push_back(m_Objects.size());
		m_Objects.push_back(p);
	}

};