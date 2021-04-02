icon_sizes = ['32', '48', '64', '128']

foreach i : icon_sizes
    install_data(
        join_paths('icons', i, meson.project_name() + '.svg'),
        install_dir: join_paths(get_option('datadir'), 'icons', 'hicolor', i + 'x' + i, 'apps')
    )
    install_data(
        join_paths('icons', i, meson.project_name() + '.svg'),
        install_dir: join_paths(get_option('datadir'), 'icons', 'hicolor', i + 'x' + i, '@2', 'apps')
    )
endforeach

install_data('gschema.xml', install_dir: join_paths(get_option('datadir'), 'glib-2.0', 'schemas'))
install_data('desktop', install_dir: join_paths(get_option('datadir'), 'applications') )
install_data('appdata.xml', install_dir: join_paths(get_option('datadir'), 'metainfo') )
