/*!
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2015-2018 Intel Corporation
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
 * @section DESCRIPTION
*/

#include "iscsi/manager.hpp"
#include "iscsi/request.hpp"
#include "iscsi/response.hpp"
#include "net/socket_address.hpp"
#include "net/stream_socket.hpp"
#include "configuration/configuration.hpp"
#include "logger/logger_factory.hpp"



using Socket = net::StreamSocket;
using SocketAddress = net::SocketAddress;

using namespace std;
using namespace agent::storage::iscsi::tgt;

namespace {

const uint32_t MUTUAL = 1;

// Reads UNIX local TGT socket path from configuration file.
SocketAddress get_tgt_socket_address() {
    try {
        return SocketAddress(configuration::Configuration::get_instance().to_json()["tgt-socket"].as_string());
    }
    catch (const std::exception& e) {
        log_error(LOGUSR, "Error occurred while reading tgt-socket field from configuration: " << e.what());
    }
    return SocketAddress();
}

}


Response Manager::create_target(const std::int32_t target_id, const std::string& target_name) const {
    Response response;
    try {
        auto request = create_target_request(target_id, target_name);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::create_lun(const int32_t target_id, const uint64_t lun_id, const string& device_path) const {
    Response response;
    try {
        auto request = create_lun_request(target_id, lun_id, device_path);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::bind_target(const int32_t target_id, const Manager::OptionMapper& options) const {
    Response response;
    try {
        auto request = bind_target_request(target_id, options);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::unbind_target(const int32_t target_id, const Manager::OptionMapper& options) const {
    Response response;
    try {
        auto request = unbind_target_request(target_id, options);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::update_target(const int32_t target_id, const Manager::OptionMapper& options) const {
    Response response;
    try {
        auto request = update_target_request(target_id, options);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::destroy_target(const int32_t target_id) const {
    Response response;
    try {
        auto request = destroy_target_request(target_id);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}


Response Manager::show_targets() const {
    Response response;
    try {
        auto request = show_targets_request();

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());

        if (response.is_valid() && response.get_length()) {
            auto len = response.get_length();
            auto& extra_data = response.get_extra_data();
            extra_data.resize(len);

            long done = 0;
            while (len > done) {
                auto ret = socket.receive_bytes(extra_data.data() + done, len - done);
                done += ret;
            }
        }
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }

    return response;
}

Response Manager::create_chap_account(const string& username, const string& password) const {
    Response response;
    try {
        auto request = create_chap_account_request(username, password);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}

Response Manager::delete_chap_account(const string& username) const {
    Response response;
    try {
        auto request = delete_chap_account_request(username);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}

Response Manager::bind_chap_account(const int32_t target_id, const string& username, const bool mutual) const {
    Response response;
    try {
        auto request = bind_chap_account_request(target_id, username, mutual);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}

Response Manager::unbind_chap_account(const int32_t target_id, const string& username, const bool mutual) const {
    Response response;
    try {
        auto request = unbind_chap_account_request(target_id, username, mutual);

        std::lock_guard<std::mutex> lock(m_mutex);

        Socket socket(get_tgt_socket_address());
        auto bytes = request.get_request_data();
        socket.send_bytes(bytes.data(), bytes.size());
        socket.receive_bytes(response.data(), response.get_response_pod_size());
    }
    catch (const std::runtime_error& e) {
        log_error("tgt", e.what());
    }
    return response;
}

Request Manager::create_chap_account_request(const string& username, const string& password) const {
    Request request;
    request.set_operation(Operation::NEW);
    request.set_mode(Mode::ACCOUNT);
    request.set_lld("iscsi");
    request.add_extra("user=" + username + ",password=" + password);
    return request;
}

Request Manager::delete_chap_account_request(const string& username) const {
    Request request;
    request.set_operation(Operation::DELETE);
    request.set_mode(Mode::ACCOUNT);
    request.set_lld("iscsi");
    request.add_extra("user=" + username);
    return request;
}

Request Manager::bind_chap_account_request(const int32_t target_id, const string& username,
                                           const bool mutual) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::BIND);
    request.set_mode(Mode::ACCOUNT);
    if(mutual)
        request.set_ac_dir(MUTUAL);
    request.set_lld("iscsi");
    request.add_extra("user=" + username);
    return request;
}

Request Manager::unbind_chap_account_request(const int32_t target_id, const string& username,
                                             const bool mutual) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::UNBIND);
    request.set_mode(Mode::ACCOUNT);
    if(mutual)
        request.set_ac_dir(MUTUAL);
    request.set_lld("iscsi");
    request.add_extra("user=" + username);
    return request;
}

Request Manager::create_target_request(const int32_t target_id, const string& target_name) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::NEW);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    request.add_extra("targetname=" + target_name);
    return request;
}


Request Manager::create_lun_request(const int32_t target_id, const uint64_t lun_id, const string& device_path) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::NEW);
    request.set_mode(Mode::DEVICE);
    request.set_lld("iscsi");
    request.set_target_id(target_id);
    request.set_lun(lun_id);
    request.add_extra("path=" + device_path);
    return request;

}


Request Manager::destroy_target_request(const int32_t target_id) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::DELETE);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    request.set_force(1); // WARNING: Will delete an iSCSI target even when there is an active connection to it!!
    return request;
}


namespace {
void add_options(Request& request, const Manager::OptionMapper& options) {
    for (const auto& option : options) {
        request.add_extra(option.first + "=" + option.second);
    }
}
}


Request Manager::bind_target_request(const int32_t target_id, const OptionMapper& options) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::BIND);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    add_options(request, options);
    return request;
}


Request Manager::unbind_target_request(const int32_t target_id, const OptionMapper& options) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::UNBIND);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    add_options(request, options);
    return request;
}


Request Manager::update_target_request(const int32_t target_id, const OptionMapper& options) const {
    Request request;
    request.set_target_id(target_id);
    request.set_operation(Operation::UPDATE);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    add_options(request, options);
    return request;
}


Request Manager::show_targets_request() const {
    Request request;
    request.set_operation(Operation::SHOW);
    request.set_mode(Mode::TARGET);
    request.set_lld("iscsi");
    return request;
}
