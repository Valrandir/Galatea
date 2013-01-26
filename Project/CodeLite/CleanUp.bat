@echo off
echo.
echo CodeLite CleanUp
echo.

rd /s /q .build-debug-32
rd /s /q .build-debug-64
rd /s /q .build-release-32
rd /s /q .build-release-64
rd /s /q .clang
del Core.tags
rename Core.workspace cw.void
del Core.workspace*
rename cw.void Core.workspace

rd /s /q CoreLib\Debug
rd /s /q CoreLib\Release
del CoreLib\CoreLib.txt

rd /s /q CoreSpecimen\Debug
rd /s /q CoreSpecimen\Release
del CoreSpecimen\CoreSpecimen.txt

del CoreLib\*.mk
del CoreSpecimen\*.mk
del *.mk
