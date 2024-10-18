project('trashd', 'c',
        version : '0.0.1',
        default_options : ['warning_level=3', 'c_std=gnu11'])

sources = [
    'src/main.c',
    'src/client.c',
    'src/daemon.c'
]

trashd = executable('trashd', sources, install : true)
