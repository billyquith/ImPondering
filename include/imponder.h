
#pragma once

#include <ponder/classbuilder.hpp>
#include <ponder/uses/runtime.hpp>
#include <imgui.h>

namespace impo {

    void showMetadata();

} // namespace impo


#ifdef IMPO_IMPLEMENTATION

namespace impo {

void showMetadata()
{
    ImGui::Begin("ImPo Metadata");

    for (const auto& cls : ponder::classes())
    {
        if (ImGui::CollapsingHeader(cls.name().data(), ImGuiTreeNodeFlags_None))
        {
            for (const auto& prop : cls.properties())
            {
                ImGui::Text(prop.name().data());
            }
            for (const auto& func : cls.functions())
            {
                ImGui::Text(func.name().data());
            }
        }
    }

    ImGui::End();
}

} // namespace impo


#endif // IMPO_IMPLEMENTATION
