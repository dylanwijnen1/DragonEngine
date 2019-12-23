function dragon_default_outdir()
    return "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}";
end

-- Local Version of the Default Output Directory
local outputdir = dragon_default_outdir();

---Adds the default settings for dragon workspaces.
function dragon_workspace_defaults()
    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

    platforms
    {
        "x64",
        "Win32"
    }
end

---Adds the default settings for any dragon project.
---To override the defaults call this function first.
function dragon_project_defaults()

    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    staticruntime "Off"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    filter "platforms:x64"
        architecture "x64"

    filter "platforms:Win32"
        architecture "x86"

        filter "configurations:Debug"
        symbols "full"
        runtime "Debug"
        defines "DRAGON_DEBUG"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"
        defines "DRAGON_RELEASE"

    filter "configurations:Distribution"
        optimize "On"
        runtime "Release"
        defines "DRAGON_DIST"
        
    -- Reset filters
    filter {}

    filter {}
end