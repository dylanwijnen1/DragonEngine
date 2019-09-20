@ECHO OFF

CALL premake5.exe --file="../premake5.lua" vs2019 graphics=sfml

PAUSE