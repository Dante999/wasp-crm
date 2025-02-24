cmake_minimum_required(VERSION 3.10)

project(WaspCRM)


find_package(PkgConfig)
find_package(spdlog)
pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake, 

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)


link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/main_window.cpp
    src/article_editor.cpp
    src/util_translate.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ${GTKMM_LIBRARIES}
        spdlog::spdlog
        wcrm-lib
        utils
)
