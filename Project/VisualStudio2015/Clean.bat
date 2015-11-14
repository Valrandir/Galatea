rd /s /q .vs
rd /s /q Debug
rd /s /q Release
rd /s /q x64
del *.opensdf
del *.sdf

cd Galatea

rd /s /q Debug
rd /s /q Release
rd /s /q x64
del *.user

cd ..\GalateaTest

rd /s /q Debug
rd /s /q Release
rd /s /q x64
del *.user
