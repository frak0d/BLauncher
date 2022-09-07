
project('BLauncher', 'cpp', version: '2.0_alpha2',
        subproject_dir: 'libs', meson_version: '>=0.60',
        default_options: ['buildtype=release', 'strip=true',
                          'b_lto=true', 'cpp_rtti=false',
                          'warning_level=3', 'cpp_std=c++20'])

qt5 = import('qt5')
gui = qt5.compile_ui(sources: ['gui/main.ui'])

deps = [
    dependency('threads', static: get_option('static')),
    dependency('qt5', version: '>=5.15', modules: ['Core','Gui','Widgets'], static: get_option('static'))
]

dir_install = meson.current_source_dir() / 'build_output'

install_subdir('assets', strip_directory: true,
               install_dir: dir_install/'assets')

install_subdir('themes', strip_directory: true,
               install_dir: dir_install/'themes')

exe_name = 'BLauncher_v' + meson.project_version()

bl_exe = executable(
           exe_name,'src/main.cpp',
           gui, dependencies: deps,
           install: true,
           install_dir: dir_install,
           cpp_args: ['-Wno-unused-variable',
                      '-Wno-unused-parameter',
                      '-Wno-ignored-attributes'])
'''
upx    = find_program('upx')           # needed to compress the final exe
echo   = find_program('echo')          # needed as a stub for upx
pkgcfg = find_program('pkg-config')    # needed for static build on msys2

if get_option('static')
    run_target('compress', depends: bl_exe,
    command: [upx, '-9', '--lzma', dir_install/exe_name])
else
    run_target('compress',
    command: [echo, '\nERROR: UPX Compression requires a static Build (use -Dstatic=true flag)\n'])
endif
'''