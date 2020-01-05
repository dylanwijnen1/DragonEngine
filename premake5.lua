local dependencies = require "dependency-injector"
local dragoncore = require "dragoncore"
local utils = dragoncore.utils;

printf("[DragonEngine] Creating DragonEngine Project")

-- Add dependency includes.
include "dependencies/dependencies.lua"

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

    startproject "DragonCore_Game"

    utils.workspace_defaults()

-- Setup dependency projects in solution.
dependencies.generateProjects()

project "DragonCore"

    utils.project_defaults();

    location "DragonCore";
    characterset "ASCII";
    kind "StaticLib";

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- This allows for <Dragon/...> includes.
    includedirs "%{prj.name}/src";

    utils._internal_init_project();

project "DragonCore_Game"

    utils.project_defaults();

    location "DragonCore_Game";
    kind "ConsoleApp";

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    {
        "%{prj.name}/src",
    }

    utils.init_dragon_project();

-- Generate UnitTests project
project "DragonCore_UnitTests"

    utils.project_defaults();

    location "DragonCore_UnitTests";
    kind "ConsoleApp";

    -- Add Catch Source Files.
    includedirs 
    {
        "%{prj.name}/thirdparty/catch2/include",
    }

    -- Add Test Files.
    files 
    {
        "%{prj.name}/*.h",
        "%{prj.name}/*.cpp"
    }

    utils.init_dragon_project();