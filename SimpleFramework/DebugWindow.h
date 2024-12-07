#pragma once
#include "imgui.h";
#include "Engine.h"
#include "CollisionInfo.h"

#include "Body.h"
#include "Physical.h"

#include <string>

enum class DebugSpawnType {
	None = -1,
	Circle, Box, Plane
};

struct DebugSpawnPacket {
	DebugSpawnType Type = DebugSpawnType::Circle;
	Vec2 Velocity = Vec2(0,0);
	Vec2 Size = Vec2(1,1);
	Vec2 Normal = Vec2(1, 0);
	float Radius = 1.0f;
	float Displacement = 0.0f;

	const char* const Selection[3]{ "Circle", "Box", "Plane" };
};

class DebugWindow {

public:
	static void Draw(Engine& engine, bool* open) {
		ImGui::Begin("Debug Window", open);

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Spawner");
		ImGui::Indent();
		ImGui::BeginGroup();

		static const char* currentItem = spawn_Packet.Selection[0];

		if (ImGui::BeginCombo("Type", currentItem)) {
		
			for (int n = 0; n < IM_ARRAYSIZE(spawn_Packet.Selection); n++)
			{
				bool is_selected = (currentItem == spawn_Packet.Selection[n]);
				if (ImGui::Selectable(spawn_Packet.Selection[n], is_selected)) {
					currentItem = spawn_Packet.Selection[n];
					spawn_Packet.Type = (DebugSpawnType)n;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();

		};

		switch (spawn_Packet.Type) {
		case DebugSpawnType::Circle:
			ImGui::DragFloat2("Velocity", &(spawn_Packet.Velocity.x), 0.05f);
			ImGui::DragFloat("Radius", &spawn_Packet.Radius, 0.05f);
			ImGui::DragFloat2("Position", &(engine.cursorPos.x), 0.05f);

			break;
		case DebugSpawnType::Box:
			ImGui::DragFloat2("Velocity", &(spawn_Packet.Velocity.x), 0.05f);
			ImGui::DragFloat2("Size", &(spawn_Packet.Size.x), 0.05f);
			ImGui::DragFloat2("Position", &(engine.cursorPos.x), 0.05f);

			break;
		case DebugSpawnType::Plane:
			ImGui::DragFloat2("Normal", &(spawn_Packet.Normal.x), 0.05f, -1.0f, 1.0f);
			ImGui::DragFloat("Displacement", &(spawn_Packet.Displacement), 0.05f);	
			spawn_Packet.Normal = glm::normalize(spawn_Packet.Normal);
			break;
		default: break;
		}

		ImGui::EndGroup();
		ImGui::Unindent();

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Constants");
		ImGui::Indent();
		ImGui::BeginGroup();

		ImGui::DragFloat("Gravity", &Environment::s_Gravity,0.1f);
		ImGui::DragFloat("Elasticity", &Environment::s_Elasticity,0.05f, 0.0f, 1.0f);

		ImGui::EndGroup();
		ImGui::Unindent();

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Objects");	
		if (ImGui::TreeNode("Static")) { 
			DrawObjectsDropdown(engine, engine.m_Objects.size(), true);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Dynamic")) {
			DrawObjectsDropdown(engine, engine.m_Objects.size());
			ImGui::TreePop();
		}

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "CollisionInfo");
		ImGui::Indent();
		ImGui::BeginGroup();
		ImGui::InputFloat2("ObjectA Depenetration", &(CollisionInfo::DEBUG_PosChangeA.x));
		ImGui::InputFloat2("ObjectB Depenetration", &(CollisionInfo::DEBUG_PosChangeB.x));
		ImGui::EndGroup();
		ImGui::Unindent();

		ImGui::End();
	}

	
	static const DebugSpawnPacket GetSpawnPacket() {
		return spawn_Packet;
	}

private:

	static DebugSpawnPacket spawn_Packet;

	static void DrawObjectsDropdown(Engine& engine, const int count, const bool isStatic = false) {
		for (int i = 0; i < count; i++) {
			std::stringstream ss;

			Physical* physical = dynamic_cast<Physical*>(engine.m_Objects[i]);

			if (physical == nullptr && isStatic == false) continue;
			else if (physical != nullptr && isStatic == true) continue;

			ss << "Object " << i << " ( " << typeid(*engine.m_Objects[i]).name() << " )";
			if (ImGui::CollapsingHeader(ss.str().c_str())) {

				ImGui::BeginGroup();
				ImGui::PushID(i);
				ImGui::Indent();
				Body* body = engine.m_Objects[i];

				if (physical == nullptr) {}
				else {
					ImGui::Text("Generic Properties");
					ImGui::Checkbox("Is Anchored", &physical->m_Anchored); ImGui::SameLine();
					ImGui::Checkbox("Preserve Motion", &physical->m_PreserveMotion);
					ImGui::Text("Mass: "); ImGui::SameLine(); ImGui::Text(std::to_string(physical->GetMass()).c_str());
					ImGui::SameLine();
					ImGui::Text("InvMass: "); ImGui::SameLine(); ImGui::Text(std::to_string(physical->GetInvMass()).c_str());
					ImGui::DragFloat2("Velocity", &(physical->m_Velocity.x));
					ImGui::DragFloat2("Position", &(physical->m_Position.x));
					ImGui::DragFloat2("Acceleration", &(physical->m_Acceleration.x));				
				}
				ImGui::Text("Object Properties");
				engine.m_Objects[i]->DrawDebugGUI();
				

				ImGui::Unindent();
				ImGui::PopID();
				ImGui::EndGroup();
			}
		}
	}
};


DebugSpawnPacket DebugWindow::spawn_Packet;