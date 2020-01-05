local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local glm = 
{
    location = "glm"
};

function glm.include(rootdir)
    includedirs(rootdir)
end

dependencies.add("glm", glm);