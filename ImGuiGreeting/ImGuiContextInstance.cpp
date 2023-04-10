#include "ImGuiContextInstance.h"

#include "IconsMaterialDesignIcons.h"
#include "MaterialDesign.inl"
#include "ImGuiBaseLayer.h"
#include "Input.h"
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <misc/freetype/imgui_freetype.h>

#include <string>
#include <unordered_map>

std::unordered_map<KeyCode, ImGuiKey> kImguiKeyLookup {
	{KeyCode::RETURN, ImGuiKey::ImGuiKey_Enter},
	{KeyCode::ESCAPE, ImGuiKey::ImGuiKey_Escape},
	{KeyCode::BACKSPACE, ImGuiKey::ImGuiKey_Backspace},
	{KeyCode::TAB, ImGuiKey::ImGuiKey_Tab},
	{KeyCode::SPACE, ImGuiKey::ImGuiKey_Space},
	// {KeyCode::EXCLAIM, ImGuiKey::ImGuiKey_}, 
	// {KeyCode::QUOTEDBL, ImGuiKey::ImGuiKey_},
	// {KeyCode::HASH, ImGuiKey::ImGuiKey_},
	// {KeyCode::PERCENT, ImGuiKey::ImGuiKey_},
	// {KeyCode::DOLLAR, ImGuiKey::ImGuiKey_},
	// {KeyCode::AMPERSAND, ImGuiKey::ImGuiKey_},
	{KeyCode::QUOTE, ImGuiKey::ImGuiKey_Apostrophe},
	// {KeyCode::LEFTPAREN, ImGuiKey::ImGuiKey_},
	// {KeyCode::RIGHTPAREN, ImGuiKey::ImGuiKey_},
	// {KeyCode::ASTERISK, ImGuiKey::ImGuiKey_},
	// {KeyCode::PLUS, ImGuiKey::ImGuiKey_},
	{KeyCode::COMMA, ImGuiKey::ImGuiKey_Comma},
	{KeyCode::MINUS, ImGuiKey::ImGuiKey_Minus},
	{KeyCode::PERIOD, ImGuiKey::ImGuiKey_Period},
	{KeyCode::SLASH, ImGuiKey::ImGuiKey_Slash},
	{KeyCode::NUM_0, ImGuiKey::ImGuiKey_0},
	{KeyCode::NUM_1, ImGuiKey::ImGuiKey_1},
	{KeyCode::NUM_2, ImGuiKey::ImGuiKey_2},
	{KeyCode::NUM_3, ImGuiKey::ImGuiKey_3},
	{KeyCode::NUM_4, ImGuiKey::ImGuiKey_4},
	{KeyCode::NUM_5, ImGuiKey::ImGuiKey_5},
	{KeyCode::NUM_6, ImGuiKey::ImGuiKey_6},
	{KeyCode::NUM_7, ImGuiKey::ImGuiKey_7},
	{KeyCode::NUM_8, ImGuiKey::ImGuiKey_8},
	{KeyCode::NUM_9, ImGuiKey::ImGuiKey_9},
	// {KeyCode::COLON, ImGuiKey::ImGuiKey_},
	{KeyCode::SEMICOLON, ImGuiKey::ImGuiKey_Semicolon},
	// {KeyCode::LESS, ImGuiKey::ImGuiKey_},
	{KeyCode::EQUALS, ImGuiKey::ImGuiKey_Equal},
	// {KeyCode::GREATER, ImGuiKey::ImGuiKey_},
	// {KeyCode::QUESTION, ImGuiKey::ImGuiKey_},
	// {KeyCode::AT, ImGuiKey::ImGuiKey_},
	{KeyCode::LEFTBRACKET, ImGuiKey::ImGuiKey_LeftBracket},
	{KeyCode::BACKSLASH, ImGuiKey::ImGuiKey_Backslash},
	{KeyCode::RIGHTBRACKET, ImGuiKey::ImGuiKey_RightBracket},
	// {KeyCode::CARET, ImGuiKey::ImGuiKey_},
	// {KeyCode::UNDERSCORE, ImGuiKey::ImGuiKey_},
	{KeyCode::BACKQUOTE, ImGuiKey::ImGuiKey_GraveAccent},
	{KeyCode::a, ImGuiKey::ImGuiKey_A},
	{KeyCode::b, ImGuiKey::ImGuiKey_B},
	{KeyCode::c, ImGuiKey::ImGuiKey_C},
	{KeyCode::d, ImGuiKey::ImGuiKey_D},
	{KeyCode::e, ImGuiKey::ImGuiKey_E},
	{KeyCode::f, ImGuiKey::ImGuiKey_F},
	{KeyCode::g, ImGuiKey::ImGuiKey_G},
	{KeyCode::h, ImGuiKey::ImGuiKey_H},
	{KeyCode::i, ImGuiKey::ImGuiKey_I},
	{KeyCode::j, ImGuiKey::ImGuiKey_J},
	{KeyCode::k, ImGuiKey::ImGuiKey_K},
	{KeyCode::l, ImGuiKey::ImGuiKey_L},
	{KeyCode::m, ImGuiKey::ImGuiKey_M},
	{KeyCode::n, ImGuiKey::ImGuiKey_N},
	{KeyCode::o, ImGuiKey::ImGuiKey_O},
	{KeyCode::p, ImGuiKey::ImGuiKey_P},
	{KeyCode::q, ImGuiKey::ImGuiKey_Q},
	{KeyCode::r, ImGuiKey::ImGuiKey_R},
	{KeyCode::s, ImGuiKey::ImGuiKey_S},
	{KeyCode::t, ImGuiKey::ImGuiKey_T},
	{KeyCode::u, ImGuiKey::ImGuiKey_U},
	{KeyCode::v, ImGuiKey::ImGuiKey_V},
	{KeyCode::w, ImGuiKey::ImGuiKey_W},
	{KeyCode::x, ImGuiKey::ImGuiKey_X},
	{KeyCode::y, ImGuiKey::ImGuiKey_Y},
	{KeyCode::z, ImGuiKey::ImGuiKey_Z},
};

std::unordered_map<KeyMod, ImGuiKey> kImguiKeyModToImGuiKeyLookup{
	{KeyMod::KMOD_LSHIFT, ImGuiKey::ImGuiKey_LeftShift},
	{KeyMod::KMOD_RSHIFT, ImGuiKey::ImGuiKey_RightShift},
	{KeyMod::KMOD_LCTRL, ImGuiKey::ImGuiKey_LeftCtrl},
	{KeyMod::KMOD_RCTRL, ImGuiKey::ImGuiKey_RightCtrl},
	{KeyMod::KMOD_LALT, ImGuiKey::ImGuiKey_LeftAlt},
	{KeyMod::KMOD_RALT, ImGuiKey::ImGuiKey_RightAlt},
	{KeyMod::KMOD_LGUI, ImGuiKey::ImGuiKey_LeftSuper},
	{KeyMod::KMOD_RGUI, ImGuiKey::ImGuiKey_RightSuper},
	{KeyMod::KMOD_NUM, ImGuiKey::ImGuiKey_NumLock},
	{KeyMod::KMOD_CAPS, ImGuiKey::ImGuiKey_CapsLock},
	{KeyMod::KMOD_MODE, ImGuiKey::ImGuiKey_ModSuper},
	{KeyMod::KMOD_SCROLL, ImGuiKey::ImGuiKey_ScrollLock},
};

std::unordered_map<KeyMod, ImGuiKey> kImguiKeyModToImGuiModLookup{
	{KeyMod::KMOD_NONE, ImGuiKey::ImGuiMod_None},
	{KeyMod::KMOD_LSHIFT, ImGuiKey::ImGuiMod_Shift},
	{KeyMod::KMOD_RSHIFT, ImGuiKey::ImGuiMod_Shift},
	{KeyMod::KMOD_LCTRL, ImGuiKey::ImGuiMod_Ctrl},
	{KeyMod::KMOD_RCTRL, ImGuiKey::ImGuiMod_Ctrl},
	{KeyMod::KMOD_LALT, ImGuiKey::ImGuiMod_Alt},
	{KeyMod::KMOD_RALT, ImGuiKey::ImGuiMod_Alt},
	{KeyMod::KMOD_LGUI, ImGuiKey::ImGuiMod_Super},
	{KeyMod::KMOD_RGUI, ImGuiKey::ImGuiMod_Super},
	{KeyMod::KMOD_CTRL, ImGuiKey::ImGuiMod_Ctrl},
	{KeyMod::KMOD_SHIFT, ImGuiKey::ImGuiMod_Shift},
	{KeyMod::KMOD_ALT, ImGuiKey::ImGuiMod_Alt},
	{KeyMod::KMOD_GUI, ImGuiKey::ImGuiMod_Super},
};

