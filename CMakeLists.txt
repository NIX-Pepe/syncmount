cmake_minimum_required(VERSION 2.6)
project(syncmount)

# pneuser begin
SET(GCC_COVERAGE_COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_definitions("-DFUSE_USE_VERSION=26")

add_executable(syncmount main.cpp wrapsyncfs.cpp)

target_link_libraries(syncmount syncfs fuse)
# pneuser end


install(TARGETS syncmount RUNTIME DESTINATION bin)
