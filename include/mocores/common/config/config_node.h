#ifndef MOCORES_COMMON_CONFIG_CONFIG_NODE_H
#define MOCORES_COMMON_CONFIG_CONFIG_NODE_H

#include <fstream>
#include <string>

#include <boost/log/trivial.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <mocores/common/config/config.h>

namespace mocores
{
    class ConfigNode : public Config
    {
    public:
        std::string host;
        std::uint16_t port;

        void parseConfig(const std::string& path)
        {
            boost::property_tree::ptree root;
            boost::property_tree::ptree items;
            boost::property_tree::read_json<boost::property_tree::ptree>(path, root);

            items = root.get_child("user");
            for (boost::property_tree::ptree::iterator it = items.begin(); it != items.end(); ++it)
            {
                std::string key = it->first; // key ID
                std::string ID = it->second.get<std::string>("ID");
                std::string Name = it->second.get<std::string>("Name");
            }
        }
    };
}

#endif