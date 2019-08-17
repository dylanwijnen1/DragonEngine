include "../dragoncore.lua"

--- Sets the PROJECT_NAME local variable.
newoption 
{
    trigger     = "projectname",
    value       = "newproject",
    description = "The name of the project"
}

local PROJECT_NAME = _OPTIONS["projectname"] or "NewProject"
local outputdir = "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}"
local DRAGON_ENGINE_PATH = path.join(path.getabsolute("../"))


printf("Generating project: %s", PROJECT_NAME)
printf("[DEBUG] DRAGON_ENGINE_PATH: %s", DRAGON_ENGINE_PATH)

workspace(PROJECT_NAME)
    location (PROJECT_NAME)

    startproject(PROJECT_NAME)

    configurations
    {
        "Debug",
        "Release",
    }

    platforms
    {
        "x64",
        "x86"
    }

externalproject "DragonCore"
    location "%{DRAGON_ENGINE_PATH}/../DragonCore"
    uuid "49A360B0-355B-A2FD-9E62-7B598A393DEE"
    kind "StaticLib"
    language "C++"

project (PROJECT_NAME)
    location (PROJECT_NAME)

    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    cppdialect "C++17"
    systemversion "latest"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        -- "%{prj.name}/scripts/**.py"
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

    -- Reset filters
    filter {}

    include_dragondependencies()
    link_dragondependencies()

    includedirs
    {
        "%{DRAGON_ENGINE_PATH}/../DragonCore/src"
    }

    links
    {
        "DragonCore"
    }