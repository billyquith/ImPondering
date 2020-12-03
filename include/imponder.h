
#pragma once

#include <ponder/classbuilder.hpp>
#include <ponder/uses/runtime.hpp>
#include <imgui.h>

namespace impo {

    void showMetadata();

} // namespace impo


#ifdef IMPO_IMPLEMENTATION

namespace impo {

// Display infomation about everything registered with Ponder.
void showMetadata()
{
    ImGui::Begin("ImPo Metadata");

    for (const auto& cls : ponder::classes())
    {
        if (ImGui::CollapsingHeader(cls.name().data(), ImGuiTreeNodeFlags_None))
        {
            for (const auto& prop : cls.properties())
            {
                const char cr = prop.isReadable() ? 'R' : '.';
                const char cw = prop.isWritable() ? 'W' : '.';
                ImGui::Text("%10s : %c%c %s", prop.name().data(), cr, cw, ponder::detail::valueKindAsString(prop.kind()));
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
