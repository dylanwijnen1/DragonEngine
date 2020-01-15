local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local enet =
{
    location = "enet"
}

function enet.project(rootdir)

    project "enet"
        location (rootdir .."Build/")
        kind "StaticLib"

        utils.project_defaults();

		language "C"
		files { rootdir .. "*.c" }
		includedirs { rootdir .. "include/" }

end

function enet.include(rootdir)
    includedirs { rootdir .. "include/" }
end

function enet.link(rootdir, dragonlibdir)
    links 
    {
        "enet"
    }

    libdirs
    {
        dragonlibdir .. "enet"
    }
end

dependencies.add("enet", enet);