spdlog_dependency        = dependency('spdlog')
nlohmann_json_dependency = dependency('nlohmann_json')

wcrm_lib_includes = include_directories('./include')
wcrm_lib_sources  = [
    'src/manager/article_manager_json.cpp',
    'src/manager/vendor_manager_json.cpp',
    'src/objects/object_comparator.cpp'
]

wcrm_lib = static_library('wcrm_lib',
    wcrm_lib_sources,
    include_directories: [wcrm_lib_includes, utils_lib_includes],
    link_with:           [utils_lib],
    dependencies:        [spdlog_dependency, nlohmann_json_dependency],
)
