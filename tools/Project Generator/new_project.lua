
--- Sets the PROJECT_NAME local variable.
newoption 
{
    trigger     = "projectname",
    value       = "newproject",
    description = "The name of the project"
}

local PROJECT_NAME = _OPTIONS["projectname"] or "NewProject"

-- TODO: If projectlocation was given as option, figure out the path to the engine.
local ENGINE_LOC = "../../"

printf("Generating project: %s", PROJECT_NAME)

---@param text string | The text to replace tokens in.
function replace_tokens(text)
    text = text:gsub("_PRJ_NAME_", PROJECT_NAME)
    text = text:gsub("_ENGINE_LOCATION_", ENGINE_LOC)
    return text
end

function readfile(filename)
    local f = assert(io.open(filename, "rb"))
    local content = f:read("*all")
    f:close()
    return content
end

matches = os.matchfiles("ProjectTemplateFiles/**.*")
for key, match in pairs(matches) do
    newFilename = replace_tokens(match):gsub("ProjectTemplateFiles/", "../../projects/" .. PROJECT_NAME .. "_Game/")
    content = readfile(match)
    content = replace_tokens(content)

    io.writefile(newFilename, content);
end
