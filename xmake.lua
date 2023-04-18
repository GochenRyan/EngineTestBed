set_project("EnigineTestBench")

add_rules("mode.debug")
set_languages("cxx20")

add_cxxflags("/Zc:__cplusplus")

set_targetdir("lib")

includes("TypeTrait")

includes("Vendor/glfw")
includes("Vendor/glad")
includes("Vendor/freetype")
includes("Vendor/SDL")

includes("Vendor/bx")
includes("Vendor/bimg")
includes("Vendor/bgfx")

includes("Vendor/imgui")
includes("ImGuiGreeting")
