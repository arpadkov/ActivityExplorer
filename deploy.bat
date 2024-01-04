call "C:\Qt\6.5.3\msvc2019_64\bin\qtenv2.bat"

:: This gives an error, but works anyways, so not sure if it is needed
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

windeployqt.exe --qmldir "C:\Users\95arp\CPPProjects\ActivityExplorer\out\build\src\QmlForms" "%~dp0\out\build\src\ActivityExplorer.exe"