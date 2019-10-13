local DEPENDENCY_MAP = {}

function dragon_default_outdir()
    return "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}";
end
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

    filter "configurations:Release"
        optimize "On"
        runtime "Release"

    filter "configurations:Distribution"
        optimize "On"
        runtime "Release"

    filter {}
end

---Add a project to the dependency list.
---@param project_name string   | "Name of the project that is being generated."
---@param project function      | "The function that generates the project."
---@param include function      | "The function that includes the project files."
---@param link function         | "The function that links the project."
function add_dependency_project(project_name, project, include, link)
    local dep = DEPENDENCY_MAP[project_name];
    if dep == nil then
        dep = {};
        dep.project_name = project_name;
        dep.project = project;
        dep.include = include;
        dep.link = link;
        DEPENDENCY_MAP[project_name] = dep;

        print("Registered dependency project " .. project_name);
    else
        print("Failed to add project " .. project_name .. " already exists.");
    end
end


---Creates the dependency projects.
---@param dependencydir     | "The root of the dependency directory"
function dragon_create_dependency_projects(dependencydir)
    for k, v in pairs(DEPENDENCY_MAP) do
        filter {}

        v.project(dependencydir)

        filter {}
    end
end

---Link and Include the dependencies.
---@param dependencydir     | "The root of the dependency directory"
function dragon_add_dependencies(dependencydir)

    for k, v in pairs(DEPENDENCY_MAP) do
        filter {}
        
        v.include(dependencydir)

        filter {}
        
        v.link("%{cfg.targetdir}")

        filter {}
    end

end

function include_dragoncore(root)
    
    filter {}

    local dragonlibdir = root .. "bin/%{cfg.buildcfg}_%{cfg.architecture}/";

    includedirs(root .. "DragonCore/src");

    -- Link the Library
    links
    {
        "DragonCore"
    }

    -- Library Directory, Prebuild Commands
    libdirs { dragonlibdir .. "/DragonCore" }

    prebuildcommands
    {
        [[msbuild "../]] .. root .. [[DragonEngine.sln" /p:Configuration=%{cfg.buildcfg};Platform=%{cfg.platform} -m]]
    }

    -- Dependency Include and Link
    dragon_include_dependencies(root .. "dependencies/")
    dragon_link_dependencies(dragonlibdir)
end

---Include the dependencies.
---@param dependencydir     | "The root of the dependency directory"
function dragon_include_dependencies(dependencydir)

    for k, v in pairs(DEPENDENCY_MAP) do

        filter {}
        v.include(dependencydir)

        filter {}
    end

end

---Link the dependencies.
---@param dragonlibdir     | "The root of the dragon output folder"
function dragon_link_dependencies(dragonlibdir)

    for k, v in pairs(DEPENDENCY_MAP) do

        filter {}
        v.link(dragonlibdir)

        filter {}
    end

end

function dragon_list_dependencies()
    print("Dependencies: ");

    for k, v in pairs(DEPENDENCY_MAP) do
        print("\t: " .. k);
    end

end