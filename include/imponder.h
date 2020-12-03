
#pragma once

#include <ponder/classbuilder.hpp>
#include <ponder/uses/runtime.hpp>
#include <imgui.h>

namespace impo {

    void showMetadata();

    class Editor
    {
    public:
        Editor();
        ~Editor();

        template <typename T>
        void edit(T& obj);
    };

    template <typename T>
    inline void Editor::edit(T& obj)
    {
        const ponder::Class& cls{ ponder::classByType<T>() };
        ponder::UserObject uobj(&obj);

        for (const auto& prop : cls.properties())
        {
            ponder::Value val = prop.get(uobj);
            ImGui::Text("%s = %s", prop.name().data(), val.to<std::string>().data());
        }
    }
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

Editor::Editor()
{
    ImGui::Begin("Editor");
}

Editor::~Editor()
{
    ImGui::End();
}

} // namespace impo

#endif // IMPO_IMPLEMENTATION
