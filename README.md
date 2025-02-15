# Voxels directories

A library which locates and validates common directories used by voxels servers, clients and various tertiary programs.

# Library feature overview

## XDG base directories

voxels directories are based on [Freedesktop base directories](https://specifications.freedesktop.org/basedir-spec/latest/)

| Directory name | example library usage     |
|----------------|---------------------------|
| data home      | examples/base/data.cpp    |
| config home    | examples/base/config.cpp  |
| runtime home   | examples/base/runtime.cpp |
| state home     | examples/base/state.cpp   |

## Voxels specific directories

# Building 

Voxels directories is built using CMake. The compilation process is designed to be modular allowing you to decide 
what components are compiled into the final binary.

# Contact 

Email: <jacobevans4@proton.me>

# License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later 
version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
details.  You should have received a copy of the GNU General Public License along with this program. If not, see 
<https://www.gnu.org/licenses/>. 
