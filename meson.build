project('tutorial', 'cpp', default_options : ['cpp_std=c++20'])
nlohmann_json = dependency('nlohmann_json')
sqlite3 = dependency('sqlite3')
openssl = dependency('openssl')
executable('nmmd', [
    'src/backend/backend.cpp', 
    'src/common/json_parser.cpp'
    ], dependencies: [nlohmann_json, sqlite3, openssl])