local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local tmxlite = 
{
    location = "tmxlite"
};

function tmxlite.project(rootdir)

    project "tmxlite"
        location (rootdir .."Build/")
        kind "StaticLib"

        characterset("ASCII")

        utils.project_defaults();
        
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

dependencies.add("tmxlite", tmxlite)