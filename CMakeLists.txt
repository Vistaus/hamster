cmake_minimum_required(VERSION 3.10)
project(hamster)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

find_package(X11 REQUIRED)
link_directories(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

# hamster program
add_executable(hamster hamster_run.cpp)
include_directories(hamster_lib)
add_subdirectory(hamster_lib)
target_link_libraries(hamster hamster_lib ${GTKMM_LIBRARIES} ${X11_LIBRARIES} -lX11 -lXtst -lXext -pthread)

# tests
# add_subdirectory(tests)
