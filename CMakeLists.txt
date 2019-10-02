cmake_minimum_required(VERSION 3.1)
project(doq CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DOQ_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/doq.hpp)

add_library(doq SHARED ${DOQ_SRC})

set_target_properties(doq
        PROPERTIES
        VERSION 0.0
        SOVERSION 0
        )

# Set generated executables to be installed.  Unfortunately they must manually
# be entered...
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

install(TARGETS doq
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

set_target_properties(doq PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
