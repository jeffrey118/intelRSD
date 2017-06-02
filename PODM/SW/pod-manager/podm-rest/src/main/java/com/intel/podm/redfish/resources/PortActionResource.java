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

package com.intel.podm.redfish.resources;

import com.intel.podm.business.BusinessApiException;

import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import java.util.concurrent.TimeoutException;

import static com.intel.podm.rest.error.PodmExceptions.notFound;
import static javax.ws.rs.core.MediaType.APPLICATION_JSON;

@Produces(APPLICATION_JSON)
public class PortActionResource extends BaseResource {
    @Override
    public Object get() {
        return notFound();
    }

    @Path("Port.Reset")
    public ResetActionResource reset() throws TimeoutException, BusinessApiException {
        return getResource(ResetActionResource.class);
    }
}
