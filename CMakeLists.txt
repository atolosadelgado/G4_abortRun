    #----------------------------------------------------------------------------
    # Setup the project
    cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
    project(yourG4Application)


    #----------------------------------------------------------------------------
    # Find Geant4 package, no UI and Vis drivers activated
    #
    #find_package(Geant4 REQUIRED)

    #----------------------------------------------------------------------------
    # Find Geant4 package, with UI and Vis drivers activated
    #
    find_package(Geant4 REQUIRED ui_all vis_all)


    #----------------------------------------------------------------------------
    # Setup Geant4 include directories and compile definitions
    #
    include(${Geant4_USE_FILE})


    #----------------------------------------------------------------------------
    # Locate sources and headers for this project
    #
    include_directories(${PROJECT_SOURCE_DIR}/include
                        ${Geant4_INCLUDE_DIR})

    file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
    file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

    #----------------------------------------------------------------------------
    # Add the executables, and link it to the Geant4 libraries
    #
    add_executable(yourMainApplication yourMainApplication.cc ${sources} ${headers})
        target_link_libraries(yourMainApplication ${Geant4_LIBRARIES})

    enable_testing()
    #----------------------
    # Test SerialOnly

    SET( test_name "test_SerialOnly" )
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_BINARY_DIR}/yourMainApplication g4run.mac SerialOnly
        )

    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    SET_TESTS_PROPERTIES( ${test_name} PROPERTIES
                                       FAIL_REGULAR_EXPRESSION  " Exception; EXCEPTION;ERROR;Error"
                                       # TIMEOUT 6
                                       )

    #----------------------
    # Test MTOnly

    SET( test_name "test_MTOnly" )
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_BINARY_DIR}/yourMainApplication g4run.mac MTOnly
        )

    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    SET_TESTS_PROPERTIES( ${test_name} PROPERTIES
                                       FAIL_REGULAR_EXPRESSION  " Exception; EXCEPTION;ERROR;Error"
                                       # TIMEOUT 6
                                       )
    #----------------------
    # Test TBBOnly

    SET( test_name "test_TBBOnly" )
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_BINARY_DIR}/yourMainApplication g4run.mac TBBOnly
        )

    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    SET_TESTS_PROPERTIES( ${test_name} PROPERTIES
                                       FAIL_REGULAR_EXPRESSION  " Exception; EXCEPTION;ERROR;Error"
                                       # TIMEOUT 6
                                       )
    #----------------------
    # Test TaskingOnly

    SET( test_name "test_TaskingOnly" )
    add_test(
        NAME ${test_name}
        COMMAND ${CMAKE_BINARY_DIR}/yourMainApplication g4run.mac TaskingOnly
        )

    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    SET_TESTS_PROPERTIES( ${test_name} PROPERTIES
                                       FAIL_REGULAR_EXPRESSION  " Exception; EXCEPTION;ERROR;Error"
                                       # TIMEOUT 6
                                       )

