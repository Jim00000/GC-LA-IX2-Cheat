#include <imgui.h>
#include <imgui_internal.h>

#include "Gui/ImGuiExt.hpp"

void ImGuiExt::ToggleButton(const char* const btnId, bool* const enable)
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight() * 0.85f;
    float width = height * 2.00f;
    float radius = height * 0.50f;

    ImGui::InvisibleButton(btnId, ImVec2(width, height));
    if (ImGui::IsItemClicked())
    {
        *enable = !*enable;
    }

    float t = *enable ? 1.0f : 0.0f;

    ImGuiContext& ctx = *ImGui::GetCurrentContext();
    float ANIM_SPEED = 10.0f;
    if (ctx.LastActiveId == ctx.CurrentWindow->GetID(btnId) && ctx.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(ctx.LastActiveIdTimer * ANIM_SPEED);
        t = *enable ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 color{};
    if (ImGui::IsItemHovered())
    {
        color = ImGui::GetColorU32(*enable ?
            ImVec4(41.0f / 255.0f, 163.0f / 255.0f, 41.0f / 255.0f, 1.0f) :
            ImVec4(0.78f, 0.78f, 0.78f, 1.0f)
        );
    }
    else
    {
        color = ImGui::GetColorU32(*enable ?
            ImVec4(51.0f / 255.0f, 204.0f / 255.0f, 51.0f / 255.0f, 1.0f) :
            ImVec4(0.85f, 0.85f, 0.85f, 1.0f)
        );
    }
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), color, height * 0.50f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}