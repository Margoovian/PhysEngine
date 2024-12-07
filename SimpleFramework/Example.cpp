#include "Example.h"
#include "imgui.h"

Example::Example()
{
	//Your initialisation code goes here!
}

void Example::Update(float delta)
{

	vel += acc * delta;
	pos += vel * delta;




	//If you want to use ImGUI to do UI stuff, you can do it here. Check out this function to see what's possible.
	//ImGui::ShowDemoWindow();


	lines->DrawCircle(pos, 0.2f, 8);


}

void Example::OnLeftClick()
{
	pos = { 0.0f, 0.0f };
	vel = { 10.0f, 10.0f };
}
