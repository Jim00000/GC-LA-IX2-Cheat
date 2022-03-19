#include <imgui.h>
#include "CheatUIRender.hpp"
#include "Gui/ImGuiExt.hpp"
#include "Helper/ProcessInformation.hpp"
#include "Helper/Pointer.hpp"

using namespace GCLAX2;

CheatUIRender::CheatUIRender() noexcept
{
    ProcessInformation procInfo{};
    unsigned char* gameBaseAddr = procInfo.getProcessBaseAddress();

    /*
    this->HP_ = Pointer{ gameBaseAddr }
        .offset(0x01896630).dereference()
        .offset(0x2C0).dereference()
        .offset(0x168).dereference()
        .offset(0x28).dereference()
        .offset(0x30).to<float*>();
    */
}

CheatUIRender::~CheatUIRender() noexcept
{
}

void CheatUIRender::render() noexcept
{
    ImGui::Begin("Gunvolt Chronicles Luminous Avenger iX 2");

    if (ImGui::TreeNode("Pointer"))
    {
        ImGui::Checkbox("##HP", &this->fixedHP_);
        ImGui::SameLine();
        ImGui::Text("HP");
        ImGui::SameLine();
        if (this->HP_ != nullptr)
        {
            ImGui::InputFloat("##HP_inputfloat", this->HP_);
        }
        else
        {
            float trivial_hp = 0;
            ImGui::InputFloat("##HP_inputfloat", &trivial_hp);
            try 
            {
                ProcessInformation procInfo{};
                unsigned char* gameBaseAddr = procInfo.getProcessBaseAddress();
                this->HP_ = Pointer{ gameBaseAddr }
                    .offset(0x01896630).dereference()
                    .offset(0x2C0).dereference()
                    .offset(0x168).dereference()
                    .offset(0x28).dereference()
                    .offset(0x30).to<float*>();
            }
            catch (...) 
            {
                this->HP_ = nullptr;
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Script"))
    {
        ImGui::TreePop();
    }
  

    ImGui::End();
}

std::shared_ptr<CheatUIRender> Singleton<CheatUIRender>::obj = nullptr;