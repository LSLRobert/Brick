@echo off
set /p NAME=<name.bat
pushd bin
call %NAME% %1 %2 %3 %4 %5 %6 %7 %8 %9
popd bin
:end
