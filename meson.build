project(
  'brainfuck',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3','c_std=c99'],
)

sources = []
subdir('src')

exe = executable(
  'brainfuck',
  sources,
  dependencies : [],
  install : true,
)
