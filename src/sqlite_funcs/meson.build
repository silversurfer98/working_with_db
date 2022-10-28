subdir('sqlite')

indir = include_directories('sqlite')

src = ['charOperations.h','charOperations.cpp','sqlite.h','sqlite.cpp']
sqlite = static_library('sqlite', src, link_with: sqlite, include_directories: indir)