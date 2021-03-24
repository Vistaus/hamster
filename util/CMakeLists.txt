add_library(
    util
    src/util/text/TextUtil.h
    src/util/text/TextUtil.cpp
    src/util/log/LogUtil.h
    src/util/log/LogUtil.cpp
)

target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(util PUBLIC "RELEASE")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(util PUBLIC "DEBUG")
endif ()