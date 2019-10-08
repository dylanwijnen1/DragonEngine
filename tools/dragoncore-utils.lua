local DEPENDENCY_MAP = {}

local outputdir = "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}"

function dragon_project_defaults()

    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    staticruntime "Off"

    targetdir("bin/" .. outputdir)
    objdir("temp/" .. outputdir)

    filter "platforms:x64"
        architecture "x64"

    filter "platforms:x86"
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

function dragon_create_dependency_projects(dependencydir)
    for k, v in pairs(DEPENDENCY_MAP) do
        filter {}
        v.project(dependencydir)

        filter {}
    end
end

function dragon_add_dependencies(dependencydir)

    for k, v in pairs(DEPENDENCY_MAP) do
        filter {}
        v.include(dependencydir)

        filter {}
        v.link()

        filter {}
    end

end

function dragon_include_dependencies(dependencydir)

    for k, v in pairs(DEPENDENCY_MAP) do

        filter {}
        v.include(dependencydir)

        filter {}
    end

end

function dragon_list_dependencies()
    print("Dependencies: ");

    for k, v in pairs(DEPENDENCY_MAP) do
        print("\t: " .. k);
    end

end

function dragon_default_outdir()
    return "%{cfg.buildcfg}_%{cfg.architecture}/%{prj.name}";
end