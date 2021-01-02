project(hamster_lib)

set(HEADER_FILES hamster_window.h)
set(SOURCE_FILES hamster_window.cpp)

add_library(hamster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})