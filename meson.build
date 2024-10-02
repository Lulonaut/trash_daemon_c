project('trashd', 'c',
        version : '1.0.0',
        default_options : ['warning_level=3', 'c_std=c11'])

sources = [
'src/main.c',
'src/daemon.c'
]

trashd = executable('trashd', sources, install : true)

test('test', trashd)