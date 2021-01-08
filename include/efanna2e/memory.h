//
// Created by 付聪 on 2017/6/21.
//

#ifndef EFANNA2E_MEMORY_H
#define EFANNA2E_MEMORY_H
#include <cstring>
#include <iostream>
#include <fstream>

namespace efanna2e {

class Memory {
public:
    static Memory& ref() {
        static Memory mem;
        return mem;
    }
    void reset() {
        maxVmSize = 0;
        maxVmRSS = 0;
    }
    float getMaxVmSizeGB() {
        return maxVmSize / 1024.0 / 1024.0;
    }
    float getMaxVmRSSGB() {
        return maxVmRSS / 1024.0 / 1024.0;
    }
    void printUsage() {
        sample();
        std::cout << "Max VmSize: " << maxVmSize << " GB, "
                  << "Max VmRSS: " << maxVmRSS << " GB" << std::endl;
    }
    void sample() {
        std::ifstream in("/proc/self/status");
        if (!in) {
            std::cerr << "open file '/proc/self/status' failed" << std::endl;
            return;
        }
        auto parseValue = [](const char* p) {
            while (*p && (*p < '0' || *p > '9')) p++;
            return strtoul(p, NULL, 10);
        };
        std::string line;
        int32_t count = 0;
        while (count < 2 && std::getline(in, line)) {
            if (strncmp(line.data(), "VmSize:", 7) == 0) {
                maxVmSize = std::max(maxVmSize, parseValue(line.data()));
                ++count;
            } else if (strncmp(line.data(), "VmRSS:", 6) == 0) {
                maxVmRSS = std::max(maxVmRSS, parseValue(line.data()));
                ++count;
            }
        }
    }
private:
    Memory() = default;
    Memory(const Memory&) = delete;

private:
    uint64_t maxVmSize = 0;
    uint64_t maxVmRSS = 0;
};

}

#endif //EFANNA2E_MEMORY_H
