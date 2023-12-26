# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

# Project name and language
project(HuffmanCompression CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK) 
  list(APPEND CMAKE_CXX_CPPCHECK "--enable=all")
  list(APPEND CMAKE_CXX_CPPCHECK "--inconclusive")
  list(APPEND CMAKE_CXX_CPPCHECK "--force") 
  list(APPEND CMAKE_CXX_CPPCHECK "--suppress=missingIncludeSystem") 
endif()

# Set the source directory
set(SRCDIR src)

# Set the include directory
set(INCDIR include)

# Set the test directory
set(TESTDIR tests)

# Set the build directory
set(BUILDDIR build)

# Set the object directory
set(OBJDIR ${BUILDDIR}/obj)

# Set the dependency directory
set(DEPDIR ${BUILDDIR}/deps)

# Set the target directory
set(TARGETDIR ${BUILDDIR}/target)

# Set the binary directory
set(BINDIR bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB_RECURSE SRCS "${SRCDIR}/*.c*")
file(GLOB_RECURSE HDRS "${INCDIR}/*.h")
file(GLOB_RECURSE TSTS "${TESTDIR}/*.c*")


# enable_testing()

include(GoogleTest)
# gtest_discover_tests(${TSTS})

# Add an executable target for each binary file in the binary directory
set(BINARY ${BINDIR}/test.cpp)
get_filename_component(TARGET_NAME ${BINARY} NAME_WE)
add_executable(${TARGET_NAME} ${BINARY} ${HDRS} ${SRCS} ${TSTS})
target_link_libraries(${TARGET_NAME} PUBLIC GTest::gtest_main)
target_include_directories(${TARGET_NAME} PUBLIC include)
