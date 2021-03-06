/*!
 * @copyright
 * Copyright (c) 2016-2018 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file utils.hpp
 *
 * @brief Netlink utilities
 * */

#pragma once
#include <string>

namespace netlink_base {
namespace utils {

std::string get_neighbor_mac_address(const std::string& port_identifier);
std::string get_port_mac_address(const std::string& port_identifier);
std::string get_port_ip_address(int ifindex, std::string& mask);

}
}

