#pragma once
#include <memory>
#include <vector>
#include <algorithm>
// Debug

#include "LineRenderer.h"

struct QuadBoundary {
	const float x;
	const float y; 
	const float w;
	const float h;

	inline const bool Contains(const float X, const float Y) const {
		return
			(X > this->x - this->w &&
				X < this->x + this->w &&
				Y > this->y - this->h &&
				Y < this->y + this->h);
	}

	inline const bool Intersects(const float X, const float Y, const float W, const float H) const {
		return
			(X - W <= this->x + this->w && X + W >= this->x - this->w) &&
			(Y - H <= this->y + this->h && Y + H >= this->y - this->h);
	}
};

template<class T>
struct QuadPoint {
	const float& X;
	const float& Y;
	T* Object;
};

template<class T>
class Quadtree {

public:
	Quadtree(QuadBoundary boundary, const int capacity, const int maxDepth = 5);
	~Quadtree();

	Quadtree(const Quadtree<T>& other); // Copy constructor
	Quadtree(Quadtree<T>&& other) noexcept; // Move constructor

	Quadtree<T>& operator=(const Quadtree<T>& other); // Copy assignment
	Quadtree<T>& operator=(Quadtree<T>&& other) noexcept; // Move assignment


	bool Insert(const QuadPoint<T> point); //Insert point
	//const std::vector<const QuadPoint&> Query(float x, float y, float w, float h);
	std::vector<QuadPoint<T>> Query(const QuadBoundary area, const int maxSize) const;

	void Draw(LineRenderer* renderer); // Debug
	void Clear();
	void Subdivide();

	inline const bool isDivided() const { return m_Divided; }

	inline const Quadtree<T>& NorthWest() const { return *m_NorthWest.get(); }
	inline const Quadtree<T>& NorthEast() const { return *m_NorthEast.get(); }
	inline const Quadtree<T>& SouthWest() const { return *m_SouthWest.get(); }
	inline const Quadtree<T>& SouthEast() const { return *m_SouthEast.get(); }

	inline const std::vector<QuadPoint<T>> GetTenants() const { return m_Tenants; }

	inline const std::vector<Quadtree<T>*> GetLeafs() const {
		return m_Root->m_Leafs;
	}

	inline const QuadBoundary GetBoundary() const { return m_Boundary; }

private:

	Quadtree(QuadBoundary boundary, const int capacity, const int maxDepth, const int depth, Quadtree<T>* parent, Quadtree<T>* root);

	void QueryRecursed(const QuadBoundary area, std::vector<QuadPoint<T>>& list);
private:
	const QuadBoundary m_Boundary;
	const int m_Capacity;

	const int m_MaxDepth;
	const int m_Depth;

	std::vector<QuadPoint<T>> m_Tenants;
	bool m_Divided = false;

	std::unique_ptr<Quadtree<T>> m_NorthWest;
	std::unique_ptr<Quadtree<T>> m_NorthEast;
	std::unique_ptr<Quadtree<T>> m_SouthWest;
	std::unique_ptr<Quadtree<T>> m_SouthEast;

	Quadtree<T>* m_Parent;
	Quadtree<T>* m_Root;

	std::vector<Quadtree<T>*> m_Leafs;
};

/////////////////////////////////////// Implementation /////////////////////////////////////////////

template<class T>
Quadtree<T>::Quadtree(QuadBoundary boundary, const int capacity, const int maxDepth) // Public
	: m_Boundary(boundary), m_Capacity(capacity), m_MaxDepth(maxDepth), m_Depth(0), m_Parent(nullptr), m_Root(this)
{
	m_Root->m_Leafs.push_back(this);
}


template<class T>
inline Quadtree<T>::Quadtree(QuadBoundary boundary, const int capacity, const int maxDepth, const int depth, Quadtree<T>* parent, Quadtree<T>* root) // Private
	: m_Boundary(boundary), m_Capacity(capacity), m_MaxDepth(maxDepth), m_Depth(depth), m_Parent(parent), m_Root(root)
{
	m_Root->m_Leafs.push_back(this);
}

template<class T>
Quadtree<T>::~Quadtree()
{
	m_Tenants.clear();

	m_NorthWest.reset();
	m_NorthEast.reset();
	m_SouthWest.reset();
	m_SouthEast.reset();
}

template<class T> // Copy constructor
Quadtree<T>::Quadtree(const Quadtree<T>& other) : Quadtree<T>(other.m_Boundary, other.m_Capacity) {
}
template<class T> // Move constructor
Quadtree<T>::Quadtree(Quadtree<T>&& other) noexcept {
	// Not sure if this will work
	m_Boundary = std::exchange(other.m_Boundary, {});
	m_Capacity = std::exchange(other.m_Capacity, {});

	m_Tenants = std::exchange(other.m_Tenants, {});
	m_Divided = std::exchange(other.m_Divided, false);

	m_NorthWest = std::exchange(other.m_NorthWest, nullptr);
	m_NorthEast = std::exchange(other.m_NorthEast, nullptr);
	m_SouthWest = std::exchange(other.m_SouthWest, nullptr);
	m_SouthEast = std::exchange(other.m_SouthEast, nullptr);

}
template<class T> // Copy assignment
Quadtree<T>& Quadtree<T>::operator=(const Quadtree<T>& other) {
	return *this = Quadtree<T>(other);
}
template<class T> // Move assignment
Quadtree<T>& Quadtree<T>::operator=(Quadtree<T>&& other) noexcept {

	std::swap(m_Boundary, other.m_Boundary);
	std::swap(m_Capacity, other.m_Capacity);

	std::swap(m_Tenants, other.m_Tenants);
	std::swap(m_Divided, other.m_Divided);

	std::swap(m_NorthWest, other.m_NorthWest);
	std::swap(m_NorthEast, other.m_NorthEast);
	std::swap(m_SouthWest, other.m_SouthWest);
	std::swap(m_SouthEast, other.m_SouthEast);

	return *this;
}

template<class T>
bool Quadtree<T>::Insert(const QuadPoint<T> point)
{
	if (!m_Boundary.Contains(point.X, point.Y)) // If quadrant does not contain point, back out
	{
		return false;
	}

	if (m_Tenants.size() + 1 < m_Capacity && !m_Divided || m_Depth == m_MaxDepth) { // If quadrant is full and isn't already divided, divide. 							   
		m_Tenants.push_back(point);													// If at max depth just add point
		return true;
	}

	if (!m_Divided) {
		Subdivide();
	}

	if (m_Divided) { // If divided, insert point in correct child
		if (m_NorthWest->Insert(point)) return true;
		if (m_NorthEast->Insert(point)) return true;
		if (m_SouthWest->Insert(point)) return true;
		if (m_SouthEast->Insert(point)) return true;
	}
	return false;
}

template<class T>
std::vector<QuadPoint<T>> Quadtree<T>::Query(const QuadBoundary area, const int maxSize) const
{
	std::vector<QuadPoint<T>> ret; // Create a scoped vector (To avoid memory leaks) 

	if (!m_Boundary.Intersects(area.x, area.y, area.w, area.h)) { // If area is not overlapping with quadrant, back out
		return ret;
	}

	for (const QuadPoint<T>& point : m_Tenants) { // Iterate through all points, if in area add to list
		if (area.Contains(point.X, point.Y)) {
			ret.push_back(point);
		}
	}

	if (m_Divided) { // If quadrant is divided, get childrens points in area
		for (Quadtree<T>* leaf : m_Root->m_Leafs) {
			leaf->QueryRecursed(area, ret);
		}
	}

	return ret;
}

// Debug
template<class T>
void Quadtree<T>::Draw(LineRenderer* renderer)
{

	Vec2 bottomFace = Vec2(m_Boundary.w, m_Boundary.h) * -1.0f;
	Vec2 topFace = Vec2(m_Boundary.w, m_Boundary.h) * 1.0f;

	Vec2 position = Vec2(m_Boundary.x, m_Boundary.y);

	renderer->SetColour({ 1,1,1 });
	renderer->AddPointToLine(Vec2(bottomFace.x, bottomFace.y) + position);
	renderer->AddPointToLine(Vec2(bottomFace.x, topFace.y) + position);
	renderer->AddPointToLine(Vec2(topFace.x, topFace.y) + position);
	renderer->AddPointToLine(Vec2(topFace.x, bottomFace.y) + position);
	renderer->AddPointToLine(Vec2(bottomFace.x, bottomFace.y) + position);
	renderer->FinishLineLoop();

	if (m_Divided) {
		m_NorthWest->Draw(renderer);
		m_NorthEast->Draw(renderer);
		m_SouthWest->Draw(renderer);
		m_SouthEast->Draw(renderer);
	}
}

template<class T>
void Quadtree<T>::Clear() {
	m_Tenants.clear();

	m_NorthWest.reset();
	m_NorthEast.reset();
	m_SouthWest.reset();
	m_SouthEast.reset();

	m_Divided = false;

	m_Leafs.clear();
	m_Root->m_Leafs.push_back(m_Root);
}

template<class T>
void Quadtree<T>::Subdivide()
{
	QuadBoundary nwBoundary = { m_Boundary.x - m_Boundary.w * 0.5f, m_Boundary.y + m_Boundary.h * 0.5f, m_Boundary.w * 0.5f , m_Boundary.h * 0.5f }; // Create new quadrants area
	QuadBoundary neBoundary = { m_Boundary.x + m_Boundary.w * 0.5f, m_Boundary.y + m_Boundary.h * 0.5f, m_Boundary.w * 0.5f , m_Boundary.h * 0.5f }; // Create new quadrants area
	QuadBoundary swBoundary = { m_Boundary.x - m_Boundary.w * 0.5f, m_Boundary.y - m_Boundary.h * 0.5f, m_Boundary.w * 0.5f , m_Boundary.h * 0.5f }; // Create new quadrants area
	QuadBoundary seBoundary = { m_Boundary.x + m_Boundary.w * 0.5f, m_Boundary.y - m_Boundary.h * 0.5f, m_Boundary.w * 0.5f , m_Boundary.h * 0.5f }; // Create new quadrants area

	for (int i = 0; i < m_Root->m_Leafs.size(); i++) { // Remove current quadrant from leafs
		auto leafs = m_Root->m_Leafs;
		if (leafs[i] == this) {
			leafs.erase(leafs.begin(), leafs.begin() + i);
			break;
		}
	}

	m_NorthWest = std::unique_ptr<Quadtree<T>>(new Quadtree<T>(nwBoundary, m_Capacity, m_MaxDepth, m_Depth + 1, this, m_Depth > 0 ? m_Root : this));	// Make new quadrant:	North West
	m_NorthEast = std::unique_ptr<Quadtree<T>>(new Quadtree<T>(neBoundary, m_Capacity, m_MaxDepth, m_Depth + 1, this, m_Depth > 0 ? m_Root : this));	// Make new quadrant:	North East
	m_SouthWest = std::unique_ptr<Quadtree<T>>(new Quadtree<T>(swBoundary, m_Capacity, m_MaxDepth, m_Depth + 1, this, m_Depth > 0 ? m_Root : this));	// Make new quadrant:	South West
	m_SouthEast = std::unique_ptr<Quadtree<T>>(new Quadtree<T>(seBoundary, m_Capacity, m_MaxDepth, m_Depth + 1, this, m_Depth > 0 ? m_Root : this));	// Make new quadrant:	South East

	m_Divided = true; // Set divided to true

	for (int i = 0; i < m_Capacity-1; i++) { // Insert current quadrants tenants into child quads
		Insert(std::move(m_Tenants[i]));
	}

	m_Tenants.clear(); // Clear current quadrants tenants ( should be 0 by this point )
}

template<class T>
void Quadtree<T>::QueryRecursed(const QuadBoundary area, std::vector<QuadPoint<T>>& list)
{
	if (!m_Boundary.Intersects(area.x, area.y, area.w, area.h)) { // If area is not overlapping with quadrant, back out
		return;
	}

	for (const QuadPoint<T>& point : m_Tenants) { // Iterate through all points, if in area add to list
		if (area.Contains(point.X, point.Y)) {
			list.push_back(point);
		}
	}

	//if (m_Divided) { // If quadrant is divided, get childrens points in area
	//	m_NorthWest->QueryRecursed(area, list);
	//	m_NorthEast->QueryRecursed(area, list);
	//	m_SouthWest->QueryRecursed(area, list);
	//	m_SouthEast->QueryRecursed(area, list);
	//}
}





