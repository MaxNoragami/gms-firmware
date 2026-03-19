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

#ifndef MODBUS_CONTROLLER_AIR_SENSOR_STH30_HPP_
#define MODBUS_CONTROLLER_AIR_SENSOR_STH30_HPP_

#include <stdio.h>

#include "modbus_rtu_controller.hpp"

namespace gms_controller 
{

#define DEVICE_ADDRESS      2
#define DEVICE_ADDRESS_NEW  10
#define DEVICE_BAUD         2 // 4800

class Sth30
{

public:

    typedef struct SensorData_ {
        float humidity;
        float temperature;
    } SensorData;
    
    typedef struct SensorFactoryData_ {
        uint16_t device_addr;
        uint16_t baud;
    } SensorFactoryData;
    
    typedef struct SensorCorrectionData_ {
        uint16_t temp_correction;
        uint16_t hum_correction;
    } SensorCorrectionData;
    
    enum Sth30_ReadRegisterAddress {
        HUMIDITY_CONTENT_REG_ADDR               = 0x0000U,
        TEMPERATURE_CONTENT_REG_ADDR            = 0x0001U,
    };

    enum Sth30_ReadWriteRegisterAddress {
        DEVICE_ADDRESS_CONTENT_REG_ADDR         = 0x0066U,
        BAUDRATE_CONTENT_REG_ADDR               = 0x0067U,
        TEMP_CORRECTION_CONTENT_REG_ADDR        = 0x006BU,
    };

    explicit Sth30(ModbusRtuController * modbus_rtu_controller);

    ~Sth30();

    bool initialize();

    bool read_all_registers();

    bool set_device_address(const uint8_t address);

    bool set_device_baudrate(const uint8_t baud);

private:

    int sensor_address_{DEVICE_ADDRESS};
    int sensor_baud_{DEVICE_BAUD};

    ModbusRtuController * modbus_rtu_controller_;

    SensorData sensor_data_{0.0f, 0.0f};
    SensorFactoryData sensor_factory_data_{0U, 0U};
    SensorCorrectionData sensor_correction_data_{0U, 0U};
};

} // namespace gms_controller 

#endif // MODBUS_CONTROLLER_AIR_SENSOR_STH30_HPP_