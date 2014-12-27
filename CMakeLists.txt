cmake_minimum_required(VERSION 2.8.11)

###
# Settings
#
set(PROJECT_NAME "SMF" CACHE STRING "Project Name")
set(PROJECT_NAME_TITLE ${PROJECT_NAME})
set(PROJECT_DOMAIN "https://github.com/imron02/SMF" CACHE STRING "Internet domain name for ${PROJECT_NAME}")
set(PROJECT_COMPANYNAME "Imron Rosdiana" CACHE STRING "Company name for ${PROJECT_NAME}")
set(PROJECT_COPYRIGHT "Copyright (C) 2013 ${PROJECT_COMPANYNAME} All Rights Reserved.")
set(PROJECT_GITHUB_FORK "https://github.com/imron02/SMF" CACHE STRING "Git fork of ${PROJECT_NAME}")

###
# Configure project
PROJECT(${PROJECT_NAME})

###
# Options
IF(WIN32)
    OPTION(MANIFEST_ENABLE "Enable Manifest" ON)
ENDIF(WIN32)

###
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

IF(BUILD_64X)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /machine:x64")
	SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /machine:x64")
	SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /machine:x64")
else()
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /machine:x86")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /machine:x86")
    SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /machine:x86")
ENDIF()

###
# Widgets finds its own dependencies (QtGui and QtCore).
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.3.2\\5.3\\msvc2013\\")
find_package(Qt5Widgets REQUIRED)

###
# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

###
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

###
# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

###
# Executables fail to build with Qt 5 in the default configuration
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

###
# GUI
QT5_WRAP_UI(UIS_HDRS
    mainwindow.ui
)

###
# Qt resource
QT5_ADD_RESOURCES(SMF_RESOURCES_RCC resource.qrc)

###
# Tell CMake to create the helloworld executable
add_executable(SMF WIN32 main.cpp mainwindow.cpp ${UIS_HDRS} ${SMF_RESOURCES_RCC} app.rc)

###
# UAC Administrator Required
SET_TARGET_PROPERTIES(SMF PROPERTIES LINK_FLAGS "/level='requireAdministrator' /uiAccess='false'")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# Use the Widgets module from Qt 5.
target_link_libraries(SMF Qt5::Widgets)