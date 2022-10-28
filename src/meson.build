project('chem_db_test', 'c', 'cpp', default_options: ['c_std=c11', 'cpp_std=c++17'])

subdir('sqlite_funcs')
inc1 = include_directories('sqlite_funcs')
src = ['main.cpp']
executable('db_test', src, link_with: [sqlite], include_directories: [inc1])