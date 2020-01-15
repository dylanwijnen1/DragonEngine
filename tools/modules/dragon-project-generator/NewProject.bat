@ECHO OFF

set /p PRJ_NAME="Enter Project Name: "
CALL "../../premake5.exe" newproject --file="dragon-project-generator.lua" --projectname="%PRJ_NAME%"

PAUSE