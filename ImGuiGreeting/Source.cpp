#include "ImGuiContextInstance.h"
#include "Timer.h"
#include "Window.h"
#include "imgui.h"
#include "MainMenu.h"
#include "ImGuiRenderer.h"


#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bgfx/embedded_shader.h>
#include <bx/math.h>
#include "RenderContext.h"


static bgfx::TextureHandle g_FontTexture = BGFX_INVALID_HANDLE;


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

    std::vector<std::unique_ptr<Renderer>> pEngineRenderers;

    std::unique_ptr<RenderContext> pRenderContext = std::make_unique<RenderContext>();
    pRenderContext->Init();
    pMainWindow->OnResize.Bind<RenderContext, &RenderContext::OnResize>(pRenderContext.get());

    StringCrc sceneViewRenderTargetName("SceneRenderTarget");
	std::vector<AttachmentDescriptor> attachmentDesc = {
		{ .textureFormat = TextureFormat::RGBA32F },
		{ .textureFormat = TextureFormat::RGBA32F },
		{ .textureFormat = TextureFormat::D32F },
	};

    // The init size doesn't make sense. It will resize by SceneView.
	RenderTarget* pSceneRenderTarget = pRenderContext->CreateRenderTarget(sceneViewRenderTargetName, width, height, std::move(attachmentDesc));

    // Note that if you don't want to use ImGuiRenderer for engine, you should also disable EngineImGuiContext.
	std::unique_ptr<Renderer> pRenderer = std::make_unique<ImGuiRenderer>(pRenderContext.get(), pRenderContext->CreateView(), pSceneRenderTarget);

    pRenderer->Init();
	pEngineRenderers.emplace_back(std::move(pRenderer));

    while (true)
    {
        Timer::m_pTimer->UpdateFPS();

        float deltaTime = Timer::m_pTimer->GetDetTime();

        pMainWindow->Update();
        pImGuiContext->Update(deltaTime);
        pRenderContext->BeginFrame();
        for (std::unique_ptr<Renderer>& pRenderer : pEngineRenderers)
        {
            if (!pRenderer->IsEnable())
            {
                continue;
            }

            const float* pViewMatrix = nullptr;
		    const float* pProjectionMatrix = nullptr;

            pRenderer->UpdateView(pViewMatrix, pProjectionMatrix);
		    pRenderer->Render(deltaTime);
        }

        pRenderContext->EndFrame();
    }


    return 0;
}
