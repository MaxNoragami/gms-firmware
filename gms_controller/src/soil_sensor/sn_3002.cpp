/*
 * MIT License
 * 
 * Copyright (c) 2026 Potlog Radu
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "sn_3002.hpp"

namespace gms_controller
{

Sn3002::Sn3002(ModbusRtuController * modbus_rtu_controller)
: modbus_rtu_controller_(modbus_rtu_controller)
{

}

Sn3002::~Sn3002()
{

}

bool Sn3002::initialize()
{
    return true;
}

bool Sn3002::read_all_registers()
{
    modbus_rtu_controller_->read_multiple_registers(sensor_address_, HOLDING_REGISTERS, 0x0000, 8);

    return false;
}

}