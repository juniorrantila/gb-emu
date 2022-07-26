
cxx = meson.get_compiler('cpp')
libSDL2 = cxx.find_library('SDL2')

libGB = library('GB', [
    'Cpu.cpp',
    'Instruction.cpp',
    'Memory.cpp',
    'MemoryLocation.cpp',
    'Ppu.cpp',
    'Register.cpp',
    'Instructions/Add.cpp',
    'Instructions/Dec.cpp',
    'Instructions/Inc.cpp',
    'Instructions/Jump.cpp',
    'Instructions/Load.cpp',
    'Instructions/Logic.cpp',
    'Instructions/Sub.cpp',
  ],
  include_directories: includes,
  link_with: libGUI,
  dependencies: libSDL2)
