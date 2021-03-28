add_library(
    util
    src/util/text/TextUtil.h
    src/util/text/TextUtil.cpp
    src/util/log/LogUtil.h
    src/util/log/LogUtil.cpp
    src/util/json/json.hpp
    src/util/ui/UIUtil.h
    src/util/ui/UIUtil.cpp
    src/util/item/ItemUtil.h
    src/util/item/ItemUtil.cpp
    src/util/file/FileUtil.h
    src/util/file/FileUtil.cpp
)

target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(util PUBLIC "RELEASE")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(util PUBLIC "DEBUG")
endif ()