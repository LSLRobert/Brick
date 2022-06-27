@echo off
:folder
if not exist bin mkdir bin

:name_list
set NAME=Engine Window

:: gcc ./src/Engine.cpp -o ./bin/Engine.o -c
set count=0
set object=
:compile_objects
(for %%a in (%NAME%) do ( 
  gcc ./src/%%a.cpp -o ./bin/%%a.o -c
  set /a count+=1
))
:loop
set /a count-=1
setlocal EnableDelayedExpansion
set object=%object% ./bin/!NAME[%count%]!.o
if not %count% equ 0 (
  goto loop
)

:link_objects
::gcc -O3 -g3 -Wall -std=c++11 -o ./bin/Engine.exe ./bin/Window.o ./bin/Engine.o -static -lstdc++ -lopengl32
gcc -O3 -g3 -Wall -std=c++11 -o ./bin/Engine.exe%object% -static -lstdc++ -lopengl32



::    
::    
::    :library
::    rem set linkPath=-LC:\
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
::    ::   copy/-y/b .\lib\glfw3.dll .\bin\glfw3.dll
::    :: )
::    :: if not exist ./bin/imgui.dll (
::    ::   echo copying imgui.dll
::    ::   copy/-y/b .\lib\imgui.dll .\bin\imgui.dll
::    :: )
::    
::    :end
::    