include "../tools/dragoncore-utils.lua"

local function imgui_project(basedir)
end

local function imgui_includes(basedir)
    includedirs { basedir .. "imgui/" }
end

local function imgui_link(dragonlibdir)
end

add_dependency_project("imgui", imgui_project, imgui_includes, imgui_link)