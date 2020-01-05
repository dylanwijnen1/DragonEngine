include "premake5_box2d.lua"
include "premake5_eastl.lua"
include "premake5_enet.lua"
include "premake5_glm.lua"
include "premake5_imgui.lua"
include "premake5_tmxlite.lua"

include "premake5_vld.lua"

include "premake5_sfml.lua"

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
