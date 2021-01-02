project(hamster_lib)

set(HEADER_FILES window.h stage.h)
set(SOURCE_FILES window.cpp stage.cpp)

add_library(hamster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})