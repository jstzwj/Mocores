#ifndef MOCORES_COMMON_CONFIG_CONFIG_H
#define MOCORES_COMMON_CONFIG_CONFIG_H

#include <string>
#include <fstream>

#include <boost/log/trivial.hpp>

namespace mocores
{
    class Config
    {
    public:
        virtual void openConfig(const std::string &path) = 0;

        virtual void saveConfig(const std::string& path) = 0;
    };
}

#endif