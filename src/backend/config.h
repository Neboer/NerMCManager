#pragma once
#include "../common/json_parser.h"
#include <map>

namespace NerMCManager
{
    struct BackendConfig {
        fs::path  data_dir;
        std::map<str, fs::path> java_versions;

        fs::path get_cached_ep_dir();
        fs::path get_wd_dir();
        fs::path get_gi_configs_dir();
        fs::path get_running_gi_dir();
        fs::path get_logs_dir();
        fs::path get_download_temp_dir();
        fs::path get_runtime_db_path();
    };

    BackendConfig parse_backend_config(fs::path config_path);
}