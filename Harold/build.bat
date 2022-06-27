@echo off
:folder
if not exist bin mkdir bin
if not exist obj mkdir obj

:project_name
set /p NAME=<name.bat

:flags
:: -O0 / -O3 -g3 : Release / Debug
set Release=-O0
set Debug=-O3 -g3
set Warning=-Wall
set FLAGS=%Debug% %Warning% -std=c11

:compile_objects
gcc ./src/main.c -o ./obj/main.o -c
gcc ./src/window/window.c -o ./obj/window.o -c
gcc ./src/window/screen.c -o ./obj/screen.o -c



:library
set Library=-lopengl32

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