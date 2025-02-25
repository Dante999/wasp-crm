utils_lib_includes = include_directories('./include')
utils_lib_sources = [
    'src/config_file.cpp',
    'src/currency.cpp',
    'src/datetime_utils.cpp',
    'src/filesystem_utils.cpp',
    'src/string_utils.cpp'
]

utils_lib = static_library('utils_lib',
    utils_lib_sources,
    include_directories: [utils_lib_includes],
)

subdir('test')