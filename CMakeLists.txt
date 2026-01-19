cmake_minimum_required(VERSION 3.19)
project(xxxApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql Network)

qt_standard_project_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/appIcon.rc")

include(cmake/ExternalLibraries.cmake)

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainform.cpp
    mainform.hpp
    mainform.ui
    rsc.qrc
    helperdatabase/helperdb.cpp helperdatabase/helperdb.hpp util/excelexporter.cpp util/excelexporter.hpp util/helper.cpp util/helper.hpp util/systemthemewatcher.cpp util/systemthemewatcher.hpp
    acercadedialog.hpp acercadedialog.cpp acercadedialog.ui
    categorydialog.cpp categorydialog.hpp categorydialog.ui
    dlgnewcategory.cpp dlgnewcategory.hpp dlgnewcategory.ui
    logindialog.cpp logindialog.hpp logindialog.ui
    resetpassworddialog.cpp resetpassworddialog.hpp resetpassworddialog.ui
    publicurldialog.cpp publicurldialog.hpp publicurldialog.ui
    swwidgets/switemdelegate.cpp swwidgets/switemdelegate.hpp swwidgets/swlabel.cpp swwidgets/swlabel.hpp swwidgets/swtablemodel.cpp swwidgets/swtablemodel.hpp
    ${APP_ICON}
    cmake/ExternalLibraries.cmake
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt::Network
        QXlsx::QXlsx
        Crypto::Crypto

)

include(GNUInstallDirs)


target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wpedantic
  -Wextra
  -Wconversion
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wno-unused-parameter

)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
  "$<TARGET_FILE_DIR:xxxApp>/tools/sqlite-tools-win-x64-3450100"
  COMMAND
  ${CMAKE_COMMAND} -E copy_directory
  "${CMAKE_CURRENT_SOURCE_DIR}/tools/sqlite-tools-win-x64-3450100"
  "$<TARGET_FILE_DIR:xxxApp>/tools/sqlite-tools-win-x64-3450100"
  COMMENT "Copiando herramientas SQLite al directorio de salida")

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
