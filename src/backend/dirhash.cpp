#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// 将二进制数据转换为十六进制字符串
std::string to_hex_string(const unsigned char* data, size_t length) {
    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    return oss.str();
}

// 更新 SHA-256 哈希
void update_hash(SHA256_CTX& ctx, const std::string& data) {
    SHA256_Update(&ctx, data.data(), data.size());
}

// 读取文件内容并更新 SHA-256 哈希
void hash_file_content(SHA256_CTX& ctx, const fs::path& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (file) {
        std::vector<char> buffer(4096);
        while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
            SHA256_Update(&ctx, buffer.data(), file.gcount());
        }
    } else {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }
}

// 递归遍历目录，按字母顺序深度优先
void hash_directory(SHA256_CTX& ctx, const fs::path& directory, const fs::path& base) {
    std::vector<fs::directory_entry> entries;

    for (const auto& entry : fs::directory_iterator(directory)) {
        entries.push_back(entry);
    }

    std::sort(entries.begin(), entries.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        return a.path().filename() < b.path().filename();
    });

    for (const auto& entry : entries) {
        if (entry.is_directory()) {
            hash_directory(ctx, entry.path(), base);
        } else if (entry.is_regular_file()) {
            auto relative_path = fs::relative(entry.path(), base).string();
            update_hash(ctx, relative_path);
            hash_file_content(ctx, entry.path());
        }
    }
}

// 计算目录的 SHA-256 哈希
std::string dirhash(const std::string& dirpath) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    fs::path directory(dirpath);
    if (fs::exists(directory) && fs::is_directory(directory)) {
        hash_directory(ctx, directory, directory);
    } else {
        throw std::runtime_error("Path is not a directory: " + dirpath);
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);

    return to_hex_string(hash, SHA256_DIGEST_LENGTH);
}
