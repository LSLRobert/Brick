@echo off
:folder
set FOLDER=bak
if not exist .\%FOLDER% mkdir %FOLDER%
:name
set NAME=Engine
:year
set year=%date:~-4%
rem echo year=%year%
:month
set month=%date:~4,2%
if "%month:~0,1%" == " " set month=0%month:~1,1%
rem echo month=%month%
:day
set day=%date:~7,2%
if "%day:~0,1%" == " " set day=0%day:~1,1%
rem echo day=%day%
:hour
set hour=%time:~0,2%
if "%hour:~0,1%" == " " set hour=0%hour:~1,1%
rem echo hour=%hour%
:minute
set min=%time:~3,2%
if "%min:~0,1%" == " " set min=0%min:~1,1%
rem echo min=%min%
:second
set secs=%time:~6,2%
if "%secs:~0,1%" == " " set secs=0%secs:~1,1%
rem echo secs=%secs%
set datetimef=%year%%month%%day%_%hour%%min%%secs%
:execute
if not exist ./%FOLDER%/%NAME%_%datetimef%.zip (
 	7z.exe -r a ./%FOLDER%/%NAME%_%datetimef%.zip * *.* -x!bak* -x!bin
)
:output
if not exist ./%FOLDER%/%NAME%_%datetimef%.zip goto nope
echo The Project "%NAME%" backup was created on %date% at %time%.
echo Backup file: %NAME%_%datetimef%.zip
goto end
:nope
echo FAILED to created bachup on %date% at %time%.
echo Backup file FAILED: %NAME%_%datetimef%.zip
echo.
:end
