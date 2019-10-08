printf("[DragonEngine] Building Project Files")
include "tools/dragoncore-utils.lua"

include "dependencies/premake5_eastl"
include "dependencies/premake5_sfml"
include "dependencies/premake5_box2d"
include "dependencies/premake5_enet"
include "dependencies/premake5_tmxlite"
include "dependencies/premake5_mathfu"

dragon_list_dependencies()

local outputdir = "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}"

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

    dragon_create_dependency_projects("dependencies/")

project "DragonCore"

    dragon_project_defaults();

    location "DragonCore"
    characterset("ASCII")
    kind "StaticLib"    

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- This allows for <Dragon/...> includes.
    includedirs "%{prj.name}/src"

    filter "configurations:Debug"
        defines "DRAGON_DEBUG"

    filter "configurations:Release"
        defines "DRAGON_RELEASE"

    filter "configurations:Distribution"
        defines "DRAGON_DIST"

        
    -- Reset filters
    filter {}

    -- Links and Includes the dependency projects.
    dragon_add_dependencies("dependencies/")

-- Generate UnitTests project
project "DragonCore_UnitTests"

    dragon_project_defaults()

    location "DragonCore_UnitTests"
    kind "ConsoleApp"

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

    links
    {
        "DragonCore"
    }

    filter {}

    dragon_include_dependencies("dependencies/")
    --dragon_add_dependencies("dependencies/")