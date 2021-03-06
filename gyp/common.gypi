{
  'variables': {
    'install_prefix%': '',
  },
  'target_defaults': {
    'default_configuration': 'Release',
    'conditions': [
      ['OS=="mac"', {
        'xcode_settings': {
          'MACOSX_DEPLOYMENT_TARGET': '10.9',
          'CLANG_CXX_LIBRARY': 'libc++',
          'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
          'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
          'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
          'GCC_ENABLE_CPP_RTTI': 'YES',
          'OTHER_CPLUSPLUSFLAGS': [
            '-Werror',
            '-Wall',
            '-Wextra',
            '-Wshadow',
            '-Wno-variadic-macros',
            '-frtti',
            '-fexceptions',
          ],
          'GCC_WARN_PEDANTIC': 'YES',
          'GCC_WARN_UNINITIALIZED_AUTOS': 'YES_AGGRESSIVE',
        },
      }, {
        'cflags_cc': [
          '-std=c++11',
          '-Werror',
          '-Wall',
          '-Wextra',
          '-Wshadow',
          '-Wno-variadic-macros',
          '-Wno-error=unused-parameter',
          '-Wno-unknown-warning-option',
          '-frtti',
          '-fexceptions',
        ],
      }],
      ['OS=="linux"', {
        'cflags_cc': [
          '-Wno-unknown-pragmas', # We are using '#pragma mark', but it is only available on Darwin.
        ],
      }],
    ],
    'target_conditions': [
      ['_type == "static_library"', {
        'conditions': [
          ['OS=="mac"', {
            'xcode_settings': {
              'OTHER_CPLUSPLUSFLAGS': [ '-fPIC' ],
              'SKIP_INSTALL': 'YES',
            },
          }, {
            'cflags_cc': [ '-fPIC' ],
          }],
          ['host == "ios"', {
            'xcode_settings': {
              'SDKROOT': 'iphoneos',
              'SUPPORTED_PLATFORMS': 'iphonesimulator iphoneos',
              'IPHONEOS_DEPLOYMENT_TARGET': '7.0',
              'TARGETED_DEVICE_FAMILY': '1,2',
              'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
              'CODE_SIGN_IDENTITY': 'iPhone Developer',
            },
            'configurations': {
              'Release': {
                'xcode_settings': {
                  'ARCHS': [ "armv7", "armv7s", "arm64", "i386", "x86_64" ],
                },
              },
            },
          }],
        ],
      }],
    ],
    'configurations': {
      'Debug': {
        'cflags_cc': [ '-g', '-O0', '-fno-omit-frame-pointer','-fwrapv', '-fstack-protector-all', '-fno-common' ],
        'defines': [ 'DEBUG' ],
        'xcode_settings': {
          'GCC_OPTIMIZATION_LEVEL': '0',
          'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
          'DEAD_CODE_STRIPPING': 'NO',
          'GCC_INLINES_ARE_PRIVATE_EXTERN': 'NO',
          'OTHER_CPLUSPLUSFLAGS': [ '-fno-omit-frame-pointer','-fwrapv', '-fstack-protector-all', '-fno-common']
        }
      },
      'Release': {
        'cflags_cc': [ '-g', '-O3' ],
        'defines': [ 'NDEBUG' ],
        'xcode_settings': {
          'GCC_OPTIMIZATION_LEVEL': '3',
          'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
          'DEAD_CODE_STRIPPING': 'NO',
          'GCC_INLINES_ARE_PRIVATE_EXTERN': 'NO'
        }
      },
    },
  }
}
