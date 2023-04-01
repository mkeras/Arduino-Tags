# Arduino-Tags
 Arduino Tag Library for abstracting a variable as a tag.


## ArduinoBasicTag
The ArduinoBasicTag class provides an easy-to-use interface for creating and managing tags for various data types in Arduino applications and to be used with the Sparkplug B protocol. The class encapsulates the functionality of reading and writing tag values, and basic detecting of changes in tag values. It is designed to be simple and extensible.

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

### Example Usage
```cpp
#include "ArduinoBasicTag.h"

int readTemperature() {
  // Read temperature from a sensor
}

bool writeLEDStatus(bool status) {
  // Set LED status
}

ArduinoBasicTag temperatureTag("Temperature", 1, readTemperature);
ArduinoBasicTag ledStatusTag("LED Status", 2, []() { return digitalRead(LED_PIN); }, writeLEDStatus);

void setup() {
  // Initialize your Arduino setup
}

void loop() {
  // Read and process tag values
  delay();
  temperatureTag.read();
  ledStatusTag.read();
  
  if (temperatureTag.valueChanged()) {
    Serial.print("Temperature: ");
    Serial.println(temperatureTag.getFloatValue());
  }

  if (ledStatusTag.valueChanged()) {
    Serial.print("LED Status: ");
    Serial.println(ledStatusTag.getBoolValue() ? "ON" : "OFF");
  }
}
```

## Methods

### Constructors
```cpp
ArduinoBasicTag(const char* name, int alias, int (*read_func)(), bool (*write_func)(int) = nullptr);
ArduinoBasicTag(const char* name, int alias, float (*read_func)(), bool (*write_func)(float) = nullptr);
ArduinoBasicTag(const char* name, int alias, bool (*read_func)(), bool (*write_func)(bool) = nullptr);
ArduinoBasicTag(const char* name, int alias, String (*read_func)(), bool (*write_func)(String) = nullptr);
```

### Getters
```cpp
const char* getName() const;
int getAlias() const;
bool isNull() const;
bool isWritable() const;
bool valueChanged();
SparkplugDataType getDataType();
int getDataTypeCode();
```

### Value Getters
```cpp
int getIntValue();
float getFloatValue();
bool getBoolValue();
String getStringValue();
```

### Read function
```cpp
bool read();
```

### Write function (optional)
```cpp
bool write(int value);
bool write(float value);
bool write(bool value);
bool write(String value);
```