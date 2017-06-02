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

package com.intel.podm.assembly.tasks;

import com.intel.podm.business.entities.redfish.EthernetInterface;
import com.intel.podm.business.services.redfish.requests.RequestedNode;
import com.intel.podm.common.enterprise.utils.beans.BeanFactory;

import javax.enterprise.context.Dependent;
import javax.inject.Inject;

@Dependent
public class VlanNodeAssemblyTaskFactory {
    @Inject
    private BeanFactory beanFactory;

    public NodeAssemblyTask createVlanCreationTask(EthernetInterface availableEthernetInterface,
                                                   RequestedNode.EthernetInterface requestedEthernetInterface) {
        VlanNodeAssemblyTask vlanNodeAssemblyTask = beanFactory.create(VlanNodeAssemblyTask.class);
        vlanNodeAssemblyTask.setRequestedInterface(requestedEthernetInterface);
        vlanNodeAssemblyTask.setAvailableInterfaceId(availableEthernetInterface.getId());

        return vlanNodeAssemblyTask;
    }
}
