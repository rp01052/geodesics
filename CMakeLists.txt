cmake_minimum_required(VERSION 3.10)

set(PROJECT geodesics)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 17)
#set( CMAKE_POSITION_INDEPENDENT_CODE ON )

#set(WORKING_DIR ${CMAKE_SOURCE_DIR})

# CGAL and its components
#find_package(CGAL QUIET COMPONENTS)
#if (NOT CGAL_FOUND)
#    message(STATUS "This project requires the CGAL library, and will not be compiled.")
#    return()
#endif()

# Boost and its components
#find_package(Boost REQUIRED)
#if (NOT Boost_FOUND)
#    message (STATUS "This project requires the Boost library, and will not be compiled." )
#    return()
#endif()

#enable_testing()

include_directories(src)
# add src CMakeLists.txt
add_subdirectory(src)

# add googletest CMakeLists.txt
add_subdirectory(googletest)

# add tests CMakeLists.txt
add_subdirectory(test)

#set(SOURCES ${WORKING_DIR}/src/main.cpp)

#add_executable( ${PROJECT} ${SOURCES} )
#add_library(${PROJECT} STATIC ${SOURCES})

#add_to_cached_list( CGAL_EXECUTABLE_TARGETS main )
# Link the executable to CGAL and third-party libraries
#target_link_libraries(${PROJECT} PRIVATE CGAL::CGAL)
