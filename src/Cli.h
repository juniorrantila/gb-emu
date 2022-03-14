#pragma once
#include <CString.h>
#include <functional>
#include <string.h>
#include <vector>

class Cli {
public:
    void on_argument(c_string argument,
                     std::function<void()> func)
    {
        m_keys.push_back(argument);
        m_values.push_back(func);
    }

    void parse(int argc, c_string argv[])
    {
        for (size_t key = 0; key<m_keys.size(); key++)
            for (int i = 0; i<argc; i++)
                if (strcmp(m_keys[key], argv[i]) == 0)
                    m_values.at(key)();
    }

private:
    std::vector<c_string> m_keys {};
    std::vector<std::function<void()>> m_values {};
};
