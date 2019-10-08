printf("[DragonEngine] Building Project Files")
include "tools/dragoncore-utils.lua"

include "dependencies/premake5_eastl"
include "dependencies/premake5_sfml"
include "dependencies/premake5_box2d"
include "dependencies/premake5_enet"
include "dependencies/premake5_tmxlite"
include "dependencies/premake5_mathfu"

dragon_list_dependencies()

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

dragon_create_dependency_projects("dependencies/")

project "DragonCore"

    location "DragonCore"
    kind "StaticLib"
    language "C++"

    staticruntime "Off"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    characterset("ASCII")
    
    cppdialect "C++17"
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

    dragon_add_dependencies("dependencies/")

-- Generate UnitTests project
project "DragonCore_UnitTests"
    location "DragonCore_UnitTests"
    kind "ConsoleApp"

    dragon_project_defaults()

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

    filter {}

    --dragon_include_dependencies("dependencies/")
    dragon_add_dependencies("dependencies/")