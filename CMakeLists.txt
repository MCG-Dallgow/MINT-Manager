cmake_minimum_required(VERSION 3.5)

project(mint-manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        mint-manager/main.cpp
        mint-manager/constants.h
        mint-manager/util.h
        mint-manager/database.h
        mint-manager/student.cpp
        mint-manager/student.h
        mint-manager/mainwindow.cpp
        mint-manager/mainwindow.h
        mint-manager/mainwindow.ui
        mint-manager/editstudentdialog.cpp
        mint-manager/editstudentdialog.h
        mint-manager/editstudentdialog.ui
        mint-manager/manageactivitiesdialog.cpp
        mint-manager/manageactivitiesdialog.h
        mint-manager/manageactivitiesdialog.ui
        mint-manager/scientificworkdialog.cpp
        mint-manager/scientificworkdialog.h
        mint-manager/scientificworkdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mint-manager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mint-manager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(mint-manager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mint-manager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mint-manager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(mint-manager PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(mint-manager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS mint-manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mint-manager)
endif()
