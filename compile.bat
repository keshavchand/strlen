@echo off

set optimizations=
::/O2
mkdir build
pushd build
pwd

cl /Zi %optimizations% /DEBUG:FULL /c ..\src\strlen.cpp 
cl /Zi %optimizations% /DEBUG:FULL /c ..\src\test.cpp 
cl /Zi strlen.obj test.obj /Festrlen
popd 
