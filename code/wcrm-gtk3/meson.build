spdlog_dependency = dependency('spdlog')
gtkmm3_dependency = dependency('gtkmm-3.0')


wcrm_gtk3_sources  = [
    'src/main.cpp',
    'src/main_window.cpp',
    'src/article_editor.cpp',
    'src/util_translate.cpp',
]


executable('wcrm_gtk3',
    wcrm_gtk3_sources,
    include_directories: [wcrm_lib_includes, utils_lib_includes],
    link_with:           [wcrm_lib, utils_lib],
    dependencies:        [spdlog_dependency, gtkmm3_dependency],
)