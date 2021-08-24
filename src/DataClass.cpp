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

/* Метод записи данных в файл */
// path_file - путь до файла
ErrorClass DataClass::WriteDataToFile(const std::string& path_file, const std::string& name_output_file)
{
  ErrorClass error_output = g_error_free;
  // Проверка на пустышку
  if (this->IsDummy())
    error_output = g_data_class_error_lack_data;
  // Проверка на наличие данных
  if (this->data.size() == 0)
    error_output = g_data_class_error_lack_data;
  // Если ошибок нет, то записываем данные в файл
  if (error_output == g_error_free)
  {
    std::string name_file = path_file;
    // Проверяем наличие '/' в конце пути до файла, если его нет, то добавляем
//    if ((path_file[path_file.size()-1] == '/') || (path_file[path_file.size()-1] == '\\'))
//      name_file += "/";
    // Проверяем на наличие требования опред. имени файла, если нет, то назваем стандартным образом
    if (name_output_file.size() == 0)
    {
      // Определяем какое из 2х стандартных имен необходимо использовать (*.txt или *.bin)
      if (this->f_string)
        name_file += NAME_OUTPUT_TXT_FILE;
      else
        name_file += NAME_OUTPUT_BIN_FILE;
    }
    else
      name_file += name_output_file;
    // Создаем поток с файлом и пытаемся его открыть
    std::ofstream file;
    // Зависимости какие у нас данные: строковые или бинарные, соот. образом открываем файл
    if (this->f_string)
      file.open(name_file, std::ios::out | std::ios::trunc);
    else
      file.open(name_file, std::ios::out | std::ios::trunc | std::ios::binary);
    // Проверяем на успешность открытия файла
    if (!file.is_open())
      error_output = g_data_class_error_file_not_open;
    else
    {
      // Если данные строковые, то необходимо сначало преобразовать их в строку, иначе записываем по байту в файл
      if (this->f_string)
      {
        auto output_str = this->GetDataStr();
        file << output_str;
      }
      else
        file.write(reinterpret_cast<char*>(this->data.data()), this->data.size());
      file.close();
    }
  }

  return error_output;
}

/* Метод чтения данных из файла */
// f_data_str - флаг, что чтаемые данные являются текстовыми данными
ErrorClass DataClass::ReadDataFromFile(const std::string& path_file, crBool f_data_str)
{
  ErrorClass error_output = g_error_free;
  // Создаем поток для файла
  std::ifstream file;
  // Открываем файл зависимости от флага типа данных
  if (f_data_str)
    file.open(path_file, std::ios::in);
  else
    file.open(path_file, std::ios::in | std::ios::binary);
  // Проверяем на открытие файла
  if (!file.is_open())
    error_output = g_data_class_error_file_not_open;
  else
  {
    std::vector<uint8_t> read_vec;
    // Считываем данные из потока по 512 байт (BufSize)
    while(!file.eof())
    {
      read_vec.resize(this->data.size()+BUFSIZ);
      file.read(reinterpret_cast<char*>(read_vec.data()), BUFSIZ);
    }
    // Освобождаем не нужную память
    while (!read_vec.empty() && (read_vec[read_vec.size()-1] == 0))
      read_vec.pop_back();
    // Проверяем, что файл был не пустым
    if (read_vec.size() == 0)
      error_output = g_data_class_error_empty_file;
    else
    {
      // Отчищаем объект от старых данных
      this->Clear();
      // Убираем флаг заглушки и устанавливаем флаг данных
      this->f_dummy  = false;
      this->f_string = f_data_str;
      this->data = read_vec;
    }
    file.close();
  }

  return error_output;
}








