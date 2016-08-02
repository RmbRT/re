# RmbRT Engine Readme

**The RmbRT Engine is still in the WIP stage, thus not yet usable.**

## Setup Guide

### Cloning the repository

Make sure to have git installed on your machine. Now select the folder you want to download the RmbRT Engine to and execute:

`
git clone https://github.com/RmbRT/re.git
`

### CMake
Clone the repository, go into the `re/` folder, make sure CMake is installed, and execute:

`
cmake .
`

This creates project files (or makefiles, depending on your machine), which you can use to compile the RmbRT Engine. Also copies all header files of the RmbRT Engine to `re/include/re/`, so that you can use the directory `re/include/` as include directory for your project that uses the RmbRT Engine.
### Doxygen
You have to have Doxygen installed. Now go to `re/`, and execute:

`
doxygen Doxyfile
`

This will generate a Doxygen documentation in `re/html`.

## What's included?

### Sources

#### Dependencies

The RmbRT Engine depends on certain libraries, which can be found in `re/depend/`, namely:
* **GLFW**: The RmbRT Engine comes with its own copy of the [GLFW](https://github.com/glfw/glfw.git) source code, to ensure more portability.
* **Lock**: The thread safety library ['Lock'](https://github.com/RmbRT/Lock.git) is also included.

#### RmbRT Engine

The RmbRT Engine source code is included as well, obviously, and can be found in `re/src/`.

### License

You can find the license in the text file `re/LICENSE`.

### Readme

You are currently reading the readme file `re/README.md`.

### Doxygen Doxyfile

A Doxyfile can be found in `re/doxygen/`. It is set to generate a HTML documentation in `re/doxygen/html/` per default. Please note that in order to reduce the size of the repository, the documentation is not part of it. This means you will have to install Doxygen on your machine and generate the documentation yourself. For this, see the [Doxygen installation section](#doxygen).

### CMake CMakeLists.txt

The CMake script `re/CMakeLists.txt` is used to generate the several project files / makefiles (depending on your machine) that are used to compile the RmbRT Engine and its dependencies. It also generates the directory `re/include/`, which contains all header files used by the RmbRT Engine.