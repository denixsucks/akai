@echo off
:: Create a build directory
mkdir build 
cd build
:: cmake config CMakeLists.txt
cmake .. -A Win32
:: build binary app
cmake --build . 
pause