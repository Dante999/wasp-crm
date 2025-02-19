project(WaspCRM-tests CXX)


find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    currency_test__initialization.cpp
    currency_test__multiplication.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME}
    PRIVATE project_options
            project_warnings
            utils
            GTest::gtest
            GTest::gtest_main
)

enable_testing()
#add_test(${PROJECT_NAME} ${PROJECT_NAME})

#target_link_system_libraries(${PROJECT_NAME}
#    PRIVATE gtest
#)
