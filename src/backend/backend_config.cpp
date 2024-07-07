#include "backend_config.h"

namespace NerMCManager
{
    std::map<str, fs::path> parse_java_versions(json java_version_json_conf)
    {
        std::map<str, fs::path> java_versions_map;
        for (auto &[version, path] : java_version_json_conf.items())
        {
            java_versions_map[version] = fs::path(path);
        }
        return java_versions_map;
    }

    BackendConfig BackendConfig::parse_backend_config(fs::path config_path)
    {
        json config = parse_json_file(config_path);
        BackendConfig backend_config;
        backend_config.data_dir = fs::path(config["data_dir"]);
        backend_config.java_versions = parse_java_versions(config["java_versions"]);
        return backend_config;
    }
}