#include "Box.h"
#include "Style.h"

Box::Box()
	: Physical()
{}
Box::Box(int x, int y, int w, int h) 
	: Physical(x, y), m_Size(Vec2(w, h))
{};

void Box::Update(float delta)
{
	Calc(delta);
}

void Box::Draw(LineRenderer* renderer)
{
	Vec2 bottomFace = GetSize() * -0.5f;
	Vec2 topFace = GetSize() * 0.5f;

	SET_STATIC_COLOUR

	renderer->AddPointToLine(Vec2(bottomFace.x	,	bottomFace.y) + GetPosition());
	renderer->AddPointToLine(Vec2(bottomFace.x	,	topFace.y	) + GetPosition());
	renderer->AddPointToLine(Vec2(topFace.x		,	topFace.y	) + GetPosition());
	renderer->AddPointToLine(Vec2(topFace.x		,	bottomFace.y) + GetPosition());
	renderer->AddPointToLine(Vec2(bottomFace.x,		bottomFace.y) + GetPosition());
	renderer->FinishLineLoop();

	renderer->SetColour({ PRIMARY_COLOUR });
}

void Box::DebugDraw(LineRenderer* renderer)
{

	SET_STATIC_COLOUR

	renderer->DrawCross(GetPosition(), 0.5f);
	renderer->SetColour({ PRIMARY_COLOUR });
}

const bool Box::IsInside(const Vec2 point) const
{
	Vec2 bottomFace = (GetSize() * -0.5f) + GetPosition();
	Vec2 topFace = (GetSize() * 0.5f) + GetPosition();
	
	return
		bottomFace.x < point.x && topFace.x > point.x &&
		bottomFace.y < point.y && topFace.y > point.y;
	 
}

void Box::DrawDebugGUI()
{
	ImGui::DragFloat2("Size", &(m_Size.x), 0.05f, 1.0f, 10.0f);
}


