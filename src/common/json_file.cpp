#include "json_file.h"
#include <iostream>

namespace NerMCManager
{
    json parse_json_file(fs::path file_path)
    {

        std::ifstream f(file_path);
        if (!f.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + file_path.string());
    }

    json data;
    try {
        f >> data;
    } catch (const json::parse_error& e) {
        // 记录解析错误信息
        std::cerr << "JSON parse error: " << e.what() << " at byte position " << e.byte << std::endl;
        // 关闭文件
        f.close();
        // 抛出异常，传播错误
        throw std::runtime_error("Failed to parse JSON file: " + std::string(e.what()));
    } catch (const std::exception& e) {
        // 其他可能的异常处理
        std::cerr << "Error reading JSON file: " << e.what() << std::endl;
        f.close();
        throw; // 继续抛出异常
    }

    f.close();
    return data;
    }

    void write_json_file(fs::path file_path, json data)
    {
        std::ofstream o(file_path);
        o << std::setw(4) << data << std::endl;
        o.close();
    }
}