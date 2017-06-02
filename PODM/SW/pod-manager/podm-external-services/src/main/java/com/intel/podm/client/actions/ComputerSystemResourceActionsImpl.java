/*
 * Copyright (c) 2015-2017 Intel Corporation
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

package com.intel.podm.client.actions;

import com.intel.podm.client.actions.requests.ComputerSystemUpdateRequest;
import com.intel.podm.client.api.ExternalServiceApiActionException;
import com.intel.podm.client.api.ExternalServiceApiReaderException;
import com.intel.podm.client.api.WebClient;
import com.intel.podm.client.api.actions.ComputerSystemResourceActions;
import com.intel.podm.client.api.resources.redfish.ComputerSystemResource;
import com.intel.podm.common.types.actions.ComputerSystemUpdateDefinition;

import java.net.URI;

public class ComputerSystemResourceActionsImpl implements ComputerSystemResourceActions {

    private WebClient webClient;

    public ComputerSystemResourceActionsImpl(WebClient webClient) {
        this.webClient = webClient;
    }

    @Override
    public ComputerSystemResource update(URI computerSystemUri, ComputerSystemUpdateDefinition computerSystemUpdateDefinition)
        throws ExternalServiceApiActionException, ExternalServiceApiReaderException {

        return (ComputerSystemResource) webClient.patchAndRetrieve(computerSystemUri,
            new ComputerSystemUpdateRequest(computerSystemUpdateDefinition));
    }

    @Override
    public void close() {
        webClient.close();
    }
}
