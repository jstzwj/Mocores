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

        virtual void openConfig(const std::string& path) override
        {
            boost::property_tree::ptree root;
            boost::property_tree::ptree items;
            boost::property_tree::read_json<boost::property_tree::ptree>(path, root);

            host = root.get<std::string>("host");
            port = root.get<std::uint16_t>("port");

            BOOST_LOG_TRIVIAL(info) << "host : " << host;
            BOOST_LOG_TRIVIAL(info) << "port : " << port;
        }

        virtual void saveConfig(const std::string& path) override
        {
            boost::property_tree::ptree root;

            root.put("host", host);
			root.put("port", port);
            boost::property_tree::write_json(path, root);
        }
    };
}

#endif