@echo off
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
del CoreLib\CoreLib.txt

rd /s /q CoreSpecimen\Debug
del CoreSpecimen\CoreSpecimen.txt
