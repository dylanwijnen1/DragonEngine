local dependencies = require "dependency-injector"



include "../../../dependencies/premake5_box2d.lua"

dependencies.list();

-- premake5_eastl
-- premake5_enet
-- premake5_glm
-- premake5_imgui
-- premake5_sfml
-- premake5_tmxlite
-- premake5_vld


workspace "TestWorkspace"
    configurations { "Debug", "Release" }

    project "TestProject"

    kind "StaticLib"
    language "C++"

    debug.prompt()

    dependencies.include("Box2D")
    dependencies.link("Box2D")