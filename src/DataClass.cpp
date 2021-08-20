#include "../include/DataClass.hpp"
#include "../include/GlobalConstants.hpp"

/* Реализация конструкторов класса DataClass */

DataClass::DataClass()
{
  this->f_string = false;
  this->f_dummy  = true;
}

DataClass::DataClass(const std::string& data_str)
{
  if (data_str.size() != 0)
  {
    this->f_dummy  = false;
    this->f_string = true;
    this->data     = std::vector<uint8_t>(data_str.begin(), data_str.end());
  }
  else
    this->f_dummy = true;
}

DataClass::DataClass(const std::vector<uint8_t>& data_vec)
{
  if (data_vec.size() != 0)
  {
    this->f_dummy  = false;
    this->f_string = false;
    this->data     = data_vec;
  }
  else
    this->f_dummy = true;
}

DataClass::DataClass(const DataClass& data_other)
{
  this->data     = data_other.data;
  this->f_string = data_other.f_string;
  this->f_dummy  = data_other.f_dummy;
}

/* Перегрузка операторов для класса DataClass */

bool DataClass::operator!= (const DataClass& data_other) const
{
  return (
          (this->f_string != data_other.f_string) ||
          (this->f_dummy  != data_other.f_dummy)  ||
          (this->data     != data_other.data)
         );
}

bool DataClass::operator== (const DataClass& data_other) const
{
  return (!(*this != data_other));
}

DataClass& DataClass::operator= (const DataClass& data_other)
{
  if (*this == data_other)
    return *this;
  
  this->data     = data_other.data;
  this->f_string = data_other.f_string;
  this->f_dummy  = data_other.f_dummy;
  return *this;
}

std::ostream& operator<< (std::ostream& out, const DataClass& data)
{
  if (!data.IsDummy())
  {
    // Если данные не являются строкой
    if (!data.GetFlagStr())
    {
      out << std::hex << std::setfill('0') << std::uppercase;
      for (size_t ind = 0; ind < data.GetDataVec().size(); ind++)
      {
        out << std::setw(2) << static_cast<int>(data.GetDataVec()[ind]);
        if (!data.GetFlagStr())
          out << ' ';
        if (((ind+1) % 16) == 0)
          out << '\n';
      }
      if (!data.GetFlagStr())
        out << std::dec;
    }
    else
      out << data.GetDataStr();
  }
  else
    out << "Объект является пустышкой (заглушкой)\n";
  
  return out;
}

/* Описание методов класса DataCLass */

ErrorClass DataClass::SetDataStr(const std::string& data_str)
{
  // Если входных данных нет, то выдаем соот. ошибку
  if (data_str.size() == 0)
  {
    return g_data_class_error_lack_data;
  }

  // Отчищаем от старых данных
  this->Clear();

  // Убираем флаг пустышки и выставляем флаг строки
  this->f_dummy  = false;
  this->f_string = true;

  // Переконвертируем строку в вектор
  this->data.resize(data_str.size());
  std::copy(data_str.begin(), data_str.end(), this->data.begin()); 

  return g_error_free;
}

ErrorClass DataClass::SetDataVec(const std::vector<uint8_t>& data_vec)
{
  // Если входных данных нет, то выдаем соот. ошибку
  if (data_vec.size() == 0)
  {
    return g_data_class_error_lack_data;
  }

  // Отчищаем от старых данных
  this->Clear();

  // Убираем флаг пустышки, выставляем флаг строки и устанавливаем новые данные
  this->f_dummy  = false;
  this->f_string = true;
  this->data = data_vec;

  return g_error_free;
}

std::string DataClass::GetDataStr() const
{
  std::string output;
  if (this->f_string)
  {
    output.resize(this->data.size());
    std::copy(this->data.begin(), this->data.end(), output.begin());
  }
  return output;
}

// Метод отчистки данных
void DataClass::Clear()
{
  this->data.clear();
  this->f_string = false;
  this->f_dummy  = true;
}
