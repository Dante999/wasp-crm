project(utils CXX)

add_library(${PROJECT_NAME}
    src/currency.cpp
    src/datetime_utils.cpp
    src/string_utils.cpp
    src/config_file.cpp
    src/filesystem_utils.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE project_options
            project_warnings
)

add_subdirectory(test)
