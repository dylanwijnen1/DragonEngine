include "../tools/dragoncore-utils.lua"

local function box2d_project(basedir)
    local box2d_dir = basedir .. "Box2D/";

    project "Box2D"
        location (box2d_dir .."Build/")
        kind "StaticLib"

        dragon_project_defaults()

        files { box2d_dir .. [[Box2D/**]] }
        includedirs { box2d_dir }

end

local function box2d_includes(basedir)
    local box2d_dir = basedir .. "Box2D/";

    includedirs { box2d_dir }
end

local function box2d_link(dragonlibdir)
    links 
    {
        "Box2D"
    }

    libdirs
    {
        dragonlibdir .. "Box2D"
    }
end

add_dependency_project("Box2D", box2d_project, box2d_includes, box2d_link)