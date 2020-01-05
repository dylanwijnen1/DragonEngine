local m = premake.modules.dragon_project_generator

newaction {
	trigger = "newproject",
	description = [[
        Generates a new dragon project.
        - Default Location : ~/projects/
        - Default Name : DragonGame_#, Where `#` is the current count of DragonGame's
        ]],

    onStart = function()
        m.initialize();
	end,
    
    execute = function()
        
        print("Generating project [" .. m.projectName .. "] at : " .. m.projectLocation)
        m.generateProjectFiles();

	end,

	onEnd = function()
		print("Finished generating project : " .. m.projectName);
	end
}