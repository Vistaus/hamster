add_library(
    util
    src/util/text/TextUtil.h
    src/util/text/TextUtil.cpp
    src/util/log/LogUtil.h
    src/util/log/LogUtil.cpp
)

target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")