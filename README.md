# Arduino-Tags
 Arduino Tag Library for abstracting a variable as a tag.


## ArduinoBasicTag
The ArduinoBasicTag class provides an easy-to-use interface for creating and managing tags for various data types in Arduino applications, specifically to be combined with a Sparkplug B protocol library. The class encapsulates the functionality of reading and writing tag values, and basic detecting of changes in tag values. It is designed to be simple and extensible. It uses function pointers for reading and writing the tag values, allowing for virtually any type of underlying data source to be used (memory, io, etc).

### Features
- Supports multiple data types: int, double, bool, and String.
- Extensible design allows easy integration of additional data types in the future.
- Enables automatic detection of changes in tag values.
- Allows tags to be read-only or writable based on the presence of a write function.
- Utilizes function pointers for reading and writing tag values, providing flexibility and customization.
- Provides simple and intuitive getters for accessing tag metadata and values.
- Offers a simple and easy-to-understand interface for managing tags in Arduino applications using the Sparkplug B protocol.
- Designed with simplicity in mind, making it easy for developers to integrate and maintain in their projects.
- Reading, writing, getting values, and tag change detection are all performed explicitly, allowing users to control the timing and frequency of these operations as needed, per tag. This provides flexibility in adapting the class to various use cases and performance requirements.


### Getting Started
### Prerequisites
- Arduino IDE or PlatformIO IDE
- Basic understanding of C++ programming and Arduino development

### Installation
1. Download the ArduinoTag.h and ArduinoTag.cpp files.
2. Include the files in your Arduino project by adding them to your project's source directory.

### Usage
1. Include the header file
Include the ArduinoTag.h header file in your main Arduino sketch:

```cpp
#include "ArduinoTag.h"
```

2. Create read and write functions (optional) for your tags
Define read and write functions for each tag. The read function should return the value of the tag, while the write function should take a value as a parameter and return a boolean indicating success or failure.

Example read and write functions for an integer tag:
```cpp
int readIntTag() {
  return analogRead(A0);
}

bool writeIntTag(int value) {
  if (value >= 0 && value <= 255) {
    analogWrite(3, value);
    return true;
  }
  return false;
}
```

3. Create ArduinoBasicTag objects
Instantiate ArduinoBasicTag objects for each tag, passing the tag name, alias, and function pointers for reading and optionally writing the tag values.
```cpp
ArduinoBasicTag intTag("AnalogInput", 1, readIntTag, writeIntTag);
```


4. Read and write tag values
Read tag values by calling the read() method:
```cpp
intTag.read();
```
Write tag values by calling the write() method with the appropriate value:
```cpp
intTag.write(128);
```


5. Access tag metadata and values
Use the getter methods to access tag metadata and values:
```cpp
Serial.print("Tag name: ");
Serial.println(intTag.getName());

Serial.print("Tag alias: ");
Serial.println(intTag.getAlias());

Serial.print("Tag value: ");
Serial.println(intTag.getIntValue());
```


### Example
Below is a complete example of using the ArduinoBasicTag class with an integer tag:
```cpp
#include "ArduinoTag.h"

int readIntTag() {
  return analogRead(A0);
}

bool writeIntTag(int value) {
  if (value >= 0 && value <= 255) {
    analogWrite(3, value);
    return true;
  }
  return false;
}

ArduinoBasicTag intTag("AnalogInput", 1, readIntTag, writeIntTag);

void setup() {
  Serial.begin(9600);
}

void loop() {
  intTag.read();

  Serial.print("Tag name: ");
  Serial.println(intTag.getName());

  Serial.print("Tag alias: ");
  Serial.println(intTag.getAlias());

  Serial.print("Tag value: ");
  Serial.println(intTag.getIntValue());

  // Write a new value to the tag (e.g., 128)
  if (intTag.isWritable()) {
    if (intTag.write(128)) {
      Serial.println("Tag value successfully written");
    } else {
      Serial.println("Tag value write failed");
    }
  } else {
    Serial.println("Tag is not writable");
  }

  delay(1000);
}
```

This example demonstrates how to create, read, and write an integer tag using the ArduinoBasicTag class. The tag value is read from an analog input and can be written to a PWM output. The tag metadata and values are printed to the serial monitor.