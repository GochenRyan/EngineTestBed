target("ImGuiGreeting")
    set_kind("binary")
    add_deps(
        "libGLFW",
        "libImGui",
        "libGlad"
    )
    add_headerfiles(
        "*.h"
    )
    add_files(
        "*.cpp"
    )

    add_includedirs(
        "$(projectdir)/Vendor/glfw/include/",
        "$(projectdir)/Vendor/imgui/",
        "$(projectdir)/Vendor/glad/include/"
    )

    add_linkdirs("$(projectdir)/lib/")

    local editorResourcesPath = "$(projectdir)/Res"

    add_defines("CDEDITOR_RESOURCES_ROOT_PATH=\""..editorResourcesPath.."\"")