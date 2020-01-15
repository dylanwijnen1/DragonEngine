local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local imgui =
{
    location = "imgui"
};

function imgui.include(rootdir)
    includedirs { rootdir }
end

dependencies.add("imgui", imgui)