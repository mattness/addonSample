{
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', '_DEBUG' ],
        'cflags': [ '-g', '-O0', '-Wall' ],
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'cflags': [ '-O3', '-Wall' ],
      },
    }
  },

  'targets': [
    {
      'target_name': 'bindings',
      'type': '<(library)',
      'sources': [
        'src/binding.cc',
        'src/native_object_wrapper.cc',
        'src/library.cc',
      ]
    }
  ]
}