/**
 * @class ArduinoBasicTag
 * @brief A class representing a basic tag for use with the Sparkplug B protocol on Arduino devices.
 *
 * This class provides a convenient way to define and manage tags with different data types for
 * Sparkplug B communication. It allows for easy reading and writing of values and tracks
 * whether a value has changed since the last read.
 *
 * Member variables:
 * - m_name: The readable tag name.
 * - m_alias: The tag alias integer for use in the Sparkplug B protocol.
 * - m_is_null: Indicates whether the value is null or not.
 * - m_datatype: The Sparkplug B data type of the tag.
 * - m_datatype_code: The numerical data type code corresponding to the Sparkplug B definition.
 * - m_writable: Flag indicating if the tag is externally writable or not.
 * - m_int_value, m_double_value, m_bool_value, m_string_value: Stores for the different value types.
 * - m_int_value_prev, m_double_value_prev, m_bool_value_prev, m_string_value_prev: Stores for the previous values.
 * - m_read_int_func, m_read_double_func, m_read_bool_func, m_read_string_func: Read function pointers for different data types.
 * - m_write_func_int, m_write_func_double, m_write_func_bool, m_write_func_string: Write function pointers for different data types.
 *
 * Constructors:
 * - ArduinoBasicTag(const char* name, int alias, int (*read_func)(), bool (*write_func)(int) = nullptr)
 * - ArduinoBasicTag(const char* name, int alias, double (*read_func)(), bool (*write_func)(double) = nullptr)
 * - ArduinoBasicTag(const char* name, int alias, bool (*read_func)(), bool (*write_func)(bool) = nullptr)
 * - ArduinoBasicTag(const char* name, int alias, String (*read_func)(), bool (*write_func)(String) = nullptr)
 *
 * Getters:
 * - getName() const
 * - getAlias() const
 * - isNull() const
 * - isWritable() const
 * - valueChanged() const
 * - getDataType() const
 * - getDataTypeCode() const
 *
 * Value Getters:
 * - getIntValue()
 * - getDoubleValue()
 * - getBoolValue()
 * - getStringValue()
 *
 * Read function:
 * - read()
 *
 * Write functions:
 * - write(int value)
 * - write(double value)
 * - write(float value)
 * - write(bool value)
 * - write(String value)
 * - write(const char* value)
 */
#ifndef ARDUINO_TAG_H
#define ARDUINO_TAG_H
#include <Arduino.h>

enum class SparkplugDataType : int {
    Unknown         = 0,
    Int8            = 1,
    Int16           = 2,
    Int32           = 3,
    Int64           = 4,
    UInt8           = 5,
    UInt16          = 6,
    UInt32          = 7,
    UInt64          = 8,
    Float           = 9,
    Double          = 10,
    Boolean         = 11,
    String          = 12,
    DateTime        = 13,
    Text            = 14,
    UUID            = 15,
    DataSet         = 16,
    Bytes           = 17,
    File            = 18,
    Template        = 19,
    PropertySet     = 20,
    PropertySetList = 21
};

class ArduinoBasicTag {
public:
  // Constructors with required read functions
  ArduinoBasicTag(const char* name, int alias, int (*read_func)(), bool (*write_func)(int) = nullptr);
  ArduinoBasicTag(const char* name, int alias, double (*read_func)(), bool (*write_func)(double) = nullptr);
  ArduinoBasicTag(const char* name, int alias, bool (*read_func)(), bool (*write_func)(bool) = nullptr);
  ArduinoBasicTag(const char* name, int alias, String (*read_func)(), bool (*write_func)(String) = nullptr);
  // TODO IMPLEMENT MORE DATATYPES


  // Getters
  const char* getName() const;
  int getAlias() const;
  bool isNull() const;
  bool isWritable() const;
  bool valueChanged() const;
  SparkplugDataType getDataType() const;
  int getDataTypeCode() const;

  // Value Getters
  int getIntValue();
  double getDoubleValue();
  bool getBoolValue();
  String getStringValue();

  // Read function
  bool read();
  
  // Write function (optional)
  bool write(int value);
  bool write(double value);
  bool write(float value);   // For handling case of float (converts it to double)
  bool write(bool value);
  bool write(String value);
  bool write(const char* value);  // For handling case of string literal (converts it to String)

private:
  const char* m_name;  // readable tag name
  int m_alias;  // tag alias integer for use in sparkplug B
  bool m_is_null;  // indicates value is null
  SparkplugDataType m_datatype;  // datatype corresponding to defined types in sparkplug definition
  int m_datatype_code;  // numerical datatype code corresponding to the sparkplug definition
  bool m_writable;  // flag indicating if tag is externally writable or not (set automatically depending on whether write function is provided in constructor)

  // Value stores
  int m_int_value;
  double m_double_value;
  bool m_bool_value;
  String m_string_value;

  int m_int_value_prev;
  double m_double_value_prev;
  bool m_bool_value_prev;
  String m_string_value_prev;

  // Read functions
  int (*m_read_int_func)();
  double (*m_read_double_func)();
  bool (*m_read_bool_func)();
  String (*m_read_string_func)();

  // Write functions
  bool (*m_write_func_int)(int);
  bool (*m_write_func_double)(double);
  bool (*m_write_func_bool)(bool);
  bool (*m_write_func_string)(String);
};


#endif // ARDUINO_TAG_H