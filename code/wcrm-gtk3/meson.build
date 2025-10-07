spdlog_dependency = dependency('spdlog')
gtkmm3_dependency = dependency('gtkmm-3.0', include_type: 'system')
gdkmm3_dependency = dependency('gdkmm-3.0', include_type: 'system')


wcrm_gtk3_sources  = [
    'src/main.cpp',
    'src/main_window.cpp',
    'src/article_editor.cpp',
    'src/customer_editor.cpp',
    'src/vendor_editor.cpp',
    'src/util_translate.cpp',
]


#add_project_arguments('wcrm_gtk3', compiler_warnings, language : 'cpp')

executable('wcrm_gtk3',
    wcrm_gtk3_sources,
    include_directories: [wcrm_lib_includes, utils_lib_includes],
    link_with:           [wcrm_lib, utils_lib],
    dependencies:        [spdlog_dependency, gtkmm3_dependency, gdkmm3_dependency]
)


