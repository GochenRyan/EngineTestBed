target("ImGuiGreeting")
    set_kind("binary")
    add_deps(
        "libGLFW",
        "libImGui",
        "libGlad",
        "libSDL"
    )
    add_headerfiles(
        "*.hpp",
        "*.h",
        "$(projectdir)/Vendor/stb/stb_image.h"
    )
    add_files(
        "*.cpp"
    )

    add_includedirs(
        "$(projectdir)/Vendor/glfw/include/",
        "$(projectdir)/Vendor/imgui/",
        "$(projectdir)/Vendor/glad/include/",
        "$(projectdir)/Vendor/freetype/include/",
        "$(projectdir)/Vendor/SDL/include/"
    )

    add_links(
        "libSDL"
    )

    add_linkdirs("$(projectdir)/lib/")
    

    add_defines("CDEDITOR_RESOURCES_ROOT_PATH=\"" .. (os.projectdir():gsub("\\", "\\\\")) .. "/Res/" .. "\"")