printf("[DragonEngine] Building Project Files")

workspace "DragonEngine"

    startproject "DragonCore_UnitTests"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

    platforms
    {
        "x64",
        "x86"
    }

local outputdir = "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}"

project "DragonCore"

    location "DragonCore"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)
    
    cppdialect "C++17"
    -- staticruntime "On"
    systemversion "latest"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- This allows for <Dragon/...> includes.
    includedirs "%{prj.name}/src"

    filter "platforms:x64"
        architecture "x64"

    filter "platforms:x86"
        architecture "x86"

    filter "configurations:Debug"
        defines "DRAGON_DEBUG"
        symbols "full"
        runtime "Debug"

    filter "configurations:Release"
        defines "DRAGON_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Distribution"
        defines "DRAGON_DIST"
        optimize "On"
        runtime "Release"

    -- Reset filters
    filter {}

    include_dragondependencies()
    link_dragondependencies()

-- Generate UnitTests project
project "DragonCore_UnitTests"
    location "DragonCore_UnitTests"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    includedirs 
    {
        "DragonCore/src",
        "%{prj.name}/thirdparty/catch2/include"
    }

    files 
    {
        "%{prj.name}/*.h",
        "%{prj.name}/*.cpp"
    }

    links "DragonCore"

    filter "platforms:x64"
        architecture "x64"
    
    filter "platforms:x86"
        architecture "x86"

    filter {}