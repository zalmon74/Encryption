#ifndef MY_STD_TYPEDEF_HPP
#define MY_STD_TYPEDEF_HPP

/*
 * Данный файл содержит псевдонимы стандартных типов данных для удобства использования
*/

#include <stdint.h>
#include <limits>

#define NUM_DIVISION_SYMBOLS 100 // Значение, которое разделяет индексы между строчными и прописными символами

#define UNDEFINED_VALUE_INT8_T   0x7F
#define UNDEFINED_VALUE_UINT8_T  0xFF
#define UNDEFINED_VALUE_INT16_T  0x7FFF
#define UNDEFINED_VALUE_UINT16_T 0xFFFF
#define UNDEFINED_VALUE_INT32_T  0x7FFFFFFF
#define UNDEFINED_VALUE_UINT32_T 0xFFFFFFFF
#define UNDEFINED_VALUE_INT64_T  0x7FFFFFFFFFFFFFFF
#define UNDEFINED_VALUE_UINT64_T 0xFFFFFFFFFFFFFFFF
#define UNDEFINED_VALUE_SIZE_T   std::numeric_limits<size_t>::max()

typedef       bool* pBool;
typedef       bool& rBool;
typedef const bool  cBool;
typedef const bool* cpBool;
typedef bool const* pcBool;
typedef const bool* const cpcBool;
typedef const bool& crBool;
typedef bool const& rcBool;

typedef       int8_t* pInt8_t;
typedef       int8_t& rInt8_t;
typedef const int8_t  cInt8_t;
typedef const int8_t* cpInt8_t;
typedef int8_t const* pcInt8_t;
typedef const int8_t* const cpcInt8_t;
typedef const int8_t& crInt8_t;
typedef int8_t const& rcInt8_t;

typedef       uint8_t* pUInt8_t;
typedef       uint8_t& rUInt8_t;
typedef const uint8_t  cUInt8_t;
typedef const uint8_t* cpUInt8_t;
typedef uint8_t const* pcUInt8_t;
typedef const uint8_t* const cpcUInt8_t;
typedef const uint8_t& crUInt8_t;
typedef uint8_t const& rcUInt8_t;

typedef       int16_t* pInt16_t;
typedef       int16_t& rInt16_t;
typedef const int16_t  cInt16_t;
typedef const int16_t* cpInt16_t;
typedef int16_t const* pcInt16_t;
typedef const int16_t* const cpcInt16_t;
typedef const int16_t& crInt16_t;
typedef int16_t const& rcInt16_t;

typedef       uint16_t* pUInt16_t;
typedef       uint16_t& rUInt16_t;
typedef const uint16_t  cUInt16_t;
typedef const uint16_t* cpUInt16_t;
typedef uint16_t const* pcUInt16_t;
typedef const uint16_t* const cpcUInt16_t;
typedef const uint16_t& crUInt16_t;
typedef uint16_t const& rcUInt16_t;

typedef       int32_t* pInt32_t;
typedef       int32_t& rInt32_t;
typedef const int32_t  cInt32_t;
typedef const int32_t* cpInt32_t;
typedef int32_t const* pcInt32_t;
typedef const int32_t* const cpcInt32_t;
typedef const int32_t& crInt32_t;
typedef int32_t const& rcInt32_t;

typedef       uint32_t* pUInt32_t;
typedef       uint32_t& rUInt32_t;
typedef const uint32_t  cUInt32_t;
typedef const uint32_t* cpUInt32_t;
typedef uint32_t const* pcUInt32_t;
typedef const uint32_t* const cpcUInt32_t;
typedef const uint32_t& crUInt32_t;
typedef uint32_t const& rcUInt32_t;

typedef       int64_t* pInt64_t;
typedef       int64_t& rInt64_t;
typedef const int64_t  cInt64_t;
typedef const int64_t* cpInt64_t;
typedef int64_t const* pcInt64_t;
typedef const int64_t* const cpcInt64_t;
typedef const int64_t& crInt64_t;
typedef int64_t const& rcInt64_t;

typedef       uint64_t* pUInt64_t;
typedef       uint64_t& rUInt64_t;
typedef const uint64_t  cUInt64_t;
typedef const uint64_t* cpUInt64_t;
typedef uint64_t const* pcUInt64_t;
typedef const uint64_t* const cpcUInt64_t;
typedef const uint64_t& crUInt64_t;
typedef uint64_t const& rcUInt64_t;

typedef       float* pFloat;
typedef       float& rFloat;
typedef const float  cFloat;
typedef const float* cpFloat;
typedef float const* pcFloat;
typedef const float* const cpcFloat;
typedef const float& crFloat;
typedef float const& rcFloat;

typedef       double* pDouble;
typedef       double& rDouble;
typedef const double  cDouble;
typedef const double* cpDouble;
typedef double const* pcDouble;
typedef const double* const cpcDouble;
typedef const double& crDouble;
typedef double const& rcDouble;

typedef       long double* pLDouble;
typedef       long double& rLDouble;
typedef const long double  cLDouble;
typedef const long double* cpLDouble;
typedef long double const* pcLDouble;
typedef const long double* const cpcLDouble;
typedef const long double& crLDouble;
typedef long double const& rcLDouble;

/* Формирование id для различных типов класса */

enum IdType
{
  TYPE_DATA_CLASS              = 0x0001,
  TYPE_ERROR_CLASS             = 0x0002,
  TYPE_CAESAR_ENCRYPTION_CLASS = 0x0004
};

#endif // MY_STD_TYPEDEF_HPP
