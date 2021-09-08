# Basic principles of the example

## Requirements:

- Python 3.6+
- Qt 6.0+
- libclang, recommended: version 10 for 6.0+
- CMake: 3.1+
- ninja-build, useful building tool

Required Qt tools for the python binding:
- PySide6
- Shiboken6
- Shiboken6_generator

Useful links:
- [Qt for Python Homepage](https://doc.qt.io/qtforpython/)
- [Shiboken homepage](https://doc.qt.io/qtforpython/shiboken6/index.html)
- [Shiboken basic installation page](https://doc.qt.io/qtforpython/shiboken6/gettingstarted.html)

## Files contained:

- example.cpp:      c++ file containing necessary class
- exaple.h:         header file for the above class
- bindings.h:       necessary file defining-containing the rest of the header files
- macros.h:         standard needed file
- pyside_config.py  standard needed file, its location should be taken into consideration at the CMakeLists.txt file
- CMakeLists.txt    mostly standard file, with some location/name adjustments needed: does all the building needed
- main.py       our python file doing most of the work
- bindings.xml      necessary in most cases typesystem file which handles possible problems due to python/c++ incompatibilities

## Basic building process:

Starting from the folder containing all the above files

mkdir build                                           create building folder<br>
cd build
cmake -H.. -B. -G Ninja -DCMAKE_BUILD_TYPE=Release    1st building step
ninja                                                 2nd building step
ninja install                                         3rd building step
cd ../
python main.py                                        run the program

New files created in the process:

- everything in the build folder, no need to be altered
- libexample.so:   the shared library-object being created
- MyModule.so:     shared object, the module that will be called from our python main file
