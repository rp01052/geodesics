set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(${BINARY}_run
    ${HEADERS}
    ${SOURCES})

add_library(${BINARY}_lib STATIC
    ${HEADERS}
    ${SOURCES})

add_to_cached_list( CGAL_EXECUTABLE_TARGETS main )
# Link the executable to CGAL and third-party libraries
target_link_libraries(${BINARY}_run PUBLIC CGAL::CGAL)
