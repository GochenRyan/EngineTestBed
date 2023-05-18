target("RPCServer")
    set_toolchains("msvc", {vs = "2022"})
    set_kind("binary")

    add_includedirs(
        "$(projectdir)/Vendor/yalantinglibs/include/",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/asio",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/async_simple",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/cinatra",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/doctest",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/frozen",
        "$(projectdir)/Vendor/yalantinglibs/thirdparty/iguana"
    , {public = true})

    -- add_linkdirs("$(projectdir)/lib")
    -- add_links("libRpc")

    add_headerfiles("*.h", "*.hpp")
    add_files("*.cpp")
    add_includedirs("$(projectdir)/RPCServer")