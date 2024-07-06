#include "backend.h"

namespace NerMCManager
{
    fs::path Backend::get_cached_ep_dir()
    {
        return config.data_dir / "cached_ep";
    }

    fs::path Backend::get_wd_dir()
    {
        return config.data_dir / "wd";
    }
    fs::path Backend::get_gi_configs_dir()
    {
        return config.data_dir / "gi_configs";
    }
    fs::path Backend::get_running_gi_dir()
    {
        return config.data_dir / "running_gi";
    }
    fs::path Backend::get_logs_dir()
    {
        return config.data_dir / "logs";
    }
    fs::path Backend::get_download_temp_dir()
    {
        return config.data_dir / "download_temp";
    }
    fs::path Backend::get_runtime_db_path()
    {
        return config.data_dir / "runtime.db";
    }
}