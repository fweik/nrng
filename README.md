# Numeric RaNGes

[![codecov](https://codecov.io/gh/fweik/nrng/branch/main/graph/badge.svg)](https://codecov.io/gh/fweik/nrng)

![CMake](https://github.com/lefticus/cpp_starter_project/workflows/CMake/badge.svg)

This repository provides the constrained and range-based version of the algorithms from the STL numerics
library that did not make it into C++20.

## Getting Started

The library is header only and has no dependencies, except a C++20 compatible compiler with concept and
ranges support. It can be consumed via cmake by adding it as a subdirectory, in which case the target
`nrng::nrng` will be available, or by copying the files under `include` to a place where they are found.
Installing the library is currently not supported.

### Necessary Dependencies
1. A C++ compiler that supports C++20.
See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
to see which features are supported by each compiler.
2. [CMake 3.15+](https://cmake.org/)
	<details>
	<summary>Install Command</summary>
	
	- Debian/Ubuntu:
		
			sudo apt-get install cmake
	
	- Windows:
		
			choco install cmake -y
	
	- MacOS:
	 		
			brew install cmake
	
	</details>

### Optional Dependencies
#### C++ Tools
  * [Doxygen](http://doxygen.nl/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:
		
			sudo apt-get install doxygen
			sudo apt-get install graphviz

	- Windows:
		
			choco install doxygen.install -y
			choco install graphviz -y

	- MacOS:
 		
			brew install doxygen
	 		brew install graphviz

	</details>


  * [ccache](https://ccache.dev/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:
		
			sudo apt-get install ccache

	- Windows:
		
			choco install ccache -y

	- MacOS:
 		
			brew install ccache

	</details>


  * [include-what-you-use](https://include-what-you-use.org/)
	<details>
	<summary>Install Command</summary>

	Follow instructions here:
	https://github.com/include-what-you-use/include-what-you-use#how-to-install
	</details>

## Build Instructions

Instruction for building the tests.

### Build directory
Make a build directory:
```
mkdir build
```
### Specify the compiler using environment variables

By default (if you don't set environment variables `CC` and `CXX`), the system default compiler will be used.

Conan and CMake use the environment variables CC and CXX to decide which compiler to use. So to avoid the conflict issues only specify the compilers using these variables.

CMake will detect which compiler was used to build each of the Conan targets. If you build all of your Conan targets with one compiler, and then build your CMake targets with a different compiler, the project may fail to build.

<details>
<summary>Commands for setting the compilers </summary>

- Debian/Ubuntu/MacOS:
	
	Set your desired compiler (`clang`, `gcc`, etc):
		
	- Temporarily (only for the current shell)
	
		Run one of the followings in the terminal:
	
		- clang
		
				CC=clang CXX=clang++
			
		- gcc
		
				CC=gcc CXX=g++
	
	- Permanent:

		Open `~/.bashrc` using your text editor:
			
			gedit ~/.bashrc
			
		Add `CC` and `CXX` to point to the compilers:
			
			export CC=clang
			export CXX=clang++
			
		Save and close the file.

- Windows:

	- Permanent:
	
		Run one of the followings in PowerShell:
				
		- Visual Studio generator and compiler (cl)
			
				[Environment]::SetEnvironmentVariable("CC", "cl.exe", "User")
				[Environment]::SetEnvironmentVariable("CXX", "cl.exe", "User")
				refreshenv
			
		  Set the architecture using [vsvarsall](https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=vs-2019#vcvarsall-syntax):
			
				vsvarsall.bat x64

		- clang

				[Environment]::SetEnvironmentVariable("CC", "clang.exe", "User")
				[Environment]::SetEnvironmentVariable("CXX", "clang++.exe", "User")
				refreshenv
	 
		- gcc

				[Environment]::SetEnvironmentVariable("CC", "gcc.exe", "User")
				[Environment]::SetEnvironmentVariable("CXX", "g++.exe", "User")
				refreshenv
	 

  - Temporarily (only for the current shell):
		
			$Env:CC="clang.exe"
			$Env:CXX="clang++.exe"
			
</details>

### Configure your build

To configure the project and write makefiles, you could use `cmake` with a bunch of command line options.
The easier option is to run cmake interactively:

#### **Configure via ccmake**:
with the Cmake Curses Dialog Command Line tool:  

    ccmake -S . -B ./build

Once `ccmake` has finished setting up, press 'c' to configure the project, 
press 'g' to generate, and 'q' to quit.

### Build
Once you have selected all the options you would like to use, you can build the 
project (all targets):

    cmake --build ./build

For Visual Studio, give the build configuration (Release, RelWithDeb, Debug, etc) like the following:

    cmake --build ./build -- /p:configuration=Release
