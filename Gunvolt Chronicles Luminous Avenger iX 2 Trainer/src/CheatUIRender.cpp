#include <imgui.h>
#include "CheatUIRender.hpp"
#include "Gui/ImGuiExt.hpp"

using namespace GCLAX2;

CheatUIRender::~CheatUIRender() noexcept
{
}

void CheatUIRender::render() noexcept
{
    ImGui::Begin("Gunvolt Chronicles Luminous Avenger iX 2");

    if (ImGui::TreeNode("Pointer"))
    {
        ImGui::Checkbox("HP", &this->fixedHP_);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Script"))
    {
        ImGui::TreePop();
    }

    ImGui::End();
}

std::shared_ptr<CheatUIRender> Singleton<CheatUIRender>::obj = nullptr;