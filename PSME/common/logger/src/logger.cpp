/*!
 * @brief C++ logger implementation
 *
 * @copyright Copyright (c) 2016-2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Files}
 * @file logger.cpp
 */

#include "logger/logger.hpp"
#include "logger/stream.hpp"

namespace logger_cpp {

Logger::Logger(const char* tag, const Options& options) :
    m_streams{} {
    union logger_options opt;
    opt.raw = options.m_raw;
    m_impl = logger_create(tag, &opt);
}

Logger::~Logger() {
    logger_destroy(m_impl);
}

struct logger* Logger::get_instance() const {
    return m_impl;
}

bool Logger::is_loggable(Level level) const {
    return logger_is_loggable(m_impl, static_cast<unsigned>(level));
}

void Logger::add_stream(const std::shared_ptr<Stream> stream) {
    if (nullptr == stream) {
        return;
    }

    logger_add_stream(
        m_impl,
        static_cast<struct logger_stream*>(stream->m_impl));

    m_streams.push_back(stream);
}

void Logger::add_stream(Stream* stream) {
    if (nullptr == stream) {
        return;
    }

    logger_add_stream(
        m_impl,
        static_cast<struct logger_stream*>(stream->m_impl));
}

void Logger::remove_stream(const std::shared_ptr<Stream> stream) {
    if (nullptr == stream) {
        return;
    }

    logger_remove_stream(
        m_impl,
        static_cast<struct logger_stream*>(stream->m_impl));

    m_streams.remove(stream);
}


void Logger::write(
    const char* logger_name,
    enum Level level,
    const char* file_name,
    const char* function_name,
    unsigned int line_number,
    const std::string& str) {

    _log_write(
        m_impl,
        logger_name,
        static_cast<unsigned int>(level),
        file_name, function_name, line_number,
        str.c_str()
    );
}


void Logger::set_options(const Options& options) {
    union logger_options opt;
    opt.raw = options.m_raw;
    logger_set_options(m_impl, &opt);
}


Options Logger::get_options() {
    union logger_options opt;
    logger_get_options(m_impl, &opt);
    Options options;
    options.m_raw = opt.raw;
    return options;
}

const char* logger_get_logger_name(const char* logger_name) {
    return logger_name;
}

/*!
 * @brief Get name of the requested logger
 *
 * @param logger logger shared poiter
 * @return logger_name
 */
const char* logger_get_logger_name(LoggerSPtr logger) {
    if (!logger) {
        return nullptr;
    }
    return logger_get_tag(logger->get_instance());
}

}
