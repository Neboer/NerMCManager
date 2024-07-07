#pragma once
#include "../common/json_file.h"
#include <map>

namespace NerMCManager
{
    struct BackendConfig {
        fs::path  data_dir = "./nmm_data";
        std::map<str, fs::path> java_versions = {};

        static BackendConfig parse_backend_config(fs::path config_path = "/etc/nmm/config.json");
    };
}