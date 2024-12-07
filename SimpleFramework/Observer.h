#pragma once

#include "CollisionInfo.h"
#include "CollisionEvents.h"

#include <typeinfo>
#include <unordered_map>
#include <functional>

typedef std::pair<BodyType, BodyType> BodyKey;

class Observer {
public:

	Observer();
	static Observer s_Observer;

	void* GetFunction(Body* body1, Body* body2) {
		return functionMap[BodyKey(body1->GetType(), body2->GetType())];
	}

private:
	struct CollisionHasher
	{
		std::size_t operator()(const BodyKey& key) const
		{
			return 1 << (int)key.first | 1 << (int)key.second + 8;
		}
	};

	struct CollisionEqualTo
	{
		bool operator()(BodyKey lhs, BodyKey rhs) const
		{
			return (1 << (int)lhs.first | 1 << (int)lhs.second + 8) == (1 << (int)rhs.first | 1 << (int)rhs.second + 8);
		}
	};

	std::unordered_map< BodyKey, void*, CollisionHasher, CollisionEqualTo> functionMap;

};
