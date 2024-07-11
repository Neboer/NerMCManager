project('nmmd', 'cpp', default_options: ['cpp_std=c++20'], version: '0.1.0')
nlohmann_json = dependency('nlohmann_json')
#capnproto = dependency('kj')
spdlog = dependency('spdlog')
cppzmq = dependency('cppzmq')
argparse = dependency('argparse')
executable(
    'nmmd',
    [
        'src/backend/system_test/test_mount.cpp',
        'src/backend/server/server.cpp',
        'src/backend/env_pack/ep.cpp',
        'src/backend/backend_ep.cpp',
        'src/backend/backend_dir.cpp',
        'src/backend/backend.cpp',
        'src/backend/backend_config.cpp',
        'src/backend/main.cpp',
        'src/backend/protocol/connector.cpp',
        'src/common/variables.cpp',
        'src/common/json_file.cpp',
    ],
    dependencies: [nlohmann_json, spdlog, cppzmq],
)

cli_sources = ['src/cli/sender.cpp']
cli_deps = [nlohmann_json, cppzmq, argparse]

executable(
    'nmm',
    cli_sources
    + [
        'src/cli/main.cpp',
    ],
    dependencies: cli_deps,
)

executable(
    'nmm_debug',
    cli_sources
    + [
        'src/cli/debug_client_main.cpp',
    ],
    dependencies: cli_deps,
)