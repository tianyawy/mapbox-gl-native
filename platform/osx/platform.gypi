{
  'targets': [
    { 'target_name': 'platform-osx',
      'product_name': 'mbgl-platform-osx',
      'type': 'static_library',
      'standalone_static_library': 1,
      'hard_dependency': 1,
      'dependencies': [
        'version',
      ],

      'sources': [
        '../darwin/log_nslog.mm',
        '../darwin/string_nsstring.mm',
        '../darwin/application_root.mm',
        '../darwin/asset_root.mm',
        '../darwin/image.mm',
      ],

      'variables': {
        'cflags_cc': [
          '<@(uv_cflags)',
          '<@(boost_cflags)',
        ],
        'libraries': [
          '<@(uv_static_libs)',
        ],
        'ldflags': [
          '-framework Foundation',
          '-framework ImageIO',
          '-framework CoreServices',
        ],
      },

      'include_dirs': [
        '../../include'
      ],

      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [ '<@(cflags_cc)' ],
        'CLANG_ENABLE_OBJC_ARC': 'YES',
      },

      'link_settings': {
        'libraries': [ '<@(libraries)' ],
        'xcode_settings': {
          'OTHER_LDFLAGS': [ '<@(ldflags)' ],
        },
      },

      'direct_dependent_settings': {
        'include_dirs': [
          '../../include',
        ],
      },
    },
  ],
}
