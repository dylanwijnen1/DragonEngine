include "../tools/dragoncore-utils.lua"

local function eastl_project(basedir)
    local eastldir = basedir .. "EASTL/";

    project "EASTL"
        location (eastldir .."Build/")
        kind "StaticLib"

        dragon_project_defaults()

        files
        {
            eastldir .. [[source/**.cpp]],
        }

        includedirs
        {
            eastldir .. [[include]],
            eastldir .. [[test/packages/EABase/include/Common]]
        }

        defines 
        {
            "EASTL_EASTDC_VSNPRINTF=0",
            "_SSIZE_T_",
            "_SSIZE_T_DEFINED"
        }

end

local function eastl_includes(basedir)
    local eastldir = basedir .. "EASTL/";

    includedirs
    {
        eastldir .. [[include]],
        eastldir .. [[test/packages/EABase/include/Common]]
    }

    files 
    {
        eastldir .. "doc/EASTL.natvis"
    }

    defines
    {
        "EASTL_EASTDC_VSNPRINTF=0",
        "_SSIZE_T_",
        "_SSIZE_T_DEFINED"
    }
end

local function eastl_link(dragonlibdir)
    links 
    {
        "EASTL"
    }

    libdirs
    {
        dragonlibdir .. "EASTL"
    }
end

add_dependency_project("EASTL", eastl_project, eastl_includes, eastl_link)