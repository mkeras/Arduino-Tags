#include "ArduinoTag.h"

// Constructor for an ArduinoBasicTag with a String value.
// Takes a name, alias, read function pointer, and optional write function pointer.
ArduinoBasicTag::ArduinoBasicTag(const char* name, int alias, String (*read_func)(), bool (*write_func)(String))
  : m_name(name),                   // Store the tag name in m_name
    m_alias(alias),                 // Store the tag alias in m_alias
    m_is_null(true),                // Set the tag as null initially
    m_datatype(SparkplugDataType::String),   // Store the data type as String
    m_writable(write_func != nullptr),      // Check if write function pointer is not null to determine if tag is writable
    m_read_int_func(nullptr),
    m_read_double_func(nullptr),
    m_read_bool_func(nullptr),
    m_read_string_func(read_func),  // Store the read function pointer in m_read_string_func
    m_write_func_int(nullptr),
    m_write_func_double(nullptr),
    m_write_func_bool(nullptr),
    m_write_func_string(write_func) // Store the write function pointer in m_write_func_string
{
  m_string_value_prev = "";
  m_string_value = "";        // Initialize the value of the tag to an empty string
  m_datatype_code = static_cast<int>(m_datatype);     // Store the numerical value code of the datatype
  read();
}

// Constructor for an ArduinoBasicTag with an int value.
// Takes a name, alias, read function pointer, and optional write function pointer.
ArduinoBasicTag::ArduinoBasicTag(const char* name, int alias, int (*read_func)(), bool (*write_func)(int))
  : m_name(name),
    m_alias(alias),
    m_is_null(true),
    m_datatype(SparkplugDataType::Int32),
    m_writable(write_func != nullptr),
    m_read_int_func(read_func),
    m_read_double_func(nullptr),
    m_read_bool_func(nullptr),
    m_read_string_func(nullptr),
    m_write_func_int(write_func),
    m_write_func_double(nullptr),
    m_write_func_bool(nullptr),
    m_write_func_string(nullptr)
{
  m_int_value_prev = 0;
  m_int_value = 0;
  m_datatype_code = static_cast<int>(m_datatype);
  read();
}

// Constructor for an ArduinoBasicTag with a double value.
// Takes a name, alias, read function pointer, and optional write function pointer.
ArduinoBasicTag::ArduinoBasicTag(const char* name, int alias, double (*read_func)(), bool (*write_func)(double))
  : m_name(name),
    m_alias(alias),
    m_is_null(true),
    m_datatype(SparkplugDataType::Double),
    m_writable(write_func != nullptr),
    m_read_int_func(nullptr),
    m_read_double_func(read_func),
    m_read_bool_func(nullptr),
    m_read_string_func(nullptr),
    m_write_func_int(nullptr),
    m_write_func_double(write_func),
    m_write_func_bool(nullptr),
    m_write_func_string(nullptr)
{
  m_double_value_prev = 0.0f;
  m_double_value = 0.0f;
  m_datatype_code = static_cast<int>(m_datatype);
  read();
}

// Constructor for an ArduinoBasicTag with a bool value.
// Takes a name, alias, read function pointer, and optional write function pointer.
ArduinoBasicTag::ArduinoBasicTag(const char* name, int alias, bool (*read_func)(), bool (*write_func)(bool))
  : m_name(name),
    m_alias(alias),
    m_is_null(true),
    m_datatype(SparkplugDataType::Boolean),
    m_writable(write_func != nullptr),
    m_read_int_func(nullptr),
    m_read_double_func(nullptr),
    m_read_bool_func(read_func),
    m_read_string_func(nullptr),
    m_write_func_int(nullptr),
    m_write_func_double(nullptr),
    m_write_func_bool(write_func),
    m_write_func_string(nullptr)
{
  m_bool_value_prev = false;
  m_bool_value = false;
  m_datatype_code = static_cast<int>(m_datatype);
  read();
}

// Get the name of the tag
const char* ArduinoBasicTag::getName() const {
  return m_name;
}

// Get the alias of the tag
int ArduinoBasicTag::getAlias() const {
  return m_alias;
}

// Check whether the tag is null
bool ArduinoBasicTag::isNull() const {
  return m_is_null;
}

// Check if tag is writable
bool ArduinoBasicTag::isWritable() const {
  return m_writable;
}

// Check if the value of the tag has changed since the last read
bool ArduinoBasicTag::valueChanged() const {
  if (m_read_int_func) {
    return m_int_value != m_int_value_prev;
  }
  else if (m_read_double_func) {
    return m_double_value != m_double_value_prev;
  }
  else if (m_read_bool_func) {
    return m_bool_value != m_bool_value_prev;
  }
  else if (m_read_string_func) {
    return m_string_value != m_string_value_prev;
  }
  else {
    return false;
  }
}

// Get the data type of the tag
SparkplugDataType ArduinoBasicTag::getDataType() const {
  return m_datatype;
}

// Get the numerical code for the data type of the tag
int ArduinoBasicTag::getDataTypeCode() const {
  return m_datatype_code;
}


// Get the integer value of the tag
int ArduinoBasicTag::getIntValue() {
  return m_int_value;
}

// Get the double value of the tag
double ArduinoBasicTag::getDoubleValue() {
  return m_double_value;
}

// Get the boolean value of the tag
bool ArduinoBasicTag::getBoolValue() {
  return m_bool_value;
}

// Get the string value of the tag
String ArduinoBasicTag::getStringValue() {
  return m_string_value;
}


// Read the current value of the tag from the read function pointer and store it in the tag's value.
bool ArduinoBasicTag::read() {
  if (m_read_int_func) {
    m_int_value_prev = m_int_value;
    m_int_value = m_read_int_func();
  }
  else if (m_read_double_func) {
    m_double_value_prev = m_double_value;
    m_double_value = m_read_double_func();
  }
  else if (m_read_bool_func) {
    m_bool_value_prev = m_bool_value;
    m_bool_value = m_read_bool_func();
  }
  else if (m_read_string_func) {
    m_string_value_prev = m_string_value;
    m_string_value = m_read_string_func();
  }
  else {
    m_is_null = true;
    return false;
  }
  m_is_null = false;
  return true;
}


// Write an integer value to the tag (if writable)
bool ArduinoBasicTag::write(int value) {
  Serial.println("ATTEMPTING INT WRITE");
  if (m_writable) {
    return m_write_func_int(value);
  }
  return false;
}

// Write a double value to the tag (if writable)
bool ArduinoBasicTag::write(double value) {
  if (m_writable) {
    return m_write_func_double(value);
  }
  return false;
}

// Write a float value to the tag (if writable)
bool ArduinoBasicTag::write(float value) {
  return write(double(value));
}

// Write a boolean value to the tag (if writable)
bool ArduinoBasicTag::write(bool value) {
  if (m_writable) {
    return m_write_func_bool(value);
  }
  return false;
}

// Write a string value to the tag (if writable)
bool ArduinoBasicTag::write(String value) {
  if (m_writable) {
    return m_write_func_string(value);
  }
  return false;
}

// Convert to String in case of string literal
bool ArduinoBasicTag::write(const char* value) {
  String strValue(value);
  return write(strValue);
}

