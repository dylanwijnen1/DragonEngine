local dependencies = require "dependency-injector"
local dragoncore = require "dragoncore"
local utils = dragoncore.utils;

local box2d = 
{
    location = "Box2D"
};

function box2d.project(rootdir)
    project "Box2D"
        location (rootdir .. "Build/")
        kind "StaticLib"

        utils.project_defaults()

        files { rootdir .. [[Box2D/**]] }
        includedirs { rootdir }

end

function box2d.include(rootdir)
    includedirs { rootdir }
end

function box2d.link(rootdir, dragonlibdir)
    links 
    {
        "Box2D"
    }

    libdirs
    {
        dragonlibdir .. "Box2D"
    }
end

dependencies.add("Box2D", box2d)