include "../tools/dragoncore-utils.lua"

local function mathfu_project(basedir)
end

local function mathfu_includes(basedir)
    local mathfu_dir = basedir .. "mathfu/";

    includedirs 
    {
        mathfu_dir .. [[include]],
        mathfu_dir .. [[dependencies/vectorial/include]],
    }
end

local function mathfu_link()
end

add_dependency_project("mathfu", mathfu_project, mathfu_includes, mathfu_link)