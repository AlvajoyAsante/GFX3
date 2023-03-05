:: Alvajoy "Alvajoy123" Asante
:: Last updated: 9/5/2022
:: This compiles the API into a folder and uses it to detect bugs of any sort.

@echo off

set API_NAME = GFX3

title Testing: GFX3
:start

:: Deletes the old version so it does not conflit with the new version
echo Deleting the old version of %API_NAME% from testing folder...
rmdir /S/Q ".\src\gfx3"

@echo Cleaning folder directories for compiling ...
make %clean

:: Clears the screen of any infomations displayed whiles deleting the folder.
cls

:: Makes a folder named notify and copies all the source code into the hyra folder
echo Copying the lastest version of %API_NAME% into testing folder...
mkdir .\src\gfx3
xcopy /y/s/i "..\gfx3" .\src\gfx3

:: Clears the screen of any infomations displayed whiles create folder.
cls

:: Compiles all the program in order to test for errors and bugs
make %debug
set /p dummyVar= 

:: Once the bug has been fixed then cleans via dev then the screen is cleared. 
cls
goto start