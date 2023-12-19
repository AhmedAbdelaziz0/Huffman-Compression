# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

# Project name and language
project(HuffmanCompression CXX)

# Set the source directory
set(SRCDIR src)

# Set the include directory
set(INCDIR include)

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

# Add an executable target for each binary file in the binary directory
set(BINARY ${BINDIR}/main.cpp)
get_filename_component(TARGET_NAME ${BINARY} NAME_WE)
add_executable(${TARGET_NAME} ${BINARY} ${HDRS} ${SRCS})
target_link_libraries(${TARGET_NAME})
target_include_directories(${TARGET_NAME} PUBLIC include)
