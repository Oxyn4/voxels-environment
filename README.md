# Voxels directories

A library for a game im making, voxels, common utility functions for finding key directories, ensuring accurate 
permissions and users.

# Library feature overview

Building the directories relies on the 'BUILD_EXAMPLES' cmake variable being defined.

## XDG base directories

voxels directories are based on [Freedesktop base directories](https://specifications.freedesktop.org/basedir-spec/latest/)

| Directory name | example library usage     |
|----------------|---------------------------|
| data home      | examples/base/data.cpp    |
| config home    | examples/base/config.cpp  |
| runtime home   | examples/base/runtime.cpp |
| state home     | examples/base/state.cpp   |

## Voxels specific directories

| Directory name    | example library usage            |
|-------------------|----------------------------------|
| mods home         | examples/voxels/mods.cpp         |
| mods logs home    | examples/voxels/mods_logs.cpp    |
| logs home         | examples/voxels/logs.cpp         |
| mods runtime home | examples/voxels/mods_runtime.cpp |

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
