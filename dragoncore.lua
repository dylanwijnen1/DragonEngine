--[[
    Graphics API option
    Default: sfml         
--]]
if not _OPTIONS["graphics"] then
    _OPTIONS["graphics"] = "sfml"
end

newoption 
{
    trigger     = "graphics",
    value       = "API",
    description = "Choose a particular API for rendering",
    allowed = {
    --    { "opengl",    "OpenGL (Cross Platform)" },
    --    { "direct3d",  "Direct3D (Windows only)" },
       { "sfml",  "SFML (Multiplatform/OpenGL)" }
    }
}

---TODO: Add a new action to generate a new game project template.
-- newoption
-- {
--     trigger     = "projectname",
--     value       = "Project Name",
--     description = "Sets the game's project name that is being generated. Default uses workspace name.",
-- }

DRAGON_DEPENDENCY_DIR = path.getabsolute("dependencies")
printf("Dependency Folder: %s", DRAGON_DEPENDENCY_DIR)
EASTL_ROOT_DIR = path.join(DRAGON_DEPENDENCY_DIR, "EASTL")

function build_dragon_dependencies()

    -- --------------------------------------------------------------------------
    -- | Box2D
    -- --------------------------------------------------------------------------
    printf("[Box2D] Generating Project Files")
    os.execute([[tools\premake5.exe --file="./dependencies/Box2D/premake5.lua" vs2019]])
    
    printf("[Box2D] Building Project Binaries")

    -- --------------------------------------------------------------------------
    -- | EASTL
    -- --------------------------------------------------------------------------
    printf("[EASTL] Generating Project Files")
    os.execute([[
        cmake -S"dependencies/EASTL" -B"dependencies/EASTL/Build/Win32" -G"Visual Studio 16 2019" -A"Win32" -DEASTL_BUILD_TESTS:BOOL=ON -DEASTL_BUILD_BENCHMARK:BOOL=OFF
    ]])

    os.execute([[
        cmake -S"dependencies/EASTL" -B"dependencies/EASTL/Build/Win64" -G"Visual Studio 16 2019" -DEASTL_BUILD_TESTS:BOOL=ON -DEASTL_BUILD_BENCHMARK:BOOL=OFF
    ]])
    
    printf("[EASTL] Building Project Binaries")

    -- --------------------------------------------------------------------------
    -- | SFML
    -- --------------------------------------------------------------------------
    -- TODO: Only if SFML option is enabled ?
    printf("[SFML] Generating Project Files")
    os.execute([[
        cmake -S"dependencies/SFML" -B"dependencies/SFML/Build/Win32" -G"Visual Studio 16 2019" -A"Win32" -DBUILD_SHARED_LIBS:BOOL=FALSE -DSFML_BUILD_NETWORK:BOOL=FALSE -DSFML_BUILD_AUDIO:BOOL=FALSE
    ]])

    os.execute([[
        cmake -S"dependencies/SFML" -B"dependencies/SFML/Build/Win64" -G"Visual Studio 16 2019" -DBUILD_SHARED_LIBS:BOOL=FALSE -DSFML_BUILD_NETWORK:BOOL=FALSE -DSFML_BUILD_AUDIO:BOOL=FALSE
    ]])

    printf("[SFML] Building Project Binaries")

    -- --------------------------------------------------------------------------
    -- | enet
    -- --------------------------------------------------------------------------
    printf("[ENet] Generating Project Files")
    os.execute([[tools\premake5.exe --file="./dependencies/enet/premake4.lua" vs2019]])

    -- --------------------------------------------------------------------------
    -- | tmxlite
    -- --------------------------------------------------------------------------
    printf("[tmxlite] Building Project Binaries")

end

function include_sfml()

    filter { "options:graphics=sfml" }
        defines "SFML_STATIC"
        includedirs "%{DRAGON_DEPENDENCY_DIR}/SFML/include"

    filter { "options:graphics=sfml", "platforms:x86" }
        postbuildcommands
        {
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win32/lib/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
        }

    filter { "options:graphics=sfml", "platforms:x64" }
        postbuildcommands
        {
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win64/lib/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
        }

    filter {}
end

--- Includes dragons dependencies
function include_dragon_dependencies()    
    includedirs
    {

        -- Header only libraries includes
        "%{DRAGON_DEPENDENCY_DIR}/pybind11/include",
        "%{DRAGON_DEPENDENCY_DIR}/mathfu/include",
        "%{DRAGON_DEPENDENCY_DIR}/mathfu/dependencies/vectorial/include",
        
        -- Library includes
        "%{DRAGON_DEPENDENCY_DIR}/Box2D",

        "%{EASTL_ROOT_DIR}/include",
        "%{EASTL_ROOT_DIR}/test/packages/EAAssert/include",
        "%{EASTL_ROOT_DIR}/test/packages/EABase/include/Common",
        "%{EASTL_ROOT_DIR}/test/packages/EAMain/include",
        "%{EASTL_ROOT_DIR}/test/packages/EAStdC/include",
        "%{EASTL_ROOT_DIR}/test/packages/EATest/include",
        "%{EASTL_ROOT_DIR}/test/packages/EAThread/include",

        "%{DRAGON_DEPENDENCY_DIR}/tmxlite/tmxlite/include",

        "%{DRAGON_DEPENDENCY_DIR}/enet/include",

        -- "%{DRAGON_DEPENDENCY_DIR}/fmod/inc",
        
        "%{DRAGON_DEPENDENCY_DIR}/imgui",

        "%{DRAGON_DEPENDENCY_DIR}/python/include",
    }

    -- Visualization Files, This helps with debugging.
    files
    {
        "%{EASTL_ROOT_DIR}/doc/EASTL.natvis"
    }

    -- x86
    filter { "platforms:x86" }
        postbuildcommands 
        {
            -- [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x86/*.dll" "%{cfg.buildtarget.directory}"]],            
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/python/x86/*.*" "%{cfg.buildtarget.directory}"]],

            -- PDB
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
            [[{COPY} "%{EASTL_ROOT_DIR}/Build/Win32/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
        }

    -- x64
    filter { "platforms:x64" }
        postbuildcommands 
        {
            -- [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x64/*.dll" "%{cfg.buildtarget.directory}"]],            
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/python/x64/*.*" "%{cfg.buildtarget.directory}"]],

            -- PDB
            [[{COPY} "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86_64/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
            [[{COPY} "%{EASTL_ROOT_DIR}/Build/Win64/Debug/*.pdb" "%{cfg.buildtarget.directory}"]],
        }

    include_sfml()
        
    filter {}

end

function link_sfml()
    -- SFML, Release, x64
    filter { "configurations:not *Debug*", "options:graphics=sfml", "platforms:x64" }
            libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win64/lib/Release/"

    -- SFML, Debug, x64
    filter { "configurations:*Debug*", "options:graphics=sfml", "platforms:x64" }
        libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win64/lib/Debug/"

    -- SFML, Release, x86
    filter { "configurations:not *Debug*", "options:graphics=sfml", "platforms:x86" }
            libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win32/lib/Release/"
            
    -- SFML, Debug, x86
    filter { "configurations:*Debug*", "options:graphics=sfml", "platforms:x86" }
        libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/Build/Win32/lib/Debug/"

    -- SFML, x64
    filter { "options:graphics=sfml", "platforms:x64" }
        libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/extlibs/libs-msvc/x64/"

    -- SFML, x86
    filter { "options:graphics=sfml", "platforms:x86" }
        libdirs "%{DRAGON_DEPENDENCY_DIR}/SFML/extlibs/libs-msvc/x86/"


    filter { "configurations:*Debug*", "options:graphics=sfml" }
        links
        {
            -- SFML
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
        }

    -- SFML, Release
    filter { "configurations:not *Debug*", "options:graphics=sfml" }
        links
        {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
        }

    -- SFML
    filter { "options:graphics=sfml" }
        links
        {
            "freetype.lib",
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib",
        }

    filter {}
end

--- Links dragons dependencies
function link_dragon_dependencies()

    -- Release, x64
    filter { "configurations:not *Debug*", "platforms:x64" }
        libdirs
        {
            "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86_64/Release/", --Box2D.lib/pdb
            "%{EASTL_ROOT_DIR}/Build/Win64/Release/", --EASTL.lib/pdb
            "%{DRAGON_DEPENDENCY_DIR}/enet/bin/x64/Release/", --enet_static64d.lib, enet_staticd.lib, enet_static.lib, x32
            --"%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x64/", --fmod_vc.lib, fmodL_vc.lib, DLL's
            "%{DRAGON_DEPENDENCY_DIR}/tmxlite/tmxlite/x64/bin/ReleaseStatic/" -- libtmxlite-s-d.lib, libtmxlite-s.lib
        }

        links
        {
            "enet_static64.lib"
        }

    -- Debug, x64
    filter { "configurations:*Debug*", "platforms:x64" }
        libdirs
        {
            "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86_64/Debug/",
            "%{EASTL_ROOT_DIR}/Build/Win64/Debug/",
            "%{DRAGON_DEPENDENCY_DIR}/enet/bin/x64/Debug/",
            --"%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x64/", 
            "%{DRAGON_DEPENDENCY_DIR}/tmxlite/tmxlite/x64/bin/DebugStatic/"
        }

        links
        {
            "enet_static64d.lib"
        }

    -- Release, x86
    filter { "configurations:not *Debug*", "platforms:x86" }
        libdirs
        {
            "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86/Release/",
            "%{EASTL_ROOT_DIR}/Build/Win32/Release/",
            "%{DRAGON_DEPENDENCY_DIR}/enet/bin/x32/Release/",
            --"%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x86/",
            "%{DRAGON_DEPENDENCY_DIR}/tmxlite/tmxlite/bin/ReleaseStatic/"
        }

        links
        {
            "enet_static.lib"
        }

    -- Debug, x86
    filter { "configurations:*Debug*", "platforms:x86" }
        libdirs
        {
            "%{DRAGON_DEPENDENCY_DIR}/Box2D/Build/bin/x86/Debug/",
            "%{EASTL_ROOT_DIR}/Build/Win32/Debug/",
            "%{DRAGON_DEPENDENCY_DIR}/enet/bin/x32/Debug/",
            --"%{DRAGON_DEPENDENCY_DIR}/fmod/lib/x86/",
            "%{DRAGON_DEPENDENCY_DIR}/tmxlite/tmxlite/bin/DebugStatic/"
        }

        links
        {
            "enet_staticd.lib"
        }

    -- Release
    filter { "configurations:not *Debug*" }
        links
        {
            --"fmod_vc.lib",
            "libtmxlite-s.lib"
        } 

    -- Debug
    filter { "configurations:*Debug*" }
        links
        {
            --"fmodL_vc.lib",
            "libtmxlite-s-d.lib"
        }

    filter { "platforms:x64" }
        libdirs 
        {
            "%{DRAGON_DEPENDENCY_DIR}/python/x64/libs/",
        }

    filter { "platforms:x86" }
        libdirs 
        {
            "%{DRAGON_DEPENDENCY_DIR}/python/x86/libs/",
        }

    link_sfml()

    filter {}

    defines
    {
        "EASTL_EASTDC_VSNPRINTF=0",
        "_SSIZE_T_",
        "_SSIZE_T_DEFINED"
    }

    links
    {
        -- Box2D
        "Box2D.lib",

        -- EASTL
        "EASTL.lib"
    }

end

--- Generates all the basic files required to open a game window.
function generate_dragon_game(projectname)

end