include "_ENGINE_LOCATION_tools/dragoncore.lua"

print("[_PRJ_NAME_] Building _PRJ_NAME_ Project Files!")

workspace "_PRJ_NAME_"

    startproject "_PRJ_NAME_"
    dragon_workspace_defaults()
    
project "_PRJ_NAME_"

    dragon_project_defaults()

    location "%{prj.name}"
    kind "ConsoleApp"

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    { 
        "%{prj.name}/src",
    }

    include_dragoncore("_ENGINE_LOCATION_")
    links { "DragonCore" }
