#include <vector>
#include <string>

#include "UiWidgets.h"
#include "Logger.h"


namespace UIWidgets
{
	std::vector<std::string> buttons;
	std::string label;

	void Sidebar(const char* name)
	{
		ImGui::Begin(name);

		ImGui::BeginGroup();
		ImGui::PushItemWidth(ImGui::GetColumnWidth());
		if(ImGui::InputText("##", &label, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if(label != "")
			{
				buttons.push_back(label);
				label = "";
			}
		}
		ImGui::Spacing();
		if(ImGui::Button("Add Board", ImVec2(ImGui::GetColumnWidth(), 35)))
		{
			if(label != "")
			{
				buttons.push_back(label);
				label = "";
			}
		}
		ImGui::EndGroup();

		ImGui::Dummy(ImVec2(0.0f, 2.5f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 2.5f));

		ImGui::BeginGroup();

		for(auto& button : buttons)
		{
			ImGui::Button(button.c_str(), ImVec2(ImGui::GetWindowContentRegionWidth(), 50));
		}

		ImGui::EndGroup();
		ImGui::End();
	}
};
