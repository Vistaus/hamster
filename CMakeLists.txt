cmake_minimum_required(VERSION 3.10)
project(hamster VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

find_package(X11 REQUIRED)
link_directories(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

add_executable(hamster hamster_run.cpp)

add_subdirectory(ui)
add_subdirectory(util)

target_link_libraries(hamster ui util ${GTKMM_LIBRARIES} ${X11_LIBRARIES}  -lX11 -lXtst -lXext -pthread)

# TEST
# add_subdirectory(test)


