# Arduino-Tags
 Arduino Tag Library for abstracting a variable as a tag.


## ArduinoBasicTag
This class provides an abstraction for handling tags in an Arduino environment. Tags are used to represent values of different data types that may be read from or written to various devices or sensors. The ArduinoBasicTag class provides a simple interface for managing and interacting with these tags.

### Features
- Supports multiple data types (int, float, bool, and String)
- Provides optional write functions for writable tags
- Keeps track of the previous tag value to identify value changes
- Handles Sparkplug data types and their codes

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