set_project("EnigineTestBench")

add_rules("mode.debug", "mode.release")
set_languages("cxx20")

set_targetdir("lib")

includes("TypeTrait")

includes("Vendor/glfw")
includes("Vendor/imgui")
includes("ImGuiGreeting")