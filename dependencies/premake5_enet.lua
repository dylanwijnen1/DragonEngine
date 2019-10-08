include "../tools/dragoncore-utils.lua"

local function enet_project(basedir)
    local enetdir = basedir .. "enet/";

    project "enet"
        location (enetdir .."Build/")
        kind "StaticLib"

        
        dragon_project_defaults()

		language "C"
		files { enetdir .. "*.c" }
		includedirs { enetdir .. "include/" }

end

local function enet_includes(basedir)
    local enetdir = basedir .. "enet/";

    includedirs { enetdir .. "include/" }
end

local function enet_link()
    links 
    {
        "enet"
    }
end

add_dependency_project("enet", enet_project, enet_includes, enet_link)