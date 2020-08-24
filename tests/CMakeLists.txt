CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (tests)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET (SOURCES
        ${SRC_DIR}/tests.cpp
        ${SRC_DIR}/TodoListModelSerializerTests.cpp
    )

SET (HEADERS
    )

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests gtest)