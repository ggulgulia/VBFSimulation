#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")

set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_RigidBody into a libary?" ${USE_LIBRARY})

## create a variable called "_sources" and append the source
## files that we wish to compile as the library
list(APPEND _sources VBF_RigidBody.hpp VBF_RigidBody.cpp)

if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to static library")
add_library(
    VBF_RigidBody STATIC #name of target library
    ${_sources}
    )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to shared library")
    add_library(VBF_RigidBody
               SHARED
               ${_sources}
               )

endif()
#make the library PUBLIC
target_include_directories(VBF_RigidBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(DynamicBodies)
add_subdirectory(KinematicBodies)
add_subdirectory(StaticBodies)

