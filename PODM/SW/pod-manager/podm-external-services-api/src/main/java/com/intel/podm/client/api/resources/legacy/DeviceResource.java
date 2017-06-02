/*
 * Copyright (c) 2016-2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.podm.client.api.resources.legacy;

import com.intel.podm.client.api.reader.ResourceSupplier;
import com.intel.podm.client.api.resources.ExternalServiceResource;
import com.intel.podm.common.types.MediaType;
import com.intel.podm.common.types.Protocol;
import com.intel.podm.common.types.Status;

import java.math.BigDecimal;

public interface DeviceResource extends ExternalServiceResource {
    Status getStatus();
    String getBusInfo();
    Protocol getInterface();
    BigDecimal getCapacityGib();
    MediaType getType();
    Integer getRpm();
    String getManufacturer();
    String getModel();
    String getSerialNumber();
    String getFirmwareVersion();
    ResourceSupplier getAdapter();
}
