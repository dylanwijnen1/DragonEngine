local dependencies = require "dependency-injector"

include "../tools/dragoncore-utils.lua"

local imgui =
{
    location = "imgui"
};

function imgui.include(rootdir)
    includedirs { rootdir }
end

dependencies.add("imgui", imgui)