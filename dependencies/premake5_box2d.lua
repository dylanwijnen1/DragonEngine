local dependencies = require "dependency-injector"

include "../tools/dragoncore-utils.lua"

local box2d = 
{
    location = "Box2D"
};

function box2d.project(rootdir)
    project "Box2D"
        location (rootdir .. "Build/")
        kind "StaticLib"

        dragon_project_defaults()

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