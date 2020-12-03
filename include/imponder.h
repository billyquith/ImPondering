
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

    for (const auto& cls : ponder::classIterator())
    {
        ImGui::Text(cls.second->name().data());
    }

    ImGui::End();
}

} // namespace impo


#endif // IMPO_IMPLEMENTATION
