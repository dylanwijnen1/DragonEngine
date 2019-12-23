local dependencies = require "dependency-injector"

printf("[DragonEngine] Creating DragonEngine Project")

-- Includes
include "tools/dragoncore-utils.lua"
include "dependencies.lua"

--- -------------------------------
--- Dragon Dependencies
--- -------------------------------
-- workspace "DragonDependencies"

--     startproject "BuildAll"
    
--     project "BuildAll"
--         kind "Utility"

--         -- Setup build rules for all projects


--- -------------------------------
--- Dragon Engine
--- -------------------------------
workspace "DragonEngine"

    startproject "DragonCore_UnitTests"

    dragon_workspace_defaults()

-- Setup dependency projects in solution.
dependencies.generateProjects()

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

    dependencies.linkAll()
    dependencies.includeAll()

-- Generate UnitTests project
project "DragonCore_UnitTests"

    dragon_project_defaults()

    location "DragonCore_UnitTests"
    kind "ConsoleApp"

    -- Add Catch and DragonCore Source Files.
    includedirs 
    {
        "%{prj.name}/thirdparty/catch2/include",
        "DragonCore/src"
    }

    -- Add Test Files.
    files 
    {
        "%{prj.name}/*.h",
        "%{prj.name}/*.cpp"
    }

    -- Link the DragonCore Library
    links
    {
        "DragonCore"
    }

    