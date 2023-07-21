cmake_minimum_required(VERSION 3.16)

project(
    PacmanGame
    VERSION 1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)

set(MAIN_OUT_DIR "${CMAKE_BINARY_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAIN_OUT_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${MAIN_OUT_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${MAIN_OUT_DIR}/lib")

find_package(
    Qt6 6.4
    REQUIRED
    COMPONENTS
    Quick
    QuickControls2
)

qt_standard_project_setup()

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/assets/appIcon.rc")

qt_add_executable(
    ${PROJECT_NAME}
    WIN32
    ${app_icon_resource_windows}
)

set(
    ${PROJECT_NAME}_Headers
    include/pacman.hpp
    include/ghost.hpp
    include/gamecontroller.hpp
    include/gameobject.hpp
)

set(
    ${PROJECT_NAME}_Sources
    src/pacman.cpp
    src/ghost.cpp
    src/gamecontroller.cpp
    src/gameobject.cpp
)

qt_add_qml_module(
    ${PROJECT_NAME}
    URI PacmanGame
    VERSION 1.0
    SOURCES
    main.cpp
    ${${PROJECT_NAME}_Headers}
    ${${PROJECT_NAME}_Sources}
)

qt_target_qml_sources(
    ${PROJECT_NAME}
    QML_FILES
    Main.qml
    imports/Game.qml
    imports/Pacman.qml
    imports/Ghost.qml
    imports/Floor.qml
    imports/Pill.qml
    imports/Point.qml
    imports/Wall.qml
    imports/PauseOverlay.qml
)

qt_add_resources(
    ${PROJECT_NAME} "${PROJECT_NAME}Assets"
    PREFIX "/pacman"
    FILES
    assets/mazeMap.txt
    assets/objectsMap.txt
    assets/pacman_main.png
    assets/close.png
    assets/Env/Floor.png
    assets/Env/Pill.png
    assets/Env/Point.png
    assets/Env/Wall.png
    assets/Ghost/Body1.png
    assets/Ghost/Body2.png
    assets/Ghost/Body3.png
    assets/Ghost/Body4.png
    assets/Ghost/EyesDown.png
    assets/Ghost/EyesLeft.png
    assets/Ghost/EyesRight.png
    assets/Ghost/EyesUp.png
    assets/Ghost/Weak.png
    assets/Pacman/Closed.png
    assets/Pacman/Dead.png
    assets/Pacman/Open.png
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
