CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (tests)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET (MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

SET (SOURCES
        ${SRC_DIR}/tests.cpp
        ${SRC_DIR}/TodoListSerializerTests.cpp
        ${MAIN_SRC_DIR}/TodoListSerializer.cpp
    )

SET (HEADERS
        ${MAIN_SRC_DIR}/TodoListSerializer.h
    )

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests gtest Qt5::Core)
TARGET_INCLUDE_DIRECTORIES (tests PRIVATE ${MAIN_SRC_DIR})
