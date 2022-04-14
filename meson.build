
project('BLauncher', 'cpp', version: '2.0_alpha',
        subproject_dir: 'libs', meson_version: '>=0.60',
        default_options: ['buildtype=release', 'strip=true',
                          'b_lto=true', 'cpp_rtti=false',
                          'warning_level=3', 'cpp_std=c++20'])

qt5 = import('qt5')
gui = qt5.compile_ui(sources: ['gui/main.ui'])

deps = [
    dependency('threads', static: get_option('static')),
    dependency('boost', version: '>=1.78', static: get_option('static')),
    dependency('qt5', version: '>=5.15', modules: ['Core','Gui','Widgets'], static: get_option('static'))
]

dir_install = meson.current_source_dir() / 'build_output'

install_subdir('assets', strip_directory: true,
               install_dir: dir_install/'assets')

install_subdir('themes', strip_directory: true,
               install_dir: dir_install/'themes')

executable('BLauncher_v'+meson.project_version(),
           'src/main.cpp', gui,
           dependencies: deps,
           install: true,
           install_dir: dir_install,
           cpp_args: ['-Wno-error',
                      '-Wno-unused-variable',
                      '-Wno-unused-parameter',
                      '-Wno-ignored-attributes'])
