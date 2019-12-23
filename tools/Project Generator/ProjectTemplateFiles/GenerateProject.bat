@ECHO OFF

ECHO [DragonEngine] Relinking Engine Files.
CALL "_ENGINE_LOCATION_tools/premake5.exe" vs2019 --file="_ENGINE_LOCATION_premake5.lua" > nul

CALL "_ENGINE_LOCATION_tools/premake5.exe" vs2019 --file="premake5.lua"

PAUSE