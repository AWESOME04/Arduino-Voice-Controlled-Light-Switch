# Arduino-Voice-Control-Light-Switch
This project involves deploying a program to the micro-controller. The LED light will be switched on when we say “Yes”, and switched off when we say “No”.

In fact, the word detection model is pretrained. My main work is to deploy the application to our microcontroller Arduino Nano 33 BLE Sense. This microcontroller has a microphone which can be used for audio signals input, and a built-in LED which can be used for output.
After the audio signals are processed and identified, control the switch of the LED light through the identified instructions. When the microcontroller “hears” the word “yes”, it’ll switch on the LED. Otherwise, when it “hears” the word “No”, it’ll switch off the LED.


Goals and objectives
•	Exploring machine learning applications using Arduino Nano 33 BLE Sense.
•	Exploring voice recognition in micro controllers.
•	Testing out the microphone capabilities of the Arduino Nano board and its real-world applications.
•	Debugging and making changes to in-built libraries and code.
•	Deploying the application (micro speech) to the microcontroller Arduino Nano 33 BLE Sense.



Hardware and Software Required
•	An Arduino Nano 33 BLE Sense board
•	A Micro USB cable to connect the Arduino board to your desktop machine.
•	To program the board, I used the  Arduino IDE. 
Procedure
•	I used the Arduino IDE to connect the microphone and deploy the application to the microcontroller. First, I installed the library named Arduino_TensorFlowLite-2.4.0-ALPHA-precompiled and chose the example named micro_speech. 

•	Afterwards, I only needed to change the code in arduino_command_responder.cpp to implement the desired functions.

•	In the program, the first thing to do is to include the command responder header file and the Arduino platform library’s header file. Then begin the implement of RespondToCommand.

•	I initialized the built-in LED pin's mode to OUTPUT by using a static flag, and I switched off the LED at the beginning. The next step is to check the value of argument is_new_command. If it is true, I know I’ve heard something and log it with error reporter. Then I can determine what I "heard" by checking the first character of the command. If the character is 'y', which means I heard 'yes', I switch on the LED. If the character is 'n', I switch off the LED instead.


SCHEMATICS
FLOW CHART
![image](https://user-images.githubusercontent.com/102630199/219323334-f1129914-0bff-47b0-9883-453624f55ad6.png)

CODE USED FOR ARDUINO (CHANGES MADE)
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
        digitalWrite(LEDG, LOW); // turn on LED
    }
    // If we hear no command, turn off the LED.
    if (found_command[0] == 'n') {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(LEDG, HIGH); // turn off LED
        }
    }
}

RESULTS

![image](https://user-images.githubusercontent.com/102630199/219323437-08978c40-f1d2-4727-8b8b-84b376ba01fa.png)


![image](https://user-images.githubusercontent.com/102630199/219323494-ef3b90cc-fa60-48ad-9da7-4bd666c40bf8.png)

REFERENCES

[1] TinyML: Machine Learning with TensorFlow Lite on Arduino and Ultra-Low-Power Microcontrollers by Pete Warden (Author), Daniel Situnayake (Author)
https://www.amazon.com/TinyML-Learning-TensorFlow-Ultra-Low-Power-Microcontrollers/dp/1492052043/ref=sr_1_1?keywords=tinyml&qid=1575689679&sr=8-1

[2] https://create.arduino.cc/projecthub/boys/voice-control-light-switch-f2749a?ref=part&ref_id=107215&offset=60
