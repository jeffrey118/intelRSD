/*!
 * @brief Implementation of UDev tests.
 *
 * @header{License}
 * @copyright Copyright (c) 2017-2018 Intel Corporation
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
 * @file udev_test.cpp
 */

#include "gtest/gtest.h"

#include "tools/udev.hpp"

using namespace agent::nvme::tools;
using namespace std;

class UDevTest: public ::testing::Test {
protected:
    UDev udev{};
public:

    virtual ~UDevTest();
};

UDevTest::~UDevTest() { }

TEST_F(UDevTest, CreateUdevCtxFailed) {
    //udev_new will return NULL and cause runtime_error exception
    ASSERT_THROW(udev.get_interface_list("u", {}), runtime_error);
}

TEST_F(UDevTest, EnumerateNewFailed) {
    //udev_enumerate_new will return NULL and cause runtime_error exception
    ASSERT_THROW(udev.get_interface_list("u", {}), runtime_error);
}

TEST_F(UDevTest, EnumerateScanDevicesFailed) {
    //udev_enumerate_scan_devices will return error code and cause runtime_error exception
    ASSERT_THROW(udev.get_interface_list("u", {}), runtime_error);
}

TEST_F(UDevTest, DeviceNewFromSyspatchFailed) {
    //udev_device_new_from_syspath will return NULL and cause runtime_error exception
    ASSERT_THROW(udev.get_interface_list("u", {}), runtime_error);
}

TEST_F(UDevTest, NoPrefix) {
    vector<string> v{"eth0"};
    ASSERT_EQ(udev.get_interface_list("u", {}), v);
}

TEST_F(UDevTest, WithPrefix) {
    vector<string> v{"eth0"};
    ASSERT_EQ(udev.get_interface_list("u", "eth"), v);
}

TEST_F(UDevTest, WithPrefixButNoMatch) {
    vector<string> v{};
    // we expect empty vector as the prefix will not match eth0
    ASSERT_EQ(udev.get_interface_list("u", "ens"), v);
}

