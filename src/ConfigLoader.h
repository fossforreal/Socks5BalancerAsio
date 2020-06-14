/**
 * Socks5BalancerAsio : A Simple TCP Socket Balancer for balance Multi Socks5 Proxy Backend Powered by Boost.Asio
 * Copyright (C) <2020>  <Jeremie>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SOCKS5BALANCERASIO_CONFIGLOADER_H
#define SOCKS5BALANCERASIO_CONFIGLOADER_H

#ifdef MSVC
#pragma once
#endif

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include <optional>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using ConfigTimeDuration = std::chrono::milliseconds;

struct Upstream {
    std::string host;
    uint16_t port;
    std::string name;
    bool disable;
};

enum class RuleEnum {
    loop,
    random,
    one_by_one,
    change_by_time,
};

struct Config {
    std::vector<Upstream> upstream;

    std::string listenHost;
    uint16_t listenPort;

    std::string testRemoteHost;
    uint16_t testRemotePort;

    RuleEnum upstreamSelectRule;

    ConfigTimeDuration serverChangeTime;

    size_t retryTimes;

    ConfigTimeDuration connectTimeout;

    ConfigTimeDuration tcpCheckPeriod;
    ConfigTimeDuration tcpCheckStart;
    ConfigTimeDuration connectCheckPeriod;
    ConfigTimeDuration connectCheckStart;
    ConfigTimeDuration additionCheckPeriod;
};

RuleEnum string2RuleEnum(std::string s);

std::string ruleEnum2string(RuleEnum r);

class ConfigLoader : public std::enable_shared_from_this<ConfigLoader> {
public:
    Config config;

    void print();

    void
    load(const std::string &filename);

    void parse_json(const boost::property_tree::ptree &tree);
};


#endif //SOCKS5BALANCERASIO_CONFIGLOADER_H
