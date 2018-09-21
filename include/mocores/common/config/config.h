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
        std::string openConfig(const std::string &path)
        {
            std::string retVal;
            std::ifstream infile;
            infile.open(path);
            if(!infile.is_open())
            {
                BOOST_LOG_TRIVIAL(error) << "Can not open config file";
            }

            std::string s;
            while (getline(infile, s))
            {
                retVal += s;
            }
            infile.close();
        }

        void saveConfig(const std::string& path, const std::string& config)
        {
            std::string retVal;
            std::ofstream outfile;
            outfile.open(path);
            if(!outfile.is_open())
            {
                BOOST_LOG_TRIVIAL(error) << "Can not save config file";
            }

            outfile << config;
            outfile.close();
        }
    };
}

#endif