project(wcrm-lib CXX)

find_package(spdlog)
find_package(nlohmann_json)


add_library(${PROJECT_NAME} 
    src/manager/article_manager_json.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options 
            project_warnings 
            utils
            spdlog::spdlog
            nlohmann_json
)

#add_subdirectory(test)