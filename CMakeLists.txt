cmake_minimum_required(VERSION 3.16)

project(Dispensa VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS LinguistTools)

set(PROJECT_SOURCES
        Source/main.cpp
        Source/mainwindow.cpp
        Source/mainwindow.h
        Source/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Dispensa
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Source/about.cpp
        Source/about.h
        Source/about.ui
        Source/connessione.cpp
        Source/connessione.h
        Source/controlli.cpp
        Source/controlli.h
        Source/dati.cpp
        Source/dati.h
        Source/datiini.cpp
        Source/datiini.h
        Source/gestione.cpp
        Source/gestione.h
        Source/gestione.ui
        Source/initia.cpp
        Source/initia.h
        Source/initia.ui
        Source/listaspesa.cpp
        Source/listaspesa.h
        Source/listaspesa.ui
        Source/messaggi.cpp
        Source/messaggi.h
        Source/movimenta.cpp
        Source/movimenta.h
        Source/movimenta.ui
        Source/prodotti.cpp
        Source/prodotti.h
        Source/prodotti.ui
        Source/situazdisp.cpp
        Source/situazdisp.h
        Source/situazdisp.ui
        Source/tools.cpp
        Source/tools.h
        Source/tools.ui
        Source/toolsmod.cpp
        Source/toolsmod.h
        Source/toolsmod.ui
        Source/visualelenco.cpp
        Source/visualelenco.h
        Source/visualelenco.ui
        Source/visualizza.cpp
        Source/visualizza.h
        Source/visualizza.ui
        Resources.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Dispensa APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Dispensa SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Dispensa
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Dispensa PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Dispensa PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(Dispensa PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(Dispensa PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_translations(Dispensa
        TS_FILES
            translations/Dispensa_en.ts
            translations/Dispensa_fr.ts
            translations/Dispensa_es.ts
            translations/Dispensa_de.ts
            translations/Dispensa_el.ts
    )
    endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Dispensa)
endif()
set_target_properties(Dispensa PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Dispensa
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Dispensa)
endif()
