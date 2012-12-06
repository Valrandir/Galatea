@echo off
rd /s /q Debug
rd /s /q CoreLib\Debug
rd /s /q CoreSpecimen\Debug

del *.sdf
del /ah *.suo
del CoreLib\*.user
del CoreSpecimen\*.user
