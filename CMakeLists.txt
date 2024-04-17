cmake_minimum_required(VERSION 3.22)

project(GraphicsStarterCode CXX)

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --suppress=missingInclude
        --enable=all
        --inline-suppr
        --inconclusive
        -i
        ${CMAKE_SOURCE_DIR})
  else()
    message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy-13)
  if(CLANGTIDY)
    set(CMAKE_C_CLANG_TIDY ${CLANGTIDY})
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy could not be located.")
  endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------------------------
# PNG and ZLIB
#
# This macro will attempt to locate the PNG include directories, link directories and libraries. The INCLUDE_DIRECTORIES
# macro adds the resulting include directories to the search path.
# --------------------------------------------------------------------
FIND_PACKAGE(PNG REQUIRED)
if(PNG_FOUND)
  message(STATUS "PNG Version: ${PNG_VERSION_STRING}, Includes: ${PNG_INCLUDE_DIR}, Libs: ${PNG_LIBRARIES}")
  include_directories(${PNG_INCLUDE_DIR})
else(PNG_FOUND)
  message(STATUS "Could not find the PNG Libraries!")
endif(PNG_FOUND)

find_package(Boost REQUIRED COMPONENTS program_options)
if(${Boost_FOUND})
  include_directories(${Boost_INCLUDE_DIR})
  message(STATUS "Boost Libs: ${Boost_LIBRARIES}")
endif()

Include(FetchContent)

# Catch2 for Unit Testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# JSON Parser for any scene files
# FROM https://github.com/nlohmann/json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# Might need glfw if interactive OpenGL/Vulkan is required
find_package(glfw3 CONFIG REQUIRED)

# Once GLFW has been added to the project, the GLFW_LIBRARIES cache variable contains all link-time dependencies of GLFW
# as it is currently configured. To link against GLFW, link against them and the glfw target.
# include_directories(${CMAKE_SOURCE_DIR}/glfw-master/include)
set(GLFW_STATIC_LIBRARIES "${GLFW_LIBRARIES}")

include_directories(${CMAKE_SOURCE_DIR}/png++)

add_executable(render
	ArgumentParsing.cpp ArgumentParsing.h
        GraphicsArgs.cpp GraphicsArgs.h
	main.cpp)
target_link_libraries(render ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(render ${PNG_LIBRARY})
target_link_libraries(render ${ZLIB_LIBRARY})

#
# Unit Tests - by enabling testing with cmake, we can create a target that lets unit tests be run. After re-building
# yourproject with ENABLE_TESTING called, a make target, called test will be enabled. You can then type
#
# make test
#
# to perform the unit tests. See the CMakeLists.txt file in the utests directory for more details. Also, see the unit
# test .cpp files in the utests directory for examples on using Boost's unit test system.
#
enable_testing()
include(CTest)
include(Catch)

set(UTESTS
    test_png)

include_directories(${CMAKE_SOURCE_DIR})
foreach(uexec ${UTESTS})
  add_executable(${uexec} ${BUNDLEOPTS} tests/${uexec}.cpp)
  target_link_libraries(${uexec} PRIVATE ${PNG_LIBRARY})
  target_link_libraries(${uexec} PRIVATE ${ZLIB_LIBRARY})
  target_link_libraries(${uexec} PRIVATE Catch2::Catch2WithMain)

  catch_discover_tests(${uexec})
endforeach(uexec)

