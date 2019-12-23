local dependencies = require "dependency-injector"

include "../tools/dragoncore-utils.lua"

local tmxlite = 
{
    location = "tmxlite"
};

function tmxlite.project(rootdir)

    project "tmxlite"
        location (rootdir .."Build/")
        kind "StaticLib"

        characterset("ASCII")

        dragon_project_defaults()
        
        files 
        { 
            rootdir .. "tmxlite/src/**.*",
        }

        excludes { "**.txt" }

        includedirs { rootdir .. "tmxlite/include/" }
        
        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "TMXLITE_STATIC",
            "_MBCS"
        }

end

function tmxlite.include(rootdir)
    includedirs { rootdir .. "tmxlite/include/" }
end

function tmxlite.link(rootdir, dragonlibdir)
    links 
    {
        "tmxlite"
    }

    libdirs { dragonlibdir .. "tmxlite" }
end

dependencies.add("tiled", tmxlite)