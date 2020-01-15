local dependencies = require "dependency-injector"
dependencies.init();

local dragoncore = require "dragoncore"
local utils = dragoncore.utils;

printf("[DragonEngine] Creating DragonEngine Project")

workspace "DragonEngine"

    startproject "DragonCore_Game"

    utils.workspace_defaults()

--- -------------------------------
--- Dragon Dependencies
--- -------------------------------

dependencies.generateProjects()

--- -------------------------------
--- Dragon Engine
--- -------------------------------

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