local dependencies = require "dependency-injector"

include "../tools/dragoncore-utils.lua"

local glm = 
{
    location = "glm"
};

function glm.include(rootdir)
    includedirs(rootdir)
end

dependencies.add("GLM", glm);