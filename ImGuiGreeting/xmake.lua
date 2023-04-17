target("ImGuiGreeting")
    set_kind("binary")
    add_deps(
        "libGLFW",
        "libImGui",
        "libGlad",
        "SDL3"
    )
    add_headerfiles(
        "*.hpp",
        "*.h",

        "$(projectdir)/Vendor/stb/*.h"
    )
    add_files(
        "*.cpp"
    )

    add_includedirs(
        "$(projectdir)/Vendor/glfw/include/",
        "$(projectdir)/Vendor/imgui/",
        "$(projectdir)/Vendor/glad/include/",
        "$(projectdir)/Vendor/freetype/include/",
        "$(projectdir)/Vendor/SDL/include/",
        "$(projectdir)/Vendor/stb/"
    )

    add_links(
        "SDL3"
    )

    add_linkdirs("$(projectdir)/lib/")
    

    add_defines("CDEDITOR_RESOURCES_ROOT_PATH=\"" .. (os.projectdir():gsub("\\", "\\\\")) .. "/Res/" .. "\"")