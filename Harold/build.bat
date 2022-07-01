@echo off & setlocal enabledelayedexpansion
:folder
if not exist bin mkdir bin
if not exist obj mkdir obj

:project_name
set /p NAME=<name.bat

:file_list
set MAIN=.\src\main.c
set WIND=.\src\window\window.c .\src\window\screen.c

set FILES=%MAIN% %WIND%

:day_year
set "_cmd=Get Day^,Month^,Year^"
for /l %%L in (2020 4 2100)do set "_array_leap_year_=!_array_leap_year_!%%L,"
for /f "tokens=1-3delims= " %%a in ('wmic Path Win32_LocalTime !_cmd! ^| findstr /r "[0-9]"') do (
  set "_yy=%%c"
  set "_mm=0%%b"
  set "_dd=0%%a"
  set "_mm=!_mm:~-2!"
  set "_dd=!_dd:~-2!"
  set _date=!_yy!_!_mm!_!_dd!
)
echo/!_array_leap_year_!|findstr /lic:"!_date:~0,4!," >nul && ( 
  set "_leap_=29" & set "_year_=366" 
)||(
  set "_leap_=28" & set "_year_=365"
)
set "_mm_dd_year_=01-31,02-!_leap_!,03-31,04-30,05-31,06-30,07-31,08-31,09-30,10-31,11-30,12-31"
set /a "_loop=!_mm! * 6"

for /l %%d in (0 6 !_loop!) do set "_sum=!_mm_dd_year_:~%%d,5!" && (
  if "9!_sum:~,2!" lss "9!_mm!" set /a "_day_year_+=!_sum:~-2!"
)
set /a "_day_year_+=!_dd!"
set /a "_remain=!_day_year_! - !_year_!"
:: echo/Today: !_date! ^| Day of Year: !_day_year_! ^| Days Remaining: !_remain:-=!

:version
:: Major Version set by Developer
set VMAJ=0
set VMID=%date:~-2%
set VMIN=!_day_year_!
set /p VBUILD=<version/vbuild.inf

echo %VMAJ% >version/vmaj.inf
echo %VMID%>version/vmid.inf
echo %VMIN%>version/vmin.inf
set /a VBUILD=%VBUILD%+1
echo %VBUILD%>version/vbuild.inf

echo Version %VMAJ%.%VMID%.%VMIN%.%VBUILD%

:flags
:: -O0 / -O3 -g3 : Release / Debug
set Release=-O0
set Debug=-O3 -g3
set Warning=-Wall
set FLAGS=%Debug% %Warning% -std=c11

:compile_objects
::gcc ./src/main.c -o ./obj/main.o -c
(for %%f in (%FILES%) do ( 
  gcc %%f -o %%f.o -c
  move/y %%f.o ./obj > null
))

:library
set Library=-lgdi32 -lopengl32

:resource
windres -i ./res/resource.rc -o ./obj/resource.o

:link_objects
gcc %FLAGS% -o ./bin/%NAME%.exe ./obj/*.o %Library%


:: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: 
::
::            Set up libs and moving libs to the BIN folder
::
:: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: :: TODO :: 
::    
::    
::    :library
::    rem set linkPath=-LC:/
::    :: set linkGLFW=../lib/libglfw3dll.a
::    :: set linkIMGUI=../lib/limgui.a
::    :: set linkGl=-lopengl32
::    :: set linkLibs=-static -lstdc++ %linkGl% %linkGLFW% %linkIMGUI%
::    
::    :Executable
::    pushd bin
::    
::    rem -O0 / -O3 -g3 : Release / Debug
::    :: gcc -O3 -g3 -Wall -std=c++11 ../src/%NAME%.cpp -o ../bin/%NAME%.exe %linkLibs%
::    gcc -O3 -g3 -Wall -std=c++11 ../src/%NAME%.cpp -o ../bin/%NAME%.exe -static -lstdc++ -lopengl32
::    
::    popd bin
::    
::    :: :move
::    :: if not exist ./bin/glfw3.dll (
::    ::   echo copying glfw3.dll
::    ::   copy/-y/b ./lib/glfw3.dll ./bin/glfw3.dll
::    :: )
::    :: if not exist ./bin/imgui.dll (
::    ::   echo copying imgui.dll
::    ::   copy/-y/b ./lib/imgui.dll ./bin/imgui.dll
::    :: )
::    
::    :end
::    