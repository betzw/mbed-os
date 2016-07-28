/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef M2M_CONNECTION_HANDLER_IMPL_MBED_STUB_H
#define M2M_CONNECTION_HANDLER_IMPL_MBED_STUB_H

#include "m2mconnectionhandler.h"

//some internal test related stuff
namespace m2mconnectionhandler_stub
{
    extern int int_value;
    extern uint16_t uint_value;
    extern bool bool_value;
    void clear();
}

#endif // M2M_CONNECTION_HANDLER_IMPL_STUB_H

