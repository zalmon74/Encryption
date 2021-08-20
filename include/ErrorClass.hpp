#ifndef ERROR_CLASS_HPP
#define ERROR_CLASS_HPP

#include <stdint.h>
#include <vector>

#include "MyStdTypedef.hpp"

#pragma pack(1)
class ErrorClass
{
private:
  union
  {
    // Сама ошибка
    int32_t error;
    /* Ошибка расписанная по битам */
    struct 
    {
      int32_t type_obj    : 16;  // Тип объекта у которой возникла данная ошибка
      int32_t type_error  : 16; // Тип ошибки
    };
  };

public:

  static cUInt16_t TYPE_CLASS = TYPE_ERROR_CLASS;

  /* Конструкторы */

  explicit ErrorClass() : error(0) {}
  // vec_num_bit - вектор с номерами битов, которые необходимо установить в 1 
  //! значение, которое должен хранить вектор, не должно превышать 15 (нумерация начинается с 0)
  explicit ErrorClass(uint16_t type_obj, std::vector<uint8_t> vec_num_bit);
  ErrorClass(const ErrorClass&);
 
  // Перегрузка операторов
  ErrorClass& operator= (const ErrorClass& other) = default;

  bool operator!= (const ErrorClass other) const { return (this->error != other.error); }
  bool operator== (const ErrorClass other) const { return (this->error == other.error); }
  ErrorClass& operator|= (const ErrorClass other);

  /* Методы */

  int32_t GetError() const { return this->error; }

};
#pragma pack()

typedef       ErrorClass* pErrorClass;
typedef       ErrorClass& rErrorClass;
typedef const ErrorClass  cErrorClass;
typedef const ErrorClass* cpErrorClass;
typedef ErrorClass* const pcErrorClass;
typedef const ErrorClass* const cpcErrorClass;
typedef const ErrorClass& crErrorClass;

#endif // ERROR_CLASS_HPP
