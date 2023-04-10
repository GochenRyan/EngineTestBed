#include "ImGuiContextInstance.h"
#include "Timer.h"

int main()
{
    uint16_t width = 1920;
    uint16_t height = 1080;
    std::unique_ptr<ImGuiContextInstance> pImGuiContext = std::make_unique<ImGuiContextInstance>(width, height);
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
        Timer::m_pTimer->UpdateFPS();
        pImGuiContext->Update(Timer::m_pTimer->GetDetTime());
    }

    return 0;
}
