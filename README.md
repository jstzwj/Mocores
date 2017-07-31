![](doc/logo/logo_small.png)
A distributed computing system.
======

Language
======
*[English](https://github.com/toyteam/Mocores/blob/master/doc/readme_en.md) </br>
*[中文](https://github.com/toyteam/Mocores/blob/master/doc/readme_zh.md)


Introduction
======
Mocores is a distributed computing system that utilizes idle computer resources. Unlike other distributed systems, the subnodes of the system can be unreliable and have poor network communication. The system is suitable for solving problems with large computationally intensive parallelism problems.

# Environment compatibility
This software is writen in c++ 11. It was tested in MSVC15 and GNUC4.9.2 compiler.


# Installation

## Using Visual Studio
Get the required tools:  
CMake. This is used for generating Visual Studio solution and project files. Get it from: http://www.cmake.org/cmake/resources/software.html  
Visual Studio 2015 or later  

Run CMake to generate the Visual Studio solution and project files:  
`cd Mocores\src\masternode`  
mkdir build (for building without polluting the source dir)  
`cd build`  
If you are using Visual Studio 2015: cmake -G "Visual Studio 14 2015" ..\  
The above, if successful, will have created a MocoresMaster.sln file in the build directory.  


Development process
------



How to use it
------




Contact me
------
e-mail:1103870790@qq.com
