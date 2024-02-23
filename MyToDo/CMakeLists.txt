cmake_minimum_required(VERSION 3.20)

project(MyToDo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMyToDo
    main.cpp
)

qt_add_qml_module(appMyToDo
    URI MyToDo
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    include/task.h src/task.cpp
    include/taskmanager.h src/taskmanager.cpp
    include/db_manager.h src/db_manager.cpp
    include/filter_manager.h src/filter_manager.cpp
    QML_FILES
    qml/EditDialog.qml
    qml/Filtering.qml
    qml/DatePicker.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMyToDo PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMyToDo
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMyToDo
    PRIVATE Qt6::Quick
    Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appMyToDo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
