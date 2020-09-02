CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (CodeMore)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
SET (TRANSLATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/translations)
SET (QML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qml)

# project description
SET (PROJECT_NAME "CodeMore")
SET (PROJECT_DESCRIPTION "CodeMore Application")

FILE (READ ${CMAKE_CURRENT_SOURCE_DIR}/version VERSION)
STRING (REPLACE "\n" "" VERSION ${VERSION})
STRING (REPLACE "\r" "" VERSION ${VERSION})
STRING (REPLACE "." ";" VERSION_LIST ${VERSION})
LIST (GET VERSION_LIST 0 VERSION_MAJOR)
LIST (GET VERSION_LIST 1 VERSION_MINOR)
LIST (GET VERSION_LIST 2 VERSION_PATCH)
LIST (GET VERSION_LIST 3 VERSION_BUILD)

CONFIGURE_FILE (${SRC_DIR}/CodeMore.rc.in ${CMAKE_BINARY_DIR}/CodeMore.rc)

SET (SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/BusinessLogic.cpp
        ${SRC_DIR}/TodoListSerializer.cpp
        ${SRC_DIR}/LocalizationDispatcher.cpp
    )

SET (HEADERS
        ${SRC_DIR}/BusinessLogic.h
        ${SRC_DIR}/TodoListSerializer.h
        ${SRC_DIR}/LocalizationDispatcher.h
    )

SET (QML_FILES
        ${QML_DIR}/AboutWindow.qml
        ${QML_DIR}/MainMenu.qml
        ${QML_DIR}/MainWindow.qml
        ${QML_DIR}/NewTaskDialog.qml
        ${QML_DIR}/OpenDialog.qml
        ${QML_DIR}/SaveChanges.qml
        ${QML_DIR}/SaveDialog.qml
        ${QML_DIR}/TaskList.qml
        ${QML_DIR}/TodoListModel.qml
    )

SET (TRANSLATION
        # russian
        ${TRANSLATION_DIR}/CodeMore_ru.ts
    )

SET (CMAKE_AUTOMOC ON)
SET (CMAKE_AUTORCC ON)

FIND_PACKAGE (Qt5 COMPONENTS Quick Qml Widgets Core)
QT5_ADD_RESOURCES (RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

FIND_PACKAGE (Qt5 COMPONENTS LinguistTools)
QT5_ADD_TRANSLATION(QM ${TRANSLATION})

IF (WIN32)
    SET (RESOURCES ${RESOURCES} ${CMAKE_BINARY_DIR}/CodeMore.rc)
ENDIF ()

ADD_SUBDIRECTORY (third_party)

ADD_EXECUTABLE (CodeMore ${SOURCES} ${HEADERS} ${RESOURCES} ${QM})
TARGET_LINK_LIBRARIES (CodeMore Qt5::Quick Qt5::Qml Qt5::Widgets)

ADD_CUSTOM_TARGET (
        version ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version
    )

ADD_CUSTOM_COMMAND(TARGET CodeMore
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:CodeMore>/translations
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/CodeMore_ru.qm $<TARGET_FILE_DIR:CodeMore>/translations/CodeMore_ru.qm
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CodeMore_ru.qm
    )

ADD_CUSTOM_COMMAND(TARGET CodeMore
        PRE_BUILD
        COMMAND lupdate ${QML_FILES} ${SOURCES} -ts ${CMAKE_CURRENT_SOURCE_DIR}/translations/CodeMore_ru.ts
    )

ADD_DEPENDENCIES (CodeMore version)

IF (BUILD_TESTING)
    INCLUDE (CTest)
    ADD_SUBDIRECTORY (tests)
ENDIF (BUILD_TESTING)
