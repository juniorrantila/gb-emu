
cxx = meson.get_compiler('cpp')
libSDL2 = cxx.find_library('SDL2')

libGUI = library('GUI', [
    'Canvas.cpp',
    'SDLWrapper.cpp'
  ],
  include_directories: includes,
  dependencies: libSDL2)
