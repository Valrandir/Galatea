REM Should be run from PostBuildEvent
REM $(SolutionDir)Copy_SDL2_dll.bat $(SolutionDir) $(PlatformTarget) $(OutDir)
xcopy /D %1..\..\..\SDL2\lib\%2\SDL2.dll %3
xcopy /D %1..\..\..\SDL2_image\lib\%2\libpng*.dll %3
xcopy /D %1..\..\..\SDL2_image\lib\%2\SDL2_image.dll %3
xcopy /D %1..\..\..\SDL2_image\lib\%2\zlib1.dll %3
