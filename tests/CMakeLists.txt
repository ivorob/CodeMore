CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (tests)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET (MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

SET (SOURCES
        ${SRC_DIR}/tests.cpp
        ${SRC_DIR}/TodoListSerializerTests.cpp
        ${SRC_DIR}/SettingsTests.cpp
        ${MAIN_SRC_DIR}/TodoListSerializer.cpp
        ${MAIN_SRC_DIR}/TodoListTagsFactory.cpp
        ${MAIN_SRC_DIR}/Settings.cpp
    )

SET (HEADERS
        ${MAIN_SRC_DIR}/TodoListSerializer.h
        ${MAIN_SRC_DIR}/TodoListTagsFactory.h
        ${MAIN_SRC_DIR}/Settings.h
    )

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests gtest Qt5::Core)
TARGET_INCLUDE_DIRECTORIES (tests PRIVATE ${MAIN_SRC_DIR})
