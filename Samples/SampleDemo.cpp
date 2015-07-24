/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
 
#include "mbed.h"
#include "BLE.h"
#include "SampleService.h"
#include "DeviceInformationService.h"

#include "BlueNRGGap.h"

#include "Samples.h"

#ifdef SAMPLE_DEMO_ENABLED

/* Enable the following if you need to throttle the connection interval. This has
 * the effect of reducing energy consumption after a connection is made;
 * particularly for applications where the central may want a fast connection
 * interval.*/
#define UPDATE_PARAMS_FOR_LONGER_CONNECTION_INTERVAL 0
 
BLE ble;
DigitalOut led1(LED1);
InterruptIn mybutton(USER_BUTTON);
 
const static char     DEVICE_NAME[]        = "BlueNRG_Chat";
const Gap::Address_t  BLE_address_BE       = {0xAA, 0x00, 0x00, 0xE1, 0x80, 0x02};
static const uint16_t uuid16_list[]        = {SampleServiceShortUUID,
                                              GattService::UUID_DEVICE_INFORMATION_SERVICE};
static volatile bool  triggerSensorPolling = false;


void disconnectionCallback(Gap::Handle_t handle, Gap::DisconnectionReason_t reason)
{
    ble.startAdvertising(); // restart advertising
}

void buttonCallback() {
    /* Note that the buttonCallback() executes in interrupt context, 
     * so it is safer to do heavy-weight computation elsewhere. */
    triggerSensorPolling = true;
}
 
void sampleDemo(void)
{
    led1 = 0;

    const char data[20] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};

    // Attach the address of the callback function to the falling edge
    mybutton.fall(&buttonCallback);

    // Set the role
    //BlueNRGGap::getInstance().setRole(Gap::PERIPHERAL);
    
    // Set BT Address
    ble.setAddress(Gap::ADDR_TYPE_PUBLIC, BLE_address_BE);

    // Init the BLE dev
    ble.init();
    ble.onDisconnection(disconnectionCallback);
 
    /* Setup primary service. */
    SampleService sampleService(ble);
    
    /* Setup auxiliary service. */
    DeviceInformationService deviceInfo(ble, "STM", "Model1", "SN1", "hw-rev1", "fw-rev1", "soft-rev1");
 
    /* Setup advertising. */
    ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *)uuid16_list, sizeof(uuid16_list));
    ble.accumulateAdvertisingPayload(GapAdvertisingData::UNKNOWN);
    ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.setAdvertisingInterval(1000);
    ble.startAdvertising();
 
    // infinite loop
    while (1) {
        // check for trigger from buttonCallback()
        if (triggerSensorPolling && ble.getGapState().connected) {
            triggerSensorPolling = false;
 
            sampleService.writeString(data);

        } else {
            ble.waitForEvent(); // low power wait for event
        }
    }
}
 
#endif /* SAMPLE_DEMO_ENABLED */