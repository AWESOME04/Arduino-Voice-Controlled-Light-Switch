/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "command_responder.h"

#include "Arduino.h"

// Toggles the built-in LED every inference, and lights a colored LED depending
// on which word was detected.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  static bool is_initialized = false;
  if (!is_initialized) {
    pinMode(LED_BUILTIN, OUTPUT);
    // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
    pinMode(LEDG, OUTPUT);
    // At beginning, the LED is off.   
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LEDG, HIGH);
    is_initialized = true;
  }
  static int certainty = 220;

  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    // If we hear yes command, light up the LED.
    // Note: The RGB LEDs on the Arduino Nano 33 BLE
    // Sense are on when the pin is LOW, off when HIGH.
    if (found_command[0] == 'y') {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(LEDG, LOW); // yes light on 
    }
    // If we hear no command, turn off the LED.
    if (found_command[0] == 'n') {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(LEDG, HIGH); // yes light off
    }
  }
}
