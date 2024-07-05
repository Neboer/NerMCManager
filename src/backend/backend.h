#pragma once
#include <string>
#include "config.h"
#include "env_pack/ep_config.h"

namespace NerMCManager
{
    struct Arguments
    {
        std::string config_path;
    };

    class Backend
    {
    public:
        Backend(BackendConfig config);

        EpConfig create_environment_pack(fs::path new_ep_dir);
        EpConfig delete_environment_pack(str ep_name, str ep_version);
        EpConfig delete_environment_pack(str ep_id);
        EpConfig rename_environment_pack(str )

    private:
        fs::path data_dir;
        std::map<str, fs::path> java_versions;

        // get path of different data dirs.
        fs::path get_cached_ep_dir();
        fs::path get_wd_dir();
        fs::path get_gi_configs_dir();
        fs::path get_running_gi_dir();
        fs::path get_logs_dir();
        fs::path get_download_temp_dir();
        fs::path get_runtime_db_path();

        // work with ep

    };

}