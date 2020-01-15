@ECHO OFF

ECHO [DragonEngine] Relinking Engine Files.
CALL "@{DRAGON_ENGINE_ROOT}@/tools/premake5.exe" vs2019 --file="@{DRAGON_ENGINE_ROOT}@/premake5.lua" > nul

CALL "@{DRAGON_ENGINE_ROOT}@/tools/premake5.exe" vs2019 --file="premake5.lua"

PAUSE