add_library(
    ui
    src/ui/window/MainWindow.h
    src/ui/window/MainWindow.cpp
    src/ui/window/WindowBody.h
    src/ui/window/WindowBody.cpp
    src/ui/window/ShortcutsWindow.h
    src/ui/window/ShortcutsWindow.cpp
    src/ui/window/PreferencesWindow.h
    src/ui/window/PreferencesWindow.cpp
    src/ui/window/ItemDetailsWindow.h
    src/ui/window/ItemDetailsWindow.cpp
    src/ui/popover/SettingsPopover.h
    src/ui/popover/SettingsPopover.cpp
    src/ui/popover/SettingsMenuButton.h
    src/ui/popover/SettingsMenuButton.cpp
    src/ui/dialog/AboutDialog.h
    src/ui/dialog/AboutDialog.cpp
)

include_directories(../util/src)
target_include_directories(ui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")