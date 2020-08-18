CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (CodeMore)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

SET (SOURCES
        ${SRC_DIR}/main.cpp
    )

SET (HEADERS
    )

SET (CMAKE_AUTOMOC ON)
SET (CMAKE_AUTORCC ON)

FIND_PACKAGE (Qt5 COMPONENTS Quick Qml Widgets)
QT5_ADD_RESOURCES (RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

ADD_EXECUTABLE (CodeMore ${SOURCES} ${HEADERS} ${RESOURCES})
TARGET_LINK_LIBRARIES (CodeMore Qt5::Quick Qt5::Qml Qt5::Widgets)