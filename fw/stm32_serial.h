// Copyright 2023 mjbots Robotic Systems, LLC.  info@mjbots.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "mbed.h"
#include "serial_api_hal.h"
#include "PeripheralPins.h"

namespace moteus {

/// When constructed, this will configure the given serial port,
/// including marking the relevant pins as alternate function.
///
/// NOTE: Unlike the Mbed RawSerial class, this will use 8X
/// oversampling when necessary to achieve higher baud rates.
class Stm32Serial {
 public:
  struct Options {
    PinName tx = NC;
    PinName rx = NC;

    // Optional RS-485 DE control using the USART's hardware DE pin.
    // If 'de' is non-NC, RS-485 mode will be initialized with the
    // given polarity and assertion/deassertion delays (in bit-times).
    PinName de = NC;
    bool de_polarity_high = true;
    uint8_t rs485_assert_bits = 0;
    uint8_t rs485_deassert_bits = 6;

    int baud_rate = 115200;
  };

  Stm32Serial(const Options&);

  UARTName uart_name() const {
    return static_cast<UARTName>(reinterpret_cast<uint32_t>(uart_));
  }

  USART_TypeDef* uart() {
    return uart_;
  }

  UART_HandleTypeDef* huart() {
    return &huart_;
  }

 private:
  USART_TypeDef* uart_ = nullptr;
  UART_HandleTypeDef huart_{};
};

}
