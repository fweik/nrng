# Numeric RaNGes

![Linux](https://github.com/fweik/nrng/workflows/CMake/badge.svg)
![Windows](https://ci.appveyor.com/api/projects/status/1hegoxj10724qbu8?svg=true)

This repository aims to provide named, reusable numeric algorithms for C++.

It is in the very early stages, work in progress and contributions are very welcome.

## Goals

The goal is to provide generic building blocks for numeric calculations. It should help following the [no raw loops](https://www.youtube.com/watch?v=W2tWOdzgXHA)
principle when writing numerics oriented code. As such it aims to provide named, reusable algorithms and not complete solvers or methods for specific problems. So an
implementation of [Kahan summation](https://en.wikipedia.org/wiki/Kahan_summation_algorithm) would be a good candidate for inclusion, and a finite element solver would be out of scope.

## Algorithms

### Constrained STL algorithms

The library currently provides constrained versions of the
following STL algorithms.

- [accumulate](include/nrng/accumulate.hpp)
- [adjacent_difference](include/nrng/adjacent_difference.hpp)
- [iota](include/nrng/iota.hpp)
- [partial_sum](include/nrng/partial_sum.hpp)
- [reduce](include/nrng/reduce.hpp)
- [transform_reduce](include/nrng/transform_reduce.hpp)

The algorithms should generally behave very similarly to
the standard versions.

### Statistics algorithms

#### [nrng::moment](include/nrng/moment.hpp)

The n-th (raw) moment $M_n$ of a sample $S$, defined as
$$M_n = \frac{1}{|S|} \sum_{ x_i \in S } x_i^n. $$

The order of summation is arbitraty, e.g. it behaves like `reduce` and not like `accumulate`. If the sample is empty,
the moments are undefined.

Example Usage

```c++
auto const snd = nrng::moment<2>(std::array{1, 2, 3, 4, 5});
```

#### [nrng::mean](include/nrng/moment.hpp)

The mean is the 0-th raw  [moment](#nrngmoment).

```c++
auto const mean = nrng::mean<1>(std::array{3., 1., 4., 1., 5., 9.});
```

## Getting Started

The library is header only and has no dependencies, except a C++20 compatible compiler with concept and
ranges support. It can be consumed via cmake by adding it as a subdirectory, in which case the target
`nrng::nrng` will be available, or by copying the files under `include` to a place where they are found.
Installing the library is currently not supported.

### Minimal Usage Example

```tree
├── CMakeLists.txt
├── external
│   └── nrng
└── src
    └── main.cpp
```

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)

project(example LANGUAGES CXX)

add_subdirectory("external/nrng")

add_executable(example "src/main.cpp")
target_link_libraries(example PRIVATE nrng::nrng)
```

`main.cpp`:

```c++
#include <nrng/moment.hpp>

#include <array>

int main() {
  return nrng::mean(std::array{1, 2, 3, 4, 5});
}
```

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

Those are not required to use the library.

#### C++ Tools
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

```bash
mkdir build
```

### Specify the compiler using environment variables

By default, (if you don't set environment variables `CC` and `CXX`), the system default compiler will be used. If the default compiler does not
support C++20 it may be necessary to install a newer compiler and explicitly configure cmake to use it.

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

```bash
ccmake -S . -B ./build
```

Once `ccmake` has finished setting up, press 'c' to configure the project,  press 'g' to generate, and 'q' to quit.

### Build

Once you have selected all the options you would like to use, you can build the project (all targets):

```bash
cmake --build ./build
```

For Visual Studio, give the build configuration (Release, RelWithDeb, Debug, etc) like the following:

```bash
cmake --build ./build -- /p:configuration=Release
```

## Run the tests

```bash
ctest -C Release
```
