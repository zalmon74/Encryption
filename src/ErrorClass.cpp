#include "../include/ErrorClass.hpp"

/* Реализация конструкторов класса ErrorClass */

// vec_num_bit - вектор с номерами битов, которые необходимо установить в 1
ErrorClass::ErrorClass(uint16_t type_obj, std::vector<uint8_t> vec_num_bit)
{
  this->type_obj   = type_obj;
  this->type_error = 0;
  // Устанавливаем соот. биты в ошибке
  for (auto num_bit : vec_num_bit)
  {
    this->type_error |= (1 << num_bit);
  }
  this->type_error = -this->type_error;
}

ErrorClass::ErrorClass(const ErrorClass& other)
{
  this->error = other.error;
}

/* Реализация перегрузки операторов класса ErrorClass */

ErrorClass& ErrorClass::operator|= (const ErrorClass other)
{
  if ((this->type_obj == other.type_obj) || (this->type_obj == 0)) 
  {
    this->type_obj    = other.type_obj;
    this->type_error |= other.type_error;
  }
  return *this;
}
