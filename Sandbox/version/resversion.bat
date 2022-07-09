@echo off

:version
set /p VMAJ=<version/vmaj.inf
call :trim %VMAJ%
set VMAJ=%TRIMRESULT%

set /p VMID=<version/vmid.inf
call :trim %VMID%
set VMID=%TRIMRESULT%
set /p VMIN=<version/vmin.inf

call :trim %VMIN%
set VMIN=%TRIMRESULT%

set /p VBUILD=<version/vbuild.inf
call :trim %VBUILD%
set VBUILD=%TRIMRESULT%

echo #define RESVERSION %VMAJ%,%VMID%,%VMIN%,%VBUILD% > version.h
goto eof

:trim
::  echo "%1"
::  echo "%2"
::  echo "%3"
::  echo "%4"
set TRIMRESULT=%*
goto eof

:eof
