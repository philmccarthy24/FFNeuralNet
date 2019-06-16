FFNeuralNet
===========

Neural net implementation in C++.

This is a project to learn about AI and neural network programming. I've so far implemented a non-batch vanilla backprop
algorithm which allows the neural network to be trained.

I've used the Eigen C++ linear algebra library to do the heavy lifting on the neural net weight matrix calculations.

Up next: try some applications more fun than XOR (!). Try better learning algorithms. Tidy up and optimise code.
Might also port to other platforms (linux and Windows?) as well as try porting to other languages if I'm still
finding this fun.
Also want to explore hidden markov models.

Phil McCarthy
April 2014

---

Updated June 2019
=================

Added CMakeLists.txt for cross platform C++ support.

Use a package manager like vcpkg to fetch libs:
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat or ./bootstrap-vcpkg.sh
.\vcpkg install eigen3
.\vcpkg install catch
```

If vcpkg dir is set to environment variable %VCPKG_ROOT% Then build using:

```
cd FFNeuralNet
mkdir build
cd build
cmake -G "Visual Studio 15 2017" .. -DCMAKE_TOOLCHAIN_FILE="$($Env:VCPKG_ROOT)\scripts\buildsystems\vcpkg.cmake"
cmake --build . --config Release
```