#include "ImGuiContextInstance.h"
#include "Timer.h"
#include "Window.h"
#include "imgui.h"
#include "MainMenu.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

int main()
{
    uint16_t width = 1024;
    uint16_t height = 768;
    std::unique_ptr<Window> pMainWindow = std::make_unique<Window>("TesT Bench", width, height);
    std::unique_ptr<ImGuiContextInstance> pImGuiContext = std::make_unique<ImGuiContextInstance>(width, height);
    pMainWindow->OnResize.Bind<ImGuiContextInstance, &ImGuiContextInstance::OnResize>(pImGuiContext.get());
    std::vector<std::string> ttfFileNames = { "FanWunMing-SB.ttf" };
	pImGuiContext->LoadFontFiles(ttfFileNames, Language::ChineseSimplied);

    pImGuiContext->AddStaticLayer(std::make_unique<MainMenu>("MainMenu"));

    if (!Timer::m_pTimer)
	{
		Timer * pTimer = new Timer();
		if (!pTimer)
		{
			return false;
		}
	}

	bgfx::init();

    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = pMainWindow->GetNativeHandle();
    bgfx::setPlatformData(pd);

    bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));

    // ImGui_Implbgfx_Init();

    while (true)
    {
        pMainWindow->Update();

        //ImGui_Implbgfx_NewFrame();

        Timer::m_pTimer->UpdateFPS();
        pImGuiContext->Update(Timer::m_pTimer->GetDetTime());

        {
			ImGui::Begin("widget_1");
			ImGui::Text("text_1");
			//ImGui::SameLine();
			ImGui::Indent();
			ImGui::Button("2222", ImVec2(100, 50));
            ImGui::End();
		}

        ImGui::Render();
	    ImGui::UpdatePlatformWindows();
	    ImGui::RenderPlatformWindowsDefault();

        //// Submit ImGui rendering commands
        //bgfx::submit(0, ImGui_Implbgfx_GetDrawList());
        bgfx::frame();
    }

    //// Destroy ImGui renderer
    //ImGui_Implbgfx_Shutdown();

    bgfx::shutdown();

    return 0;
}
