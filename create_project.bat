cmake -E make_directory ./build

cmake -E chdir ./build cmake .. -G "Visual Studio 15 2017"