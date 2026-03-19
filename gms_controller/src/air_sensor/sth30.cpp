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

#include "sth30.hpp"

namespace gms_controller
{

Sth30::Sth30(ModbusRtuController * modbus_rtu_controller)
: modbus_rtu_controller_(modbus_rtu_controller)
{

}

Sth30::~Sth30()
{

}

bool Sth30::initialize()
{
    return true;
}

bool Sth30::read_all_registers()
{
    int16_t data[2] = {0};

    modbus_rtu_controller_->read_multiple_registers(sensor_address_, HOLDING_REGISTERS, HUMIDITY_CONTENT_REG_ADDR, 2, data);

    sensor_data_.humidity = data[0] / 100.0f;
    sensor_data_.temperature = data[1] / 100.0f;

    Serial.print("Read all register:");
    Serial.print("\n");
    Serial.print("--------------------");
    Serial.print("\n");

    Serial.print("Humidity: ");
    Serial.print(sensor_data_.humidity);
    Serial.print("\n");
    Serial.print("Temperature: ");
    Serial.print(sensor_data_.temperature);
    Serial.print("\n");
    
    delay(100);

    modbus_rtu_controller_->read_multiple_registers(sensor_address_, HOLDING_REGISTERS, DEVICE_ADDRESS_CONTENT_REG_ADDR, 2, data);
    sensor_factory_data_.device_addr = static_cast<uint16_t>(data[0]);
    sensor_factory_data_.baud = static_cast<uint16_t>(data[1]);

    Serial.print("Device address: ");
    Serial.print(data[0]);
    Serial.print("\n");
    Serial.print("Device baud: ");
    Serial.print(data[1]);
    Serial.print("\n");
    
    delay(100);

    modbus_rtu_controller_->read_multiple_registers(sensor_address_, HOLDING_REGISTERS, TEMP_CORRECTION_CONTENT_REG_ADDR, 1, data);
    sensor_correction_data_.temp_correction = data[0];

    Serial.print("Temperature correction value: ");
    Serial.print(sensor_correction_data_.temp_correction);
    Serial.print("\n");
    
    return true;
}

bool Sth30::set_device_address(const uint8_t address)
{
    modbus_rtu_controller_->write_single_register(sensor_address_, DEVICE_ADDRESS_CONTENT_REG_ADDR, static_cast<uint16_t>(address));
    sensor_address_ = address;
    return false;
}

bool Sth30::set_device_baudrate(const uint8_t baud)
{
    modbus_rtu_controller_->write_single_register(sensor_address_, BAUDRATE_CONTENT_REG_ADDR, static_cast<uint16_t>(baud));
    
    return false;
}

}