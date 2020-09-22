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
        ${SRC_DIR}/TodoListTagsFactory.cpp
        ${SRC_DIR}/LocalizationDispatcher.cpp
        ${SRC_DIR}/Settings.cpp
        ${SRC_DIR}/ThemeDispatcher.cpp
    )

SET (HEADERS
        ${SRC_DIR}/BusinessLogic.h
        ${SRC_DIR}/TodoListSerializer.h
        ${SRC_DIR}/TodoListTagsFactory.h
        ${SRC_DIR}/LocalizationDispatcher.h
        ${SRC_DIR}/Settings.h
        ${SRC_DIR}/ThemeDispatcher.h
    )

FILE (GLOB QML_FILES ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.qml)
FILE (GLOB JS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/js/*.js)

SET (TRANSLATION
        ${TRANSLATION_DIR}/CodeMore_en.ts
        ${TRANSLATION_DIR}/CodeMore_ru.ts
        ${TRANSLATION_DIR}/CodeMore_es.ts
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

IF (WIN32)
    ADD_EXECUTABLE (CodeMore WIN32 ${SOURCES} ${HEADERS} ${RESOURCES} ${QM})
ELSEIF (APPLE)
    ADD_EXECUTABLE (CodeMore MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES} ${QM})
    SET_TARGET_PROPERTIES (CodeMore PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
ENDIF (WIN32)

TARGET_LINK_LIBRARIES (CodeMore Qt5::Quick Qt5::Qml Qt5::Widgets)

ADD_CUSTOM_TARGET (
        version ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version
    )

# translate
ADD_CUSTOM_COMMAND (TARGET CodeMore
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:CodeMore>/translations
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/CodeMore_en.qm $<TARGET_FILE_DIR:CodeMore>/translations/CodeMore_en.qm
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/CodeMore_ru.qm $<TARGET_FILE_DIR:CodeMore>/translations/CodeMore_ru.qm
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/CodeMore_es.qm $<TARGET_FILE_DIR:CodeMore>/translations/CodeMore_es.qm
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CodeMore_en.qm
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CodeMore_ru.qm
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CodeMore_es.qm
    )

ADD_CUSTOM_COMMAND (TARGET CodeMore
        PRE_BUILD
        COMMAND lupdate ${QML_FILES} ${SOURCES} ${JS_FILES} -ts ${CMAKE_CURRENT_SOURCE_DIR}/translations/CodeMore_en.ts
        COMMAND lupdate ${QML_FILES} ${SOURCES} ${JS_FILES} -ts ${CMAKE_CURRENT_SOURCE_DIR}/translations/CodeMore_ru.ts
        COMMAND lupdate ${QML_FILES} ${SOURCES} ${JS_FILES} -ts ${CMAKE_CURRENT_SOURCE_DIR}/translations/CodeMore_es.ts
    )

ADD_DEPENDENCIES (CodeMore version)

IF (APPLE)
ENDIF (APPLE)

IF (BUILD_TESTING)
    INCLUDE (CTest)
    ADD_SUBDIRECTORY (tests)
ENDIF (BUILD_TESTING)

# Package
SET (CPACK_PACKAGE_VERSION ${VERSION})
SET (CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET (CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET (CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

SET (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
SET (CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})

IF (WIN32)
    INSTALL (FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE DESTINATION .)
    INSTALL (DIRECTORY $<TARGET_FILE_DIR:CodeMore>/
        DESTINATION .
    )
    INCLUDE (CPack)
ENDIF (WIN32)
