project(hamster_lib)

set(HEADER_FILES
        MainWindow.h
        WindowBody.h
        settings_popover/SettingsPopover.h
        settings_popover/SettingsMenuButton.h
        about_dialog/AboutDialog.h
        shortcuts_window/ShortcutsWindow.h
        preferences_window/PreferencesWindow.h
        )

set(SOURCE_FILES
        MainWindow.cpp
        WindowBody.cpp
        settings_popover/SettingsPopover.cpp
        settings_popover/SettingsMenuButton.cpp
        about_dialog/AboutDialog.cpp
        shortcuts_window/ShortcutsWindow.cpp
        preferences_window/PreferencesWindow.cpp)

add_library(hamster_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
