project(
    'rtiaw', # project name
    'cpp', # C++ project, e.g: for C project
    version : '1.0.0',
    license : 'MIT',
    default_options : [
        'cpp_std=c++20',
        'buildtype=debugoptimized',
        'b_lto=true',
        'b_lto_threads=2',
    ],
) # compile for C++

cflags = [
    # '-flto',
    '-ffast-math',
    # '-Ofast',
    '-march=native',
    '-mtune=native',
]
add_project_arguments(cflags, language : 'cpp')


# it will be referred from subdir projects
inc = include_directories('include')

# meson will try to find a meson.build file inside following directories
subdir('include')
subdir('src')
subdir('test')
