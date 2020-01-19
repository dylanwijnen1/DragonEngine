local dependencies = require "dependency-injector"

local dragoncore = require "dragoncore"
local utils = dragoncore.utils

local sfml = 
{
	location = "SFML"
};

function sfml.project(rootdir)
	-- sfml-graphics
	-- sfml-audio
	-- sfml-system
	-- sfml-window

	project "sfml-system"
		location (rootdir .. "Build/")
		kind "StaticLib"

		utils.project_defaults();
		
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
			rootdir .. [[src/SFML/System/*.hpp]],
			rootdir .. [[src/SFML/System/*.cpp]],
			rootdir .. [[src/SFML/System/Win32/*.cpp]],
			rootdir .. [[src/SFML/System/Win32/*.hpp]]
		}

		includedirs
		{
			rootdir .. [[include/]],
			rootdir .. [[src/]],
		}
		
	project "sfml-audio"
		location (rootdir .. "Build/")
		kind "StaticLib"

		utils.project_defaults();
		
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
			rootdir .. [[src/SFML/Audio/*.*]],
			rootdir .. [[src/SFML/Audio/**.hpp]]
		}

		includedirs
		{
			rootdir .. [[include/]],
			rootdir .. [[src/]],
			rootdir .. [[extlibs/headers/]],
			rootdir .. [[extlibs/headers/AL/]]
		}

		links
		{
			"sfml-system"
		}
	
	project "sfml-window"
		location (rootdir .. "Build/")
		kind "StaticLib"

		utils.project_defaults();
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC"
		}

		files
		{
			rootdir .. [[src/SFML/Window/Win32/**.cpp]],
			rootdir .. [[src/SFML/Window/Win32/**.hpp]],
			rootdir .. [[src/SFML/Window/*.hpp]],
			rootdir .. [[src/SFML/Window/*.cpp]]
		}

		excludes 
		{
			rootdir .. "src/SFML/Window/EGLCheck.cpp",
			rootdir .. "src/SFML/Window/EGLCheck.hpp",
			rootdir .. "src/SFML/Window/EglContext.cpp",
			rootdir .. "src/SFML/Window/EglContext.hpp"
		}

		includedirs
		{
			rootdir .. [[include/]],
			rootdir .. [[src/]],
			rootdir .. [[extlibs/headers/stb_image/]],
			rootdir .. [[extlibs/headers/freetype2/]],
		}
			
		filter {}
		
		links
		{
			"sfml-system"
		}	
	
    project "sfml-graphics"
        location (rootdir .. "Build/")
        kind "StaticLib"

        utils.project_defaults();
		
		defines 
		{
			"WIN32",
			"_WINDOWS",
			"SFML_STATIC"
		}

        files
        {
            rootdir .. [[src/SFML/Graphics/**.cpp]],
			rootdir .. [[src/SFML/Graphics/**.hpp]]
        }

        includedirs
        {
            rootdir .. [[include/]],
			rootdir .. [[src/]],
			rootdir .. [[extlibs/headers/stb_image/]],
			rootdir .. [[extlibs/headers/freetype2/]]
        }
		
		links
		{
			"sfml-window",
			"sfml-system"
		}

	filter {}
end

function sfml.include(rootdir)
    includedirs
    {
		rootdir .. [[include/]],
	}

	filter "architecture:x64"
		libdirs
		{
			rootdir .. [[extlibs/libs-msvc/x64/]],
		}

	filter "architecture:x86"
		libdirs
		{
			rootdir .. [[extlibs/libs-msvc/x86/]],
		}
	
	-- Reset Filter
	filter {}

	defines 
	{
		"SFML_STATIC",
		"DRAGON_RENDERSKIN=DRAGON_RENDERSKIN_SFML"
	}
end

function sfml.link(rootdir, dragonlibdir)
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

	libdirs 
	{
		dragonlibdir .. "sfml-graphics",
		dragonlibdir .. "sfml-audio",
		dragonlibdir .. "sfml-system",
		dragonlibdir .. "sfml-window",
	}
end

dependencies.add("SFML", sfml)