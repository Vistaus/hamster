project(hamster_lib)

set(HEADER_FILES
        MainWindow.h
        WindowBody.h
        util/text/TextUtil.h
        util/log/LogUtil.h
        settings_popover/SettingsPopover.h
        settings_popover/SettingsMenuButton.h
        about_dialog/AboutDialog.h
        shortcuts_window/ShortcutsWindow.h
        preferences_window/PreferencesWindow.h
        item_details_window/ItemDetailsWindow.h
        )

set(SOURCE_FILES
        MainWindow.cpp
        WindowBody.cpp
        util/text/TextUtil.cpp
        util/log/LogUtil.cpp
        settings_popover/SettingsPopover.cpp
        settings_popover/SettingsMenuButton.cpp
        about_dialog/AboutDialog.cpp
        shortcuts_window/ShortcutsWindow.cpp
        preferences_window/PreferencesWindow.cpp
        item_details_window/ItemDetailsWindow.cpp
        )

add_library(hamster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(hamster_lib PUBLIC "RELEASE")
endif ()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(hamster_lib PUBLIC "DEBUG")
endif ()