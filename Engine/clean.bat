@echo off
set folder=bin
:loopBin
del /s /q /f \%folder%\*.* > nul 2> nul
rmdir /s /q %folder% > nul 2> nul
if exist %folder% goto loopBin
:end
