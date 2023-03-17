set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(${BINARY}_run
    ${HEADERS}
    ${SOURCES})

add_library(${BINARY}_lib STATIC
    ${HEADERS}
    ${SOURCES})
