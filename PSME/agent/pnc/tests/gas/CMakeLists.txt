# <license_header>
#
# Copyright (c) 2015-2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# </license_header>

if (NOT GTEST_FOUND)
    return()
endif()

add_gtest(gas psme-pnc
    test_runner.cpp
    pcie_access_interface_test.cpp
    command_test.cpp
)

add_library(pnc_objects_test
    $<TARGET_OBJECTS:pnc-gas>
)

target_link_libraries(${test_target}
    pnc_objects_test
    agent-framework
    json-cxx
    ${LOGGER_LIBRARIES}
    ${UUID_LIBRARIES}
    ${SAFESTRING_LIBRARIES}
    ${CONFIGURATION_LIBRARIES}
    ${JSONCXX_LIBRARIES}
    md5
)