// ImGui has a static global ImGuiContext* which points to current active ImGuiContext.
// And almost all ImGui apis assume that the api call will affect current active ImGuiContext.
// 
// As we have multiple ImGuiContext instances so you need to use ImGui correctly by two solutions:
// 1. Create a TempSwitchContextScope variable before calling any ImGui API. It will switch context temporarily for you automatically.
// It is a convenient way to develop features but it will waste a little performance on switching context.
// 
// 2. Don't use any ImGui apis to finish your work. Instead, you should use m_pImGuiContext to call API.
// It is an advance way to save performances but you are easy to cause bugs if you forgot to use ImGui api.
// For example, ImGui::GetIO() returns current active context's IO. Instead, you should use m_pImGuiContext->IO.
//
// I recommend that you use TempSwitchContextScope in some functions which doesn't call frequently or the logic is too complex to write many codes.
//
class TempSwitchContextScope
{
public:
	TempSwitchContextScope(ImGuiContextInstance* pThis)
	{
		ImGuiIO& io = ImGui::GetIO();
		assert(io.UserData != nullptr && "Please set ImGuiContextInstance to io.UserData field.");
		if (io.UserData != pThis)
		{
			pThis->SwitchCurrentContext();
			pBackContext = reinterpret_cast<ImGuiContextInstance*>(io.UserData);
		}
	}

	~TempSwitchContextScope()
	{
		if (pBackContext)
		{
			pBackContext->SwitchCurrentContext();
		}
	}

	// Disable Copy/Move as it is just a simple scope object to switch ImGui contexts.
	TempSwitchContextScope(const TempSwitchContextScope&) = delete;
	TempSwitchContextScope& operator=(const TempSwitchContextScope&) = delete;
	TempSwitchContextScope(TempSwitchContextScope&&) = delete;
	TempSwitchContextScope& operator=(TempSwitchContextScope&&) = delete;

private:
	ImGuiContextInstance* pBackContext = nullptr;
};


ImGuiContextInstance::ImGuiContextInstance(uint16_t width, uint16_t height, bool enableDock)
{
	m_pImGuiContext = ImGui::CreateContext();
	SwitchCurrentContext();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.UserData = this;

	if (enableDock)
	{
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}

	// TODO
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

	SetImGuiStyles();
}

ImGuiContextInstance::~ImGuiContextInstance()
{
	ImGui::DestroyContext(m_pImGuiContext);
}

void ImGuiContextInstance::SwitchCurrentContext() const
{
	ImGui::SetCurrentContext(m_pImGuiContext);
}

bool ImGuiContextInstance::IsActive() const
{
	return ImGui::GetCurrentContext() == m_pImGuiContext;
}

void ImGuiContextInstance::AddStaticLayer(std::unique_ptr<ImGuiBaseLayer> pLayer)
{
	pLayer->Init();
	m_pImGuiStaticLayers.emplace_back(std::move(pLayer));
}

void ImGuiContextInstance::AddDynamicLayer(std::unique_ptr<ImGuiBaseLayer> pLayer)
{
	pLayer->Init();
	m_pImGuiDockableLayers.emplace_back(std::move(pLayer));
}

void ImGuiContextInstance::BeginDockSpace()
{
	// To create a dock space, we need to create a window to host it at first.
	constexpr const char* pDockSpaceName = "FullScreenDockSpace";
	static bool enableDockSpace = true;
	constexpr ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_NoDocking |
													  ImGuiWindowFlags_NoTitleBar |
													  ImGuiWindowFlags_NoCollapse |
													  ImGuiWindowFlags_NoResize |
													  ImGuiWindowFlags_NoMove |
													  ImGuiWindowFlags_NoBringToFrontOnFocus |
													  ImGuiWindowFlags_NoNavFocus |
													  ImGuiWindowFlags_NoBackground;

	// Place dock space window under static imgui layers.
	// It is a hack now as only main menu bar is a static layer so we only need to adjust the height.
	// If we have more static layers, we need to calculate their accurate areas.
	ImGuiViewport* pMainViewport = ImGui::GetMainViewport();
	assert(pMainViewport && "The main viewport cannot be null");
	const float mainMenuBarSize = ImGui::GetFrameHeight();
	ImVec2 dockSpacePos = pMainViewport->Pos;
	dockSpacePos.y += mainMenuBarSize;
	ImVec2 dockSpaceSize = pMainViewport->Size;
	dockSpaceSize.y -= mainMenuBarSize;
	ImGui::SetNextWindowPos(dockSpacePos);
	ImGui::SetNextWindowSize(dockSpaceSize);
	ImGui::SetNextWindowViewport(pMainViewport->ID);

	// Create the dock space host window.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(pDockSpaceName, &enableDockSpace, dockSpaceWindowFlags);
	ImGui::PopStyleVar(3);

	// Build other child dock spaces in the window.
	ImGuiID dockSpaceWindowID = ImGui::GetID(pDockSpaceName);
	if (!ImGui::DockBuilderGetNode(dockSpaceWindowID))
	{
		ImGui::DockBuilderRemoveNode(dockSpaceWindowID);
		ImGui::DockBuilderAddNode(dockSpaceWindowID);
		ImGui::DockBuilderSetNodeSize(dockSpaceWindowID, ImGui::GetIO().DisplaySize * ImGui::GetIO().DisplayFramebufferScale);

		ImGuiID dockSpaceMainID = dockSpaceWindowID;

		ImGuiID dockSpaceUp = ImGui::DockBuilderSplitNode(dockSpaceMainID, ImGuiDir_Up, 0.7f, nullptr, &dockSpaceMainID);
		ImGuiID dockSpaceBottom = ImGui::DockBuilderSplitNode(dockSpaceMainID, ImGuiDir_Down, 0.3f, nullptr, &dockSpaceMainID);

		ImGuiID dockSpaceUpLeft = ImGui::DockBuilderSplitNode(dockSpaceUp, ImGuiDir_Left, 0.7f, nullptr, &dockSpaceUp);
		ImGuiID dockSpaceUpLeftLeft = ImGui::DockBuilderSplitNode(dockSpaceUpLeft, ImGuiDir_Left, 0.3f, nullptr, &dockSpaceUpLeft);
		ImGuiID dockSpaceUpRight = ImGui::DockBuilderSplitNode(dockSpaceUp, ImGuiDir_Right, 0.3f, nullptr, &dockSpaceUp);

		ImGuiID dockSpaceLeftLeft = ImGui::DockBuilderSplitNode(dockSpaceUpLeft, ImGuiDir_Left, 0.5f, nullptr, &dockSpaceUpLeft);
		ImGuiID dockSpaceLeftRight = ImGui::DockBuilderSplitNode(dockSpaceUpLeft, ImGuiDir_Right, 0.5f, nullptr, &dockSpaceUpLeft);

		ImGuiID dockSpaceBottomLeft = ImGui::DockBuilderSplitNode(dockSpaceBottom, ImGuiDir_Left, 0.5f, nullptr, &dockSpaceBottom);
		ImGuiID dockSpaceBottomRight = ImGui::DockBuilderSplitNode(dockSpaceBottom, ImGuiDir_Right, 0.5f, nullptr, &dockSpaceBottom);

		// Register dockable layers.
		// TODO : Place these codes here is not suitable but convenient.
		ImGui::DockBuilderDockWindow("EntityList", dockSpaceUpLeftLeft);
		ImGui::DockBuilderDockWindow("GameView", dockSpaceLeftLeft);
		ImGui::DockBuilderDockWindow("SceneView", dockSpaceLeftRight);
		ImGui::DockBuilderDockWindow("Terrain Editor", dockSpaceUpRight);
		ImGui::DockBuilderDockWindow("Inspector", dockSpaceUpRight);
		ImGui::DockBuilderDockWindow("AssetBrowser", dockSpaceBottomLeft);
		ImGui::DockBuilderDockWindow("OutputLog", dockSpaceBottomRight);

		ImGui::DockBuilderFinish(dockSpaceWindowID);
	}

	// Create a dock space by ImGui default settings by using the created host window.
	ImGui::DockSpace(dockSpaceWindowID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton);
}

void ImGuiContextInstance::EndDockSpace()
{
	ImGui::End();
}

void ImGuiContextInstance::Update(float deltaTime)
{
	SwitchCurrentContext();

	// It is necessary to pass correct deltaTime to ImGui underlaying framework because it will use the value to check
	// something such as if mouse button double click happens(Two click event happens in one frame, < deltaTime).
	ImGui::GetIO().DeltaTime = deltaTime;

	AddInputEvent();

	ImGui::NewFrame();
	
	for (const auto& pImGuiLayer : m_pImGuiStaticLayers)
	{
		pImGuiLayer->Update();
	}

	ImGuiIO& io = ImGui::GetIO();
	const bool dockingEnabled = io.ConfigFlags & ImGuiConfigFlags_DockingEnable;
	if (dockingEnabled)
	{
		BeginDockSpace();
	}

	for (const auto& pImGuiLayer : m_pImGuiDockableLayers)
	{
		if (pImGuiLayer->IsEnable())
		{
			pImGuiLayer->Update();
		}
	}

	if (dockingEnabled)
	{
		EndDockSpace();
	}
}

// Don't push unnecessary events to ImGui. Or it will overflow its event queue to cause a time delay UI feedback.
// Why we don't use callback directly from native platform window? Because we have multiple imgui contexts to receive input events.
// And only the active imgui context can receive window messages. It sounds no problem but imgui context can switch during one frame multiple times.
// It is not safe to use event callback.
void ImGuiContextInstance::AddInputEvent()
{
	ImGuiIO& io = ImGui::GetIO();
	if (bool mouseLBPressed = Input::Get().IsMouseLBPressed(); m_lastMouseLBPressed != mouseLBPressed)
	{
		io.AddMouseButtonEvent(ImGuiMouseButton_Left, mouseLBPressed);
		m_lastMouseLBPressed = mouseLBPressed;
	}

	if (bool mouseRBPressed = Input::Get().IsMouseRBPressed(); m_lastMouseRBPressed != mouseRBPressed)
	{
		io.AddMouseButtonEvent(ImGuiMouseButton_Right, mouseRBPressed);
		m_lastMouseRBPressed = mouseRBPressed;
	}

	if (bool mouseMBPressed = Input::Get().IsMouseMBPressed(); m_lastMouseMBPressed != mouseMBPressed)
	{
		io.AddMouseButtonEvent(ImGuiMouseButton_Middle, mouseMBPressed);
		m_lastMouseMBPressed = mouseMBPressed;
	}

	if (float mouseScrollOffsetY = Input::Get().GetMouseScrollOffsetY(); mouseScrollOffsetY != m_lastMouseScrollOffstY)
	{
		io.AddMouseWheelEvent(0.0f, mouseScrollOffsetY);
		m_lastMouseScrollOffstY = mouseScrollOffsetY;
	}

	float mousePosX = static_cast<float>(Input::Get().GetMousePositionX());
	float mousePosY = static_cast<float>(Input::Get().GetMousePositionY());
	if (mousePosX != m_lastMousePositionX || mousePosY != m_lastMousePositionY)
	{
		io.AddMousePosEvent(mousePosX - m_windowPosOffsetX, mousePosY - m_windowPosOffsetY);
		m_lastMousePositionX = mousePosX;
		m_lastMousePositionY = mousePosY;
	}

	const std::vector<Input::KeyEvent> keyEvents = Input::Get().GetKeyEventList();
	for (uint32_t i = 0; i < keyEvents.size(); ++i)
	{
		const Input::KeyEvent keyEvent = keyEvents[i];
		if (keyEvent.mod != KeyMod::KMOD_NONE)
		{
			// Add the modifier key event
			if (kImguiKeyModToImGuiModLookup.find(keyEvent.mod) != kImguiKeyModToImGuiModLookup.cend())
			{
				io.AddKeyEvent(kImguiKeyModToImGuiModLookup[keyEvent.mod], keyEvent.isPressed);
			}
			// Also add the key itself as key event
			if (kImguiKeyModToImGuiKeyLookup.find(keyEvent.mod) != kImguiKeyModToImGuiKeyLookup.cend())
			{
				io.AddKeyEvent(kImguiKeyModToImGuiKeyLookup[keyEvent.mod], keyEvent.isPressed);
			}
		}
		if (kImguiKeyLookup.find(keyEvent.code) != kImguiKeyLookup.cend()) {
			io.AddKeyEvent(kImguiKeyLookup[keyEvent.code], keyEvent.isPressed);
		}
	}

	const char* inputChars = Input::Get().GetInputCharacters();
	const size_t inputCharSize = strlen(inputChars);
	for (size_t i = 0; i < inputCharSize; ++i)
	{
		io.AddInputCharacter(inputChars[i]);
	}
}

void ImGuiContextInstance::OnResize(uint16_t width, uint16_t height)
{
	ImGuiIO& io = m_pImGuiContext->IO;
	io.DisplaySize.x = width;
	io.DisplaySize.y = height;
}

void ImGuiContextInstance::LoadFontFiles(const std::vector<std::string>& ttfFileNames, Language language)
{
	TempSwitchContextScope tempSwitchScope(this);

	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 1.0f;

	ImFontConfig config;
	config.OversampleH = 2;
	config.OversampleV = 1;
	config.GlyphExtraSpacing.x = 1.0f;

	bool ttfFileLoaded = false;
	for (const std::string& ttfFileName : ttfFileNames)
	{
		std::string editorFontResourcePath = CDEDITOR_RESOURCES_ROOT_PATH;
		editorFontResourcePath += ttfFileName;

		const ImWchar* pGlyphRanges = nullptr;
		switch (language)
		{
		// Glyph ranges for Chinese Simplied have issues on showing some characters.
		// So let's use the bigger Glyph ranges including tradional characters.
		case Language::ChineseSimplied:
		case Language::ChineseTraditional:
			pGlyphRanges = io.Fonts->GetGlyphRangesChineseFull();
			break;
		case Language::Cyrillic:
			pGlyphRanges = io.Fonts->GetGlyphRangesCyrillic();
			break;
		case Language::Greek:
			pGlyphRanges = io.Fonts->GetGlyphRangesGreek();
			break;
		case Language::Japanese:
			pGlyphRanges = io.Fonts->GetGlyphRangesJapanese();
			break;
		case Language::Korean:
			pGlyphRanges = io.Fonts->GetGlyphRangesKorean();
			break;
		case Language::Thai:
			pGlyphRanges = io.Fonts->GetGlyphRangesThai();
			break;
		case Language::Vitnam:
			pGlyphRanges = io.Fonts->GetGlyphRangesVietnamese();
			break;
		case Language::English:
		default:
			break;
		}

		if (ImFont* pFont = io.Fonts->AddFontFromFileTTF(editorFontResourcePath.c_str(), 15.0f, &config, pGlyphRanges))
		{
			ttfFileLoaded = true;
		}
	}

	// If no .ttf files loaded, we should use the default font.
	if (!ttfFileLoaded)
	{
		io.Fonts->AddFontDefault();
	}

	// IconFont
	ImFontConfig iconFontConfig;
	iconFontConfig.MergeMode = true;
	iconFontConfig.PixelSnapH = true;
	iconFontConfig.GlyphOffset.y = 1.0f;
	iconFontConfig.OversampleH = iconFontConfig.OversampleV = 1;
	iconFontConfig.GlyphMinAdvanceX = 4.0f;
	iconFontConfig.SizePixels = 12.0f;

	// MaterialDesignIconFont is from https://materialdesignicons.com/, then generated a c style header file to use in memory without loading from disk.
	// Note that font glyph range array needs to be persistent until you build the font. So it will be convenient to declare it as static.
	static ImWchar iconFontGlyphRange[] = { ICON_MIN_MDI, ICON_MAX_MDI, 0 };
	io.Fonts->AddFontFromMemoryCompressedTTF(MaterialDesign_compressed_data, MaterialDesign_compressed_size, 14.0f, &iconFontConfig, iconFontGlyphRange);
	io.Fonts->TexGlyphPadding = 1;
	for (int fontConfigDataIndex = 0; fontConfigDataIndex < io.Fonts->ConfigData.Size; ++fontConfigDataIndex)
	{
		io.Fonts->ConfigData[fontConfigDataIndex].RasterizerMultiply = 1.0f;
	}

	ImFontAtlas* pFontAtlas = ImGui::GetIO().Fonts;
	pFontAtlas->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType();
	pFontAtlas->FontBuilderFlags = 0;
	pFontAtlas->Build();
}

void ImGuiContextInstance::SetImGuiStyles()
{
	TempSwitchContextScope tempSwitchScope(this);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(5, 5);
	style.FramePadding = ImVec2(4, 4);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(2, 2);
	style.IndentSpacing = 6.0f;
	style.TouchExtraPadding = ImVec2(4, 4);

	style.ScrollbarSize = 10;

	style.WindowBorderSize = 0;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 3;
	style.FrameBorderSize = 0.0f;

	constexpr int roundingAmount = 2;
	style.PopupRounding = roundingAmount;
	style.WindowRounding = roundingAmount;
	style.ChildRounding = 0;
	style.FrameRounding = roundingAmount;
	style.ScrollbarRounding = roundingAmount;
	style.GrabRounding = roundingAmount;
	style.WindowMinSize = ImVec2(200.0f, 200.0f);

	style.TabBorderSize = 1.0f;
	style.TabRounding = roundingAmount;

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = roundingAmount;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
}