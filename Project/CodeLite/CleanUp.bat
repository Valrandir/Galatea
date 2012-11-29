@echo off
rd /s /q .build-debug
rd /s /q .clang
del Core.tags
del Core.workspace.session
del Core.workspace.valrandir

rd /s /q CoreLib\Debug
del CoreLib\CoreLib.txt

rd /s /q CoreSpecimen\Debug
del CoreSpecimen\CoreSpecimen.txt
