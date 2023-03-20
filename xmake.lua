set_project("EnigineTestBench")

add_rules("mode.debug")
set_languages("cxx20")

set_targetdir("lib")

includes("TypeTrait")

includes("Vendor/glfw")
includes("Vendor/glad")
includes("Vendor/imgui")
includes("ImGuiGreeting")
