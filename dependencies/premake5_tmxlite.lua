include "../tools/dragoncore-utils.lua"

local function tmxlite_project(basedir)
    local tmxlitedir = basedir .. "tmxlite/";

    project "tmxlite"
        location (tmxlitedir .."Build/")
        kind "StaticLib"

        characterset("ASCII")

        dragon_project_defaults()
        
        files 
        { 
            tmxlitedir .. "tmxlite/src/**.*",
        }

        excludes { "**.txt" }

        includedirs { tmxlitedir .. "tmxlite/include/" }
        
        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "TMXLITE_STATIC",
            "_MBCS"
        }

end

local function tmxlite_includes(basedir)
    local tmxlitedir = basedir .. "tmxlite/";

    includedirs { tmxlitedir .. "tmxlite/include/" }
end

local function tmxlite_link()
    links 
    {
        "tmxlite"
    }
end

add_dependency_project("tmxlite", tmxlite_project, tmxlite_includes, tmxlite_link)