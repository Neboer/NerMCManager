#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mount.h>

using str = std::string;

bool has_mount_permission(const char *test_dir)
{
    // Create a temporary directory for mounting test
    str temp_dir = str(test_dir) + "/temp_mount";
    if (mkdir(temp_dir.c_str(), 0700) != 0)
    {
        std::perror("mkdir");
        return false;
    }

    // Try to mount tmpfs to the temporary directory
    if (mount("tmpfs", temp_dir.c_str(), "tmpfs", 0, nullptr) != 0)
    {
        std::perror("mount");
        rmdir(temp_dir.c_str());
        return false;
    }

    // Unmount the temporary directory
    if (umount(temp_dir.c_str()) != 0)
    {
        std::perror("umount");
        return false;
    }

    // Remove the temporary directory
    if (rmdir(temp_dir.c_str()) != 0)
    {
        std::perror("rmdir");
        return false;
    }

    return true;
}
