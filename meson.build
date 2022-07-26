project('gb-emu', ['cpp'],
  default_options: [
    'cpp_std=c++20',
    'cpp_eh=none',
    'cpp_rtti=false',
  ])

add_global_arguments('-Wno-c99-designator', language: 'cpp')
add_global_arguments('-Wno-c99-extensions', language: 'cpp')
add_global_arguments('-Wno-gnu-zero-variadic-macro-arguments', language: 'cpp')
add_global_arguments('-Wno-keyword-macro', language: 'cpp')
add_global_arguments('-Wno-gnu-conditional-omitted-operand', language: 'cpp')
add_global_arguments('-Wno-format-pedantic', language: 'cpp')

add_global_arguments('-fdebug-prefix-map=../=', language: 'cpp')
add_global_arguments('-ffile-prefix-map=../=', language: 'cpp')

includes = [include_directories('src')]
subdir('src')
