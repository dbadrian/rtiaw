omp = dependency('openmp')
testexe = executable(
	'rtiaw',
	'main.cpp',
    'sphere.cpp',
    'material.cpp',
    include_directories : inc,
    dependencies : omp
    #link_with : foolib
)
test('foolib test', testexe)
