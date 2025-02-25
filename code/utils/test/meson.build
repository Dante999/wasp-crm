gtest_dependency      = dependency('gtest')
gtest_main_dependency = dependency('gtest_main')


utils_lib_tests_sources = [
    'currency_test__initialization.cpp',
    'currency_test__multiplication.cpp',
]

executable('utils_lib_tests',
    utils_lib_tests_sources,
    include_directories: [utils_lib_includes],
    link_with:           [utils_lib],
    dependencies:        [gtest_dependency, gtest_main_dependency],
)