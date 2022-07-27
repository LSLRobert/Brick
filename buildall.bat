@echo off

:Harold
pushd Harold
call clean.bat
call build.bat
popd

:Sandbox
pushd Sandbox
call clean.bat
call build.bat
popd
