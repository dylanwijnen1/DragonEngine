include "dependencies/premake5_box2d.lua"
include "dependencies/premake5_eastl.lua"
include "dependencies/premake5_enet.lua"
include "dependencies/premake5_glm.lua"
include "dependencies/premake5_imgui.lua"
include "dependencies/premake5_tmxlite.lua"

include "dependencies/premake5_vld.lua"

include "dependencies/premake5_sfml.lua"

-- if _OPTIONS["graphics"] == nil then
--     _OPTIONS["graphics"] = "SFML"; -- SFML is the default graphics API
-- end

-- -- TODO: Figure out defines.
-- -- Choose Graphics API
-- if _OPTIONS["graphics"] == "SFML" then

--     include "dependencies/premake5_sfml.lua"
--     -- defines "DRAGON_RENDERSKIN_SFML=1"

-- elseif _OPTIONS["graphics"] == "NONE" then

--     -- defines "DRAGON_RENDERSKIN_NONE=1"

-- end
