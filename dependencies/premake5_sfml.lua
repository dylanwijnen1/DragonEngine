include "../tools/dragoncore-utils.lua"

local function sfml_project(basedir)
    local sfmldir = basedir .. "SFML/";

	-- sfml-graphics
	-- sfml-audio
	-- sfml-system
	-- sfml-window

	project "sfml-system"
		location (sfmldir .. "Build/")
		kind "StaticLib"

		dragon_project_defaults()
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC",
			"_CRT_SECURE_NO_DEPRECATE",
			"_SCL_SECURE_NO_WARNINGS"
		}

		files
		{
			sfmldir .. [[src/SFML/System/*.hpp]],
			sfmldir .. [[src/SFML/System/*.cpp]],
			sfmldir .. [[src/SFML/System/Win32/*.cpp]],
			sfmldir .. [[src/SFML/System/Win32/*.hpp]]
		}

		includedirs
		{
			sfmldir .. [[include/]],
			sfmldir .. [[src/]],
		}
		
	project "sfml-audio"
		location (sfmldir .. "Build/")
		kind "StaticLib"

		dragon_project_defaults()
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC",
			"_CRT_SECURE_NO_DEPRECATE",
			"_SCL_SECURE_NO_WARNINGS",
			"OV_EXCLUDE_STATIC_CALLBACKS",
			"FLAC__NO_DLL"
		}

		files
		{
			sfmldir .. [[src/SFML/Audio/*.*]],
			sfmldir .. [[src/SFML/Audio/**.hpp]]
		}

		includedirs
		{
			sfmldir .. [[include/]],
			sfmldir .. [[src/]],
			sfmldir .. [[extlibs/headers/]],
			sfmldir .. [[extlibs/headers/AL/]]
		}

		links
		{
			"sfml-system"
		}
	
	project "sfml-window"
		location (sfmldir .. "Build/")
		kind "StaticLib"

		dragon_project_defaults()
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC"
		}

		files
		{
			sfmldir .. [[src/SFML/Window/Win32/**.cpp]],
			sfmldir .. [[src/SFML/Window/Win32/**.hpp]],
			sfmldir .. [[src/SFML/Window/*.hpp]],
			sfmldir .. [[src/SFML/Window/*.cpp]]
		}

		excludes 
		{
			sfmldir .. "src/SFML/Window/EGLCheck.cpp",
			sfmldir .. "src/SFML/Window/EGLCheck.hpp",
			sfmldir .. "src/SFML/Window/EglContext.cpp",
			sfmldir .. "src/SFML/Window/EglContext.hpp"
		}

		includedirs
		{
			sfmldir .. [[include/]],
			sfmldir .. [[src/]],
			sfmldir .. [[extlibs/headers/stb_image/]],
			sfmldir .. [[extlibs/headers/freetype2/]],
		}
			
		filter {}
		
		links
		{
			"sfml-system"
		}	
	
    project "sfml-graphics"
        location (sfmldir .. "Build/")
        kind "StaticLib"

        dragon_project_defaults()
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC"
		}

        files
        {
            sfmldir .. [[src/SFML/Graphics/**.cpp]],
			sfmldir .. [[src/SFML/Graphics/**.hpp]]
        }

        includedirs
        {
            sfmldir .. [[include/]],
			sfmldir .. [[src/]],
			sfmldir .. [[extlibs/headers/stb_image/]],
			sfmldir .. [[extlibs/headers/freetype2/]]
        }
		
		links
		{
			"sfml-window",
			"sfml-system"
		}

end

local function sfml_includes(basedir)
    local sfmldir = basedir .. "SFML/";

    includedirs
    {
		sfmldir .. [[include/]],
	}

	libdirs
	{
		sfmldir .. [[extlibs/libs-msvc/x64/]],
	}

    defines "SFML_STATIC"
end

local function sfml_link()
    links 
    {
        "sfml-graphics",
		"sfml-audio",
		"sfml-system",
		"sfml-window",
		"flac.lib",
		"freetype.lib",
		"ogg.lib",
		"openal32.lib",
		"vorbis.lib",
		"vorbisenc.lib",
		"vorbisfile.lib",
		"opengl32.lib",
		"gdi32.lib",
		"winmm.lib"
	}
end

add_dependency_project("SFML", sfml_project, sfml_includes, sfml_link)