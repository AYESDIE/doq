project(doq_tests CXX)

set(DOQ_TESTS_SOURCES
    main.cpp
    document_test.cpp
    term_matrix_test.cpp
    term_matrix_unit_test.cpp
    vanilla_posting_test.cpp
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME} ${DOQ_TESTS_SOURCES})

# Copy test data into place.
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data/
    ${CMAKE_BINARY_DIR}/data/
    )

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})