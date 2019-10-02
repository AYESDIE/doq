cmake_minimum_required(VERSION 3.1)
project(doq CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(BEFORE "${CMAKE_SOURCE_DIR}/include/")

# Install the headers to the correct location.
install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/include"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        PATTERN "*~" EXCLUDE
        PATTERN "*.sw*" EXCLUDE)
install(FILES ${CMAKE_SOURCE_DIR}/src/doq.hpp
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include")

enable_testing()

add_subdirectory(tests)