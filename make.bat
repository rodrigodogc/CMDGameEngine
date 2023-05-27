cls
@echo off
del .\build\TestEnv.exe
cmake --build ./build --config Debug --target all -j 6 --
start build/TestEnv.exe
