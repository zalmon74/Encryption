#ifndef DATA_CLASS_HPP
#define DATA_CLASS_HPP

#include <string>
#include <vector>
#include <stdint.h>
#include <ostream>
#include <iomanip>

#include "ErrorClass.hpp"

class DataClass
{
private:
  std::vector<uint8_t> data; // Даннные

  bool f_string; // Флаг, что данные являются строкой
  bool f_dummy ; // Флаг заглушки (пустышки)

public:

  /* Конструкторы */

  DataClass();
  DataClass(const std::string& data_str);
  DataClass(const std::vector<uint8_t>& data_vec);
  DataClass(const DataClass& data_other);

  /* Перегрузка операторов */

  bool          operator!= (const DataClass& data_other) const;
  bool          operator== (const DataClass& data_other) const;
  DataClass&    operator= (const DataClass& data_other);

  friend std::ostream& operator<< (std::ostream& out, const DataClass& data);

  /* Методы */

  ErrorClass SetDataStr(const std::string& data_str);
  ErrorClass SetDataVec(const std::vector<uint8_t>& data_vec);

  std::string GetDataStr() const;

  std::vector<uint8_t> GetDataVec() const { return this->data;        }
  bool GetFlagStr                () const { return this->f_string;    }
  bool IsDummy                   () const { return this->f_dummy;     }


  // Метод отчистки данных
  void Clear();

};

typedef       DataClass* pDataClass;
typedef       DataClass& rDataClass;
typedef const DataClass  cDataClass;
typedef const DataClass* cpDataClass;
typedef DataClass* const pcDataClass;
typedef const DataClass* const cpcDataClass;
typedef const DataClass& crDataClass;

#endif // DATA_CLASS_HPP
