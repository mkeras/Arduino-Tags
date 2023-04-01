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


### Getting Started
#### Prerequisites
- Arduino IDE or PlatformIO IDE
- Basic understanding of C++ programming and Arduino development

### Installation
1. Download the ArduinoTag.h and ArduinoTag.cpp files.
2. Include the files in your Arduino project by adding them to your project's source directory.

### Usage
1. Include the header file
Include the ArduinoTag.h header file in your main Arduino sketch: