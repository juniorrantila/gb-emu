
subdir('GUI')
subdir('GB')

cxx = meson.get_compiler('cpp')
libSDL2 = cxx.find_library('SDL2')

executable('gb-emu', [
    'main.cpp',
  ], 
  include_directories: includes,
  link_with: [libGUI, libGB],
  dependencies: libSDL2)
