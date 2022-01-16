project('BLauncher', 'cpp', version: '2.0',
        subproject_dir: 'libs', meson_version: '>=0.60',
        default_options: ['buildtype=release', 'strip=true',
                          'b_lto=true', 'b_lto_mode=thin',
                          'warning_level=3', 'cpp_std=c++20'])

qt5 = import('qt5')
gui = qt5.compile_ui(sources: ['gui/main.ui'])

deps = [
    dependency('threads'),
    dependency('qt5', modules: ['Core','Gui','Widgets'])
]

dir_base = meson.current_source_dir()
dir_install = join_paths(dir_base, 'build')

dir_install_assets = join_paths(dir_install, 'assets')
dir_install_themes = join_paths(dir_install, 'themes')

install_subdir('assets', strip_directory: true,
               install_dir: dir_install_assets)

install_subdir('themes', strip_directory: true,
               install_dir: dir_install_themes)

executable('BLauncher', 'src/main.cpp', gui,
           dependencies: deps,
           install: true,
           install_dir: dir_install,
           override_options: [])