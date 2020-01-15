premake.modules.dragoncore.utils = {};
local m = premake.modules.dragoncore.utils;

function m.default_outdir()
    return "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}";
end

---Adds the default settings for dragon workspaces.
function m.workspace_defaults()
    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

    platforms
    {
        "x64",
        "Win32"
    }
end

---Adds the default settings for any dragon project.
---To override the defaults call this function first then apply your overrides.
function m.project_defaults()

    local outputdir = m.default_outdir();

    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    staticruntime "Off"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    filter "platforms:x64"
        architecture "x64"

    filter "platforms:Win32"
        architecture "x86"

        filter "configurations:Debug"
        symbols "full"
        runtime "Debug"
        defines "DRAGON_DEBUG"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"
        defines "DRAGON_RELEASE"

    filter "configurations:Distribution"
        optimize "On"
        runtime "Release"
        defines "DRAGON_DIST"
        
    -- Reset filters
    filter {}

end

--- Links and includes all dependencies for the dragon engine.
function m._internal_init_project()

    local dependencies = require "dependency-injector";

    dependencies.require("Box2D");
    dependencies.require("EASTL");
    dependencies.require("enet");
    dependencies.require("glm");
    dependencies.require("imgui");
    dependencies.require("tmxlite");

    -- TODO: Depends on the current graphics implementation. _OPTIONS['gfx'] == ...
    dependencies.require("SFML");

end

--- Initializes the dragon engine in the current project scope.
--- @param engine_root string | "The root path to the engine. Can pass nil for current executing premake file being in the same as the root directory."
function m.init_dragon_project(engine_root)

    engine_root = engine_root or "";

    m._internal_init_project();

    links "DragonCore";
    includedirs(engine_root .. "DragonCore/src")

end

return m;