#include "ImGuiContextInstance.h"
#include "Timer.h"
#include "Window.h"
#include "imgui.h"

int main()
{
    uint16_t width = 1920;
    uint16_t height = 1080;
    std::unique_ptr<Window> pMainWindow = std::make_unique<Window>("TesT Bench", width, height);
    std::unique_ptr<ImGuiContextInstance> pImGuiContext = std::make_unique<ImGuiContextInstance>(width, height);
    pMainWindow->OnResize.Bind<ImGuiContextInstance, &ImGuiContextInstance::OnResize>(pImGuiContext.get());
    std::vector<std::string> ttfFileNames = { "FanWunMing-SB.ttf" };
	pImGuiContext->LoadFontFiles(ttfFileNames, Language::ChineseSimplied);

    if (!Timer::m_pTimer)
	{
		Timer * pTimer = new Timer();
		if (!pTimer)
		{
			return false;
		}
	}

    while (true)
    {
        pMainWindow->Update();
        Timer::m_pTimer->UpdateFPS();
        pImGuiContext->Update(Timer::m_pTimer->GetDetTime());
        ImGui::Render();
	    ImGui::UpdatePlatformWindows();
	    ImGui::RenderPlatformWindowsDefault();
    }

    return 0;
}
