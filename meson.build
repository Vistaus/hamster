project('com.github.slawtul.hamster', 'cpp', version: '1.0.0', default_options : ['warning_level=3', 'cpp_std=c++17'])

gnome = import('gnome')
i18n = import('i18n')

add_global_arguments('-DGETTEXT_PACKAGE="@0@"'.format (meson.project_name()), language:'cpp')

subdir('src/util_lib')
subdir('src/ui_lib')

executable(
    meson.project_name(),
    'src/hamster_run.cpp',
    dependencies : [util_dep, ui_dep],
    install: false
)

i18n.merge_file(
    input: join_paths('data', 'desktop.in'),
    output: meson.project_name() + '.desktop',
    po_dir: join_paths(meson.source_root(), 'po'),
    type: 'desktop',
    install: true,
    install_dir: join_paths(get_option('datadir'), 'applications')
)

i18n.merge_file(
    input: join_paths('data', 'appdata.xml.in'),
    output: meson.project_name() + '.appdata.xml',
    po_dir: join_paths(meson.source_root(), 'po'),
    install: true,
    install_dir: join_paths(get_option('datadir'), 'metainfo')
)

subdir('po')
