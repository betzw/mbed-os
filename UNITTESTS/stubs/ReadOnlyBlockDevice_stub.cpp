/* mbed Microcontroller Library
 * Copyright (c) 2017-2017 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ReadOnlyBlockDevice.h"
#include "mbed_error.h"


ReadOnlyBlockDevice::ReadOnlyBlockDevice(BlockDevice *bd)
{
    // Does nothing
}

ReadOnlyBlockDevice::~ReadOnlyBlockDevice()
{
    // Does nothing
}

int ReadOnlyBlockDevice::init()
{
    return 0;
}

int ReadOnlyBlockDevice::deinit()
{
    return 0;
}

int ReadOnlyBlockDevice::sync()
{
    return 0;
}

int ReadOnlyBlockDevice::read(void *buffer, bd_addr_t addr, bd_size_t size)
{
    return 0;
}

int ReadOnlyBlockDevice::program(const void *buffer, bd_addr_t addr, bd_size_t size)
{
    return 0;
}

int ReadOnlyBlockDevice::erase(bd_addr_t addr, bd_size_t size)
{
    return 0;
}

bd_size_t ReadOnlyBlockDevice::get_read_size() const
{
    return 0;
}

bd_size_t ReadOnlyBlockDevice::get_program_size() const
{
    return 0;
}

bd_size_t ReadOnlyBlockDevice::get_erase_size() const
{
    return 0;
}

bd_size_t ReadOnlyBlockDevice::get_erase_size(bd_addr_t addr) const
{
    return 0;
}

int ReadOnlyBlockDevice::get_erase_value() const
{
    return 0;
}

bd_size_t ReadOnlyBlockDevice::size() const
{
    return 0;
}
