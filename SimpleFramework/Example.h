#pragma once

#include "Application.h"
#include "Maths.h"

class Example : public Application
{
public:

	Vec2 pos = { 0.0f, 0.0f };
	Vec2 vel = { 0.0f, 0.0f };
	Vec2 acc = { 0.0f, -9.81f };

	Example();

	virtual void Update(float delta) override;

	void OnLeftClick() override;

};