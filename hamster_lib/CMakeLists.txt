project(hamster_lib)

set(HEADER_FILES hamster.h)
set(SOURCE_FILES hamster.cpp)

add_library(hamster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})