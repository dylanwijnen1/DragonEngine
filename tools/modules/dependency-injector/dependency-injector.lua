premake.modules.dragondependencies = {}
local m = premake.modules.dragondependencies

local MODULE_ROOT = path.getabsolute("");
local DRAGON_ENGINE_ROOT = path.getabsolute("../../../")
local DRAGON_DEPENDENCY_FOLDER = path.getabsolute("../../../dependencies")
local DRAGON_OUT_FOLDER = path.getabsolute("../../../bin")

-- Create an empty dependency table.
m.dependencies = {};

--- Returns the dependency folder relative to the current executing script.
local function dependencyFolder(dependencyRoot, dependency)
    return dependencyRoot .. "/" .. dependency.location .. "/";
end

--- @ref dependency-example 
--- local dep = 
--- {
---     project     = function(rootdir) end
---     include     = function(rootdir) end
---     link        = function(rootdir, outputdir) end
--- }

--- Adds a dependency project to the dependency injector.
--- @param id string | "The id of the dependency"
--- @param dependency table | "A dependency table. @see dependency-example"
function m.add(id, dependency)

    if m.dependencies[id] == nil then
        dependency.location = dependency.location or id;

        m.dependencies[id] = dependency
        printf("Registered dependency [" .. id .. "]")
    else
        printf("Dependency with id [" .. id .. "] already registered.")
    end

end

--- Lists all dependencies that are available.
function m.list()

    printf("Registered Dependencies: ")
    for id, dependency in pairs(m.dependencies) do
        printf("\t - " .. id);
    end

end

function m.details(id)

    for id, dependency in pairs(m.dependencies) do
        if dependency.shortname ~= nil then
            print("\t" .. dependency.shortname);
        end

        if dependency.description ~= nil then
            print("\t" .. dependency.description);
        end

        print("\t" .. dependency.location);

        print("\n\n");    
    end    

end

--- Links the dependency to the project.
function m._linkDependency(dependency)

    -- Dependency Root Folder
    local depRoot = dependencyFolder(DRAGON_DEPENDENCY_FOLDER, dependency);
    
    if dependency.link ~= nil then
        -- Reset Filters
        filter {}

        dependency.link(depRoot, DRAGON_OUT_FOLDER);
    end

end

--- Links a dependency to the project.
--- @param id | "The dependency id the dependency has registered with."
function m.link(id)

    local dependency = m.dependencies[id];

    if dependency ~= nil then
        m._linkDependency(dependency);
    else
        printf("Could not find the dependency: " .. id .. ".");
    end

end

--- Links all dependencies at once.
function m.linkAll()

    for _, dependency in pairs(m.dependencies) do
        m._linkDependency(dependency);
    end

end

--- Includes a dependency into the project.
--- @param dependency table | "A dependency object."
function m._includeDependency(dependency)
    
    -- Dependency Root Folder
    local depRoot = dependencyFolder(DRAGON_DEPENDENCY_FOLDER, dependency);
        
    if dependency.include ~= nil then
        -- Reset Filters
        filter {}
        
        dependency.include(depRoot);
    end

end

--- Setup Include Folders for the dependency project.
--- @param id | "The dependency id the dependency has registered with."
function m.include(id)

    local dependency = m.dependencies[id];

    if dependency ~= nil then
        m._includeDependency(dependency);
    else
        printf("Could not find the dependency: " .. id .. ".");
    end

end

--- Includes all dependencies into the project.
function m.includeAll()

    for _, dependency in pairs(m.dependencies) do
        m._includeDependency(dependency)
    end

end

--- Links and includes the dependency.
function m.require(id)

    local dependency = m.dependencies[id];

    if dependency ~= nil then
        m._includeDependency(dependency);
        m._linkDependency(dependency);
    else
        printf("Could not find the dependency: " .. id .. ".");
    end

end

--- Generates the project for the dependency.
function m.generateProjects()

    for _, dependency in pairs(m.dependencies) do

        local depRoot = dependencyFolder(DRAGON_DEPENDENCY_FOLDER, dependency);

        if dependency.project ~= nil then
            dependency.project(depRoot);
        end

    end

end

return m;