#include "config.h"

namespace NerMCManager
{
    std::map<str, fs::path> parse_java_versions(json java_version_json_conf)
    {
        std::map<str, fs::path> java_versions_map;
        for (auto& [version, path] : java_version_json_conf.items())
        {
            java_versions_map[version] = fs::path(path);
        }
        return java_versions_map;
    }

    BackendConfig parse_backend_config(std::string config_path)
    {
        json config = parse_json_file(config_path);
        BackendConfig backend_config;
        backend_config.data_dir = fs::path(config["data_dir"]);
        backend_config.java_versions = parse_java_versions(config["java_versions"]);
        return backend_config;
    }

    fs::path BackendConfig::get_cached_ep_dir() {
        return data_dir / "cached_ep";
    }

    fs::path BackendConfig::get_wd_dir() {
        return data_dir / "wd";
    }
    fs::path BackendConfig::get_gi_configs_dir() {
        return data_dir / "gi_configs";
    }
    fs::path BackendConfig::get_running_gi_dir() {
        return data_dir / "running_gi";
    }
    fs::path BackendConfig::get_logs_dir() {
        return data_dir / "logs";
    }
    fs::path BackendConfig::get_download_temp_dir() {
        return data_dir / "download_temp";
    }
    fs::path BackendConfig::get_runtime_db_path() {
        return data_dir / "runtime.db";
    }
}