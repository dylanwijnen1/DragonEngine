printf("[DragonEngine] Building Project Files")
include "tools/dragoncore.lua"

local outputdir = "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}"

workspace "DragonEngine"

    startproject "DragonCore_UnitTests"

    dragon_workspace_defaults()

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
        "%{prj.name}/thirdparty/catch2/include",
        "DragonCore/src"
    }

    files 
    {
        "%{prj.name}/*.h",
        "%{prj.name}/*.cpp"
    }

    -- Link the Library
    links
    {
        "DragonCore"
    }

    dragon_include_dependencies("dependencies/")

    