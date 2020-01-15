-- TODO: Add Template support ? Allows users to make their own project templates.

local MODULE_NAME = "Dragon Project Generator";
local DEFAULT_PRJ_NAME = "DragonGame";

-- Create the module namespace.
premake.modules.dragon_project_generator = {}
local m = premake.modules.dragon_project_generator

-- Include options and actions. This is now safe since we've created our module namespace.
include "_options.lua"
include "_actions.lua"

-- Root path to engine from current file location.
local DRAGON_ENGINE_ROOT = path.getabsolute("../../../");

--- Called by action : newproject
function m.initialize()

    -- Create the token table.
    m._tokens = {}

    -- Set all option values passed into the command line and add them to the module space.
    m.projectName = m._defaultOrOption("projectname", m.getDefaultNewProjectName());
    m.projectLocation = m._defaultOrOption("projectlocation", DRAGON_ENGINE_ROOT .. "/projects/");

    -- Determine the path to the engine root folder.
    m.pathToRoot = path.getrelative(m.projectLocation .. m.projectName .. "/", DRAGON_ENGINE_ROOT);

    -- Add generator default tokens.
    m.addToken("PRJ_NAME", m.projectName);
    m.addToken("PRJ_LOCATION", m.projectLocation);
    m.addToken("DRAGON_ENGINE_ROOT", m.pathToRoot);

end

--- Returns an option or the given default.
--- @param key string | "The option key."
--- @param default any | "The default item to return when option has not been set."
function m._defaultOrOption(key, default)

    local val = _OPTIONS[key] or nil;
    
    if val == nil then
        val = default;
    end

    return val;

end

--- Returns the default new project name using the count of `DEFAULT_PRJ_NAME` matches found.
--- @return string | "A name for a new project."
function m.getDefaultNewProjectName()
    return DEFAULT_PRJ_NAME .. "_#";
end

--- Tokens must be added before project is being generated, obviously.
--- @param token string | "The text to be replaced."
--- @param replacement string|function | "The text to replace the token."
--- @return boolean @"Wether or not the token was added."
function m.addToken(token, replacement)

    -- Initialization step hasn't happened.
    if m._tokens == nil then
        return false;
    end


    if m._tokens[token] ~= nil then
        m._printDebug("Token already exists. Discarding token.");
        return false;
    end

    local replacementType = type(replacement);

    if replacementType ~= "string" and replacementType ~= "function" then
        m._printDebug("Token `" .. token .. "` replacement is not of type string or function. Type is : " .. replacementType);
        return false;
    end

    m._printDebug("Adding token: " .. token);

    m._tokens[token] = replacement;

    return true;

end

--- Lists all tokens currently registered to the generator module.
function m.listTokens()

    m._printDebug("Tokens:");

    if m._tokens ~= nil then

        for tok, repl in pairs(m._tokens) do

            print("\t- " .. tok .. ": ");

            -- Print token replacement.
            local replType = type(repl);

            if replType == "string" then
                print(repl);
            else
                print(replType);
            end

        end

    end

end

--- Reads an entire file into a string.
--- @param filename string | "The name of the file to read."
--- @return string | "The entire file as a string."
function m._readfile(filename)

    local f = assert(io.open(filename, "rb"));
    local content = f:read("*all");
    f:close();
    return content;

end

--- Gets the replacement part for the token.
--- @param token string | "The token to replace."
function m._getTokenReplacement(token)

    -- Find the token if it exists.
    local replacement = m._tokens[token] or nil;

    -- Check for nil.
    if replacement ~= nil then

        local replType = type(replacement);

        -- Return the string.
        if replType == "string" then
            return replacement;
        -- If function, Call the function passing in the token.
        elseif replType == "function" then
            return replacement(token);
        else
            return nil;
        end

    else
        
        m._printInfo("Found token but could not find a suitable replacement. Token: " .. token);

    end


end

--- Replaces the tokens inside a string.
--- @param text string | "A string to replace tokens on."
--- @return string | "A string containing the modified text."
function m._replaceTokens(text)

    local repl = function(token)

        local result = m._getTokenReplacement(token);

        return result;

    end

    -- Find every token matching the following pattern
    local result, num = string.gsub(text, "@{(.-)}@", repl);

    return result;

end


function m.generateProjectFiles()

    -- debug.prompt();

    -- Grab the template files.
    local matches = os.matchfiles("ProjectTemplateFiles/**.*");

    -- Do tokenization of template files.
    for _, match in pairs(matches) do
        
        local newFilename = m._replaceTokens(match);
        newFilename = string.gsub(newFilename, "ProjectTemplateFiles", m.projectLocation .. m.projectName);

        local content = m._readfile(match);
        local result = m._replaceTokens(content);
        
        local written = io.writefile(newFilename, result);

        if written then
            m._printInfo("Writing file: " .. newFilename);
        else
            m._printError("Could not write file: " .. newFilename);
        end

    end
    
end

--- Prints using the modules name.
--- @varargs string
function m._printDebug(...)
    print("[" .. MODULE_NAME .. "] ");
    print(...);
end

--- Prints using the modules name.
--- @varargs string
function m._printInfo(...)
    premake.info("[" .. MODULE_NAME .. "] ");
    premake.info(...);
end

--- Prints using the modules name.
--- @varargs string
function m._printError(...)
    premake.error("[" .. MODULE_NAME .. "] ");
    premake.error(...);
end

return m;