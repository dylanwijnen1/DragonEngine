local dependencies = require "dependency-injector"
dependencies.init();

local dragoncore = require "dragoncore"
local utils = dragoncore.utils;

local ENGINE_ROOT = "@{DRAGON_ENGINE_ROOT}@";

print("[@{PRJ_NAME}@] Building @{PRJ_NAME}@ Project Files!")

workspace "@{PRJ_NAME}@"

    startproject "@{PRJ_NAME}@";
    utils.workspace_defaults();
    
project "@{PRJ_NAME}@"

    utils.project_defaults();

    location "%{prj.name}";
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

    utils.init_dragon_project(ENGINE_ROOT);