@ECHO OFF

set /p PRJ_NAME="Enter Project Name: "
CALL premake5.exe --file="new_project.lua" vs2019 --projectname="%PRJ_NAME%"

PAUSE