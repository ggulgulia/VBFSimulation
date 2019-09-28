# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 3.2.3)
project(VBF_iwb_TUM LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Configuring ${PROJECT_NAME} project with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} Compiler")

# set a default configure type of DEBUG
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
endif()

message(STATUS "Configuring project ${project} on/for ${CMAKE_SYSTEM_NAME}")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})
add_subdirectory(vbf_source)
add_subdirectory(vbf_exe)
if(${WITH_UNIT_TESTS})
    message(STATUS "configuring project with UNIT TESTS")
    add_subdirectory(unit_tests)
else()
    message(STATUS "configuring project without unit tests")
    message(STATUS "to configure with unit test, use CLI: -DWIHT_UNIT_TESTS=ON")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake configure type for project is DEBUG")
    set(CMAKE_CXX_FLAGS "-std=c++17 -g Wall -Werror -fno-elide-constructors")
    message(STATUS "C++ Compiler flags:  ${CMAKE_CXX_FLAGS}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake configure type is RELEASE")
    set(CMAKE_CXX_FLAGS "-std=c++17 -o1 -Wall -Werror -fno-elide-constructors")
    message(STATUS "C++ Compiler flags:  ${CMAKE_CXX_FLAGS}")
endif()
    

message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message(STATUS "compiling the ${PROJECT_NAME} with CXX ${COMPILER_FLAGS}")

# append the path to UseDoxygenDoc.cmake file to the
# list of CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# include the UseDoxygenDoc from the above included path
include(UseDoxygenDoc)

# 'the command add_doxygen_doc' is defined in the 
# UseDoxygenDoc.cmake file
add_doxygen_doc(
    #the line below instructs cmake to create a
    # `_documentation` directory within build directory
    BUILD_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/_documentation  

    # the line below instructs cmake file
    # to look for doxygen configuration file
    # from the path specified
    DOXY_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in

    # the line below tells cmake to generate a 
    # target called `docs` which when executed
    # generates a doxygen file
    TARGET_NAME
    docs
    COMMENT
    "HTML documentation"
    )
