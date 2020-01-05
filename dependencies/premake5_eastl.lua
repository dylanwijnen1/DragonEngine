local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local eastl =
{
    location = "EASTL"
};

function eastl.project(rootdir)

    project "EASTL"
        location (rootdir .."Build/")
        kind "StaticLib"

        utils.project_defaults();

        files
        {
            rootdir .. [[source/**.cpp]],
        }

        includedirs
        {
            rootdir .. [[include]],
            rootdir .. [[test/packages/EABase/include/Common]]
        }

        defines 
        {
            "EASTL_EASTDC_VSNPRINTF=0",
            "_SSIZE_T_",
            "_SSIZE_T_DEFINED"
        }

end

function eastl.include(rootdir)

    includedirs
    {
        rootdir .. [[include]],
        rootdir .. [[test/packages/EABase/include/Common]]
    }

    files 
    {
        rootdir .. "doc/EASTL.natvis"
    }

    defines
    {
        "EASTL_EASTDC_VSNPRINTF=0",
        "_SSIZE_T_",
        "_SSIZE_T_DEFINED"
    }
end

function eastl.link(rootdir, dragonlibdir)
    links 
    {
        "EASTL"
    }

    libdirs
    {
        dragonlibdir .. "EASTL"
    }
end

dependencies.add("EASTL", eastl);