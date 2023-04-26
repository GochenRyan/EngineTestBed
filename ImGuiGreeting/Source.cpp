#include "ImGuiContextInstance.h"
#include "Timer.h"
#include "Window.h"
#include "imgui.h"
#include "MainMenu.h"

#include "shader/vs_ocornut_imgui.bin.h"
#include "shader/fs_ocornut_imgui.bin.h"
#include "shader/vs_imgui_image.bin.h"
#include "shader/fs_imgui_image.bin.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bgfx/embedded_shader.h>

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
    BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER(vs_imgui_image),
    BGFX_EMBEDDED_SHADER(fs_imgui_image),

    BGFX_EMBEDDED_SHADER_END()
};

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

    bgfx::Init initDesc;
    initDesc.type = bgfx::RendererType::Direct3D11;
    bgfx::init(initDesc);

    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = pMainWindow->GetNativeHandle();
    bgfx::setPlatformData(pd);

    //bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setDebug(BGFX_DEBUG_NONE);
    bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
    bgfx::setViewClear(0
        , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
        , 0x303030ff
        , 1.0f
        , 0
    );

    // ImGui_Implbgfx_Init();


    bgfx::RendererType::Enum type = bgfx::getRendererType();
    bgfx::ProgramHandle program = bgfx::createProgram(
        bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_ocornut_imgui")
        , bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_ocornut_imgui")
        , true
    );

    bgfx::UniformHandle imageLodEnabled = bgfx::createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);
    bgfx::ProgramHandle imageProgram = bgfx::createProgram(
        bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_image")
        , bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_image")
        , true
    );
    
    bgfx::VertexLayout m_layout;

    m_layout
        .begin()
        .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();

    bgfx::UniformHandle tex = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "imgui_impl_bgfx";
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
    io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;  // We can create multi-viewports on the Renderer side (optional)


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

        // ImGuiRenderer will be used by different ImGuiContext which has different font settings.
        // Shares the same font atlas now to save memory.
        // TODO : support different fonts in different ImGuiContext.
        if (!bgfx::isValid(g_FontTexture))
        {
            ImFontAtlas* pFontAtlas = ImGui::GetIO().Fonts;
            assert(pFontAtlas->IsBuilt() && "The ImGui font atlas should be already built successfully.");
            uint8_t* pFontAtlasData;
            int32_t fontAtlasWidth;
            int32_t fontAtlasHeight;
            pFontAtlas->GetTexDataAsRGBA32(&pFontAtlasData, &fontAtlasWidth, &fontAtlasHeight);
            g_FontTexture = bgfx::createTexture2D(static_cast<uint16_t>(fontAtlasWidth), static_cast<uint16_t>(fontAtlasHeight), false, 1,
                bgfx::TextureFormat::BGRA8, 0, bgfx::copy(pFontAtlasData, fontAtlasWidth * fontAtlasHeight * 4));
            bgfx::setName(g_FontTexture, "font_atlas");
        }

        ImGui::Render();
	    ImGui::UpdatePlatformWindows();
	    ImGui::RenderPlatformWindowsDefault();

        bgfx::setViewMode(0, bgfx::ViewMode::Sequential);

        const ImDrawData* pImGuiDrawData = ImGui::GetDrawData();
        float x = pImGuiDrawData->DisplayPos.x;
        float y = pImGuiDrawData->DisplayPos.y;
        float width = pImGuiDrawData->DisplaySize.x;
        float height = pImGuiDrawData->DisplaySize.y;
        const bgfx::Caps* pCapabilities = bgfx::getCaps();

        // Set view 0 default viewport.
        bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));

        for (int32_t commandListIndex = 0, numCommandLists = pImGuiDrawData->CmdListsCount; commandListIndex < numCommandLists; ++commandListIndex)
        {
            const ImDrawList* pDrawList = pImGuiDrawData->CmdLists[commandListIndex];

            uint32_t numVertices = static_cast<uint32_t>(pDrawList->VtxBuffer.size());
            uint32_t numIndices = static_cast<uint32_t>(pDrawList->IdxBuffer.size());
            const bool vertexBufferAvaiable = (numVertices == bgfx::getAvailTransientVertexBuffer(numVertices, m_layout));
            const bool indexBufferAvaiable = (0 == numIndices || numIndices == bgfx::getAvailTransientIndexBuffer(numIndices));
            if (!vertexBufferAvaiable || !indexBufferAvaiable)
            {
                // not enough space in transient buffer just quit drawing the rest...
                break;
            }

            bgfx::TransientVertexBuffer vertexBuffer;
            bgfx::TransientIndexBuffer indexBuffer;
            bgfx::allocTransientVertexBuffer(&vertexBuffer, numVertices, m_layout);
            bgfx::allocTransientIndexBuffer(&indexBuffer, numIndices, std::is_same<uint32_t, ImDrawIdx>());

            ImDrawVert* pVertices = reinterpret_cast<ImDrawVert*>(vertexBuffer.data);
            std::memcpy(pVertices, pDrawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert));

            ImDrawIdx* pIndices = reinterpret_cast<ImDrawIdx*>(indexBuffer.data);
            std::memcpy(pIndices, pDrawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx));

            bgfx::Encoder* pEncoder = bgfx::begin();

            for (const ImDrawCmd* cmd = pDrawList->CmdBuffer.begin(), *cmdEnd = pDrawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd)
            {
                if (cmd->UserCallback)
                {
                    cmd->UserCallback(pDrawList, cmd);
                }
                else if (0 != cmd->ElemCount)
                {
                    uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA;
                    bgfx::TextureHandle textureHandle;
                    if (nullptr != cmd->TextureId)
                    {
                        union
                        {
                            ImTextureID ptr;
                            struct
                            {
                                bgfx::TextureHandle handle;
                                uint8_t flags;
                                uint8_t mip;
                            } s;
                        } texture = { cmd->TextureId };
                        textureHandle = texture.s.handle;
                    }
                    else
                    {
                        textureHandle = g_FontTexture;
                        state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
                    }

                    const ImVec2 clipPos = pImGuiDrawData->DisplayPos;			// (0,0) unless using multi-viewports
                    const ImVec2 clipScale = pImGuiDrawData->FramebufferScale;  // (1,1) unless using retina display which are often (2,2)

                    // Project scissor/clipping rectangles into framebuffer space
                    ImVec4 clipRect;
                    clipRect.x = (cmd->ClipRect.x - clipPos.x) * clipScale.x;
                    clipRect.y = (cmd->ClipRect.y - clipPos.y) * clipScale.y;
                    clipRect.z = (cmd->ClipRect.z - clipPos.x) * clipScale.x;
                    clipRect.w = (cmd->ClipRect.w - clipPos.y) * clipScale.y;

                    int frameBufferWidth = static_cast<int>(pImGuiDrawData->DisplaySize.x * pImGuiDrawData->FramebufferScale.x);
                    int frameBufferHeight = static_cast<int>(pImGuiDrawData->DisplaySize.y * pImGuiDrawData->FramebufferScale.y);

                    if (clipRect.x < frameBufferWidth &&
                        clipRect.y < frameBufferHeight &&
                        clipRect.z >= 0.0f &&
                        clipRect.w >= 0.0f)
                    {
                        const uint16_t xx = static_cast<uint16_t>(std::max(clipRect.x, 0.0f));
                        const uint16_t yy = static_cast<uint16_t>(std::max(clipRect.y, 0.0f));
                        pEncoder->setScissor(xx, yy, uint16_t(std::min(clipRect.z, 65535.0f) - xx), uint16_t(std::min(clipRect.w, 65535.0f) - yy));

                        pEncoder->setState(state);

                        pEncoder->setTexture(0, tex, textureHandle);

                        pEncoder->setVertexBuffer(0, &vertexBuffer, cmd->VtxOffset, numVertices);
                        pEncoder->setIndexBuffer(&indexBuffer, cmd->IdxOffset, cmd->ElemCount);

                        pEncoder->submit(0, program);
                    }
                }
            }

            bgfx::end(pEncoder);
        }



        // This dummy draw call is here to make sure that view 0 is cleared
        // if no other draw calls are submitted to view 0.
        bgfx::touch(0);


        //// Submit ImGui rendering commands
        //bgfx::submit(0, ImGui_Implbgfx_GetDrawList());
        bgfx::frame();
    }

    //// Destroy ImGui renderer
    //ImGui_Implbgfx_Shutdown();

    bgfx::destroy(imageLodEnabled);
    bgfx::destroy(imageProgram);
    bgfx::destroy(program);
    bgfx::shutdown();

    return 0;
}
