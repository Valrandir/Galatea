@echo off
echo.
echo Visual Studio 2012 CleanUp
echo.

rd /s /q CoreLib\Build
rd /s /q CoreSpecimen\Build

del *.sdf
del /ah *.suo
del CoreLib\*.user
del CoreSpecimen\*.user
