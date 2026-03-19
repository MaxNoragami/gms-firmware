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
 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTW
*/

#include <PortentaEthernet.h>
#include <Ethernet.h>
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>
#include <Arduino_PortentaMachineControl.h>

namespace gms_controller 
{

class ModbusTcpController
{

public:

    union Register_u32 {
        float f32;
        uint32_t u32;
        uint16_t u16_arr[2];
    };

    ModbusTcpController(arduino::EthernetClass * ethernet);
    
    ~ModbusTcpController();

    bool initilize();

    void loop() ;

    bool write_holding_registers(float * data, uint8_t len);

private:

    void update_coils() 
    {
        for (int i = 0; i < 8; i++) {
            int coil_value = modbus_tcp_server_.coilRead(i);
            MachineControl_DigitalOutputs.write(i, coil_value ? HIGH : LOW);
        }
    }

    void update_discrete_inputs() 
    {
        uint8_t buff[8];

        buff[0] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_00);
        buff[1] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_01);
        buff[2] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_02);
        buff[3] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_03);
        buff[4] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_04);
        buff[5] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_05);
        buff[6] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_06);
        buff[7] = (uint8_t)MachineControl_DigitalInputs.read(DIN_READ_CH_PIN_07);
                
        if (!modbus_tcp_server_.writeDiscreteInputs(0, buff, 8)) {
            Serial.println("Failed to write discrete inputs");
        }
    }

    void update_holding_registers() 
    {
        for (int i = 0; i < 32; i++) {
            modbus_tcp_server_.holdingRegisterWrite(i, holding_registers_[i]);
        }
        
        // Serial.println("Failed to write discrete inputs");
    }

    arduino::EthernetClass * ethernet_;

    ModbusTCPServer modbus_tcp_server_;
    EthernetServer eth_server_; 
    EthernetClient client_;

    uint16_t holding_registers_[32]{0x00};
    
};
    
} // namespace gms_controller