#pragma once
#include <string>
#include <vector>
#include "backend_config.h"
#include "env_pack/ep.h"
#include "../common/variables.h"

namespace NerMCManager
{
    struct Arguments
    {
        fs::path config_path;
    };

    class Backend
    {
    public:
        Backend(BackendConfig config);

        EnvPack create_env_pack(fs::path new_ep_dir);
        EnvPack delete_env_pack(str ep_name, str ep_version);
        EnvPack rename_env_pack(str ep_name, str ep_version, str new_ep_name, str new_ep_version);
        std::vector<EnvPack> get_env_packs();

        Backend(const Backend &) = delete;
        Backend &operator=(const Backend &) = delete;

    private:
        BackendConfig config;

        // get path of different data dirs.
        fs::path get_wd_dir();
        fs::path get_gi_configs_dir();
        fs::path get_running_gi_dir();
        fs::path get_logs_dir();
        fs::path get_download_temp_dir();

        // work with ep
        fs::path get_cached_ep_dir();
        std::vector<str> get_env_pack_names();
    };

}