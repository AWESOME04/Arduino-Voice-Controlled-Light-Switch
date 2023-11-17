# Arduino Voice-Controlled Light Switch

![Voice-Controlled Light Switch](https://user-images.githubusercontent.com/102630199/228667881-ada43a93-2506-4cf5-9266-859e415d4cc6.jpg)

## Project Overview

This project utilizes the Arduino Nano 33 BLE Sense microcontroller to create a voice-controlled light switch. The built-in microphone captures audio signals, and a pretrained word detection model identifies the words "Yes" and "No." The LED light is switched on when "Yes" is detected and off when "No" is heard.

## Goals and Objectives

- Explore machine learning applications using Arduino Nano 33 BLE Sense.
- Implement voice recognition on microcontrollers.
- Test the microphone capabilities of the Arduino Nano board for real-world applications.
- Debug and modify in-built libraries and code.
- Deploy the Micro Speech application to the Arduino Nano 33 BLE Sense.

## Hardware and Software Required

- Arduino Nano 33 BLE Sense board
- Micro USB cable for connecting the Arduino board to a desktop machine.
- Arduino IDE for programming the board.

## Procedure

1. Use the Arduino IDE to connect the microphone and deploy the Micro Speech application to the microcontroller.
2. Install the Arduino_TensorFlowLite-2.4.0-ALPHA-precompiled library and select the micro_speech example.
3. Modify the code in arduino_command_responder.cpp to implement the desired functions.

### Code Modification Example

```cpp
// ... (Previous code)

void RespondToCommand(tflite::ErrorReporter* error_reporter,
    int32_t current_time, const char* found_command,
    uint8_t score, bool is_new_command) {
    static bool is_initialized = false;
    if (!is_initialized) {
        pinMode(LED_BUILTIN, OUTPUT);
        pinMode(LEDG, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(LEDG, HIGH);
        is_initialized = true;
    }
    static int certainty = 220;
    if (is_new_command) {
        error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
            current_time);

        if (found_command[0] == 'y') {
            digitalWrite(LED_BUILTIN, HIGH);
            digitalWrite(LEDG, LOW); // turn on LED
        }

        if (found_command[0] == 'n') {
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(LEDG, HIGH); // turn off LED
        }
    }
}

// ... (Remaining code)
```

## Schematics and Flow Chart

### Schematics

![Schematics](https://user-images.githubusercontent.com/102630199/219323334-f1129914-0bff-47b0-9883-453624f55ad6.png)

### Flow Chart

![Flow Chart](https://user-images.githubusercontent.com/102630199/219323494-ef3b90cc-fa60-48ad-9da7-4bd666c40bf8.png)

## Results

![Results](https://user-images.githubusercontent.com/102630199/219323437-08978c40-f1d2-4727-8b8b-84b376ba01fa.png)

## References

1. [TinyML: Machine Learning with TensorFlow Lite on Arduino and Ultra-Low-Power Microcontrollers](https://www.amazon.com/TinyML-Learning-TensorFlow-Ultra-Low-Power-Microcontrollers/dp/1492052043/ref=sr_1_1?keywords=tinyml&qid=1575689679&sr=8-1) by Pete Warden and Daniel Situnayake.

2. [Voice-Controlled Light Switch Project](https://create.arduino.cc/projecthub/boys/voice-control-light-switch-f2749a?ref=part&ref_id=107215&offset=60) on Arduino Project Hub.

Feel free to reach out for any additional information or assistance!
