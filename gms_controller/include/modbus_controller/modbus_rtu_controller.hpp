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

#ifndef MODBUS_CONTROLLER_MODBUS_RTU_CONTROLLER_HPP_
#define MODBUS_CONTROLLER_MODBUS_RTU_CONTROLLER_HPP_

#include <ArduinoModbus.h>
#include <ArduinoRS485.h>
#include <Arduino_PortentaMachineControl.h>

namespace gms_controller 
{

class ModbusRtuController 
{

public:

    ModbusRtuController();
    
    ~ModbusRtuController();

    bool initilize();

    bool read_single_register(int id, int type, int address);

    bool read_multiple_registers(int id, int type, int address, int nb, int16_t * data);

private:

    uint16_t buff[256]{0};

    ModbusRTUClientClass * modbus_rtu_client_;

    RS485CommClass * rs_485_port_;
};

} // namespace gms_controller

#endif // MODBUS_CONTROLLER_MODBUS_RTU_CONTROLLER_HPP_