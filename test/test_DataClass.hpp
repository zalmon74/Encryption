#define BOOST_TEST_MODULE Test module Encryption
#include <boost/test/included/unit_test.hpp>

#include <boost/filesystem.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../include/DataClass.hpp"
#include "../include/GlobalConstants.hpp"

BOOST_AUTO_TEST_SUITE(DataClass_Tests)

BOOST_AUTO_TEST_CASE(CunstructorWithNoParametrs)
{
  // Параметры для проверки
  const std::vector<uint8_t> relevant_data;
  cBool relevant_f_str   = false;
  cBool relevant_f_dummy = true;
  DataClass test_class;
  // Вытаскиваем с объекта значения полей
  std::vector<uint8_t> data = test_class.GetDataVec();
  bool                f_str = test_class.GetFlagStr();
  bool              f_dummy = test_class.IsDummy();
  // Проверяем соот. полей
  BOOST_REQUIRE_EQUAL_COLLECTIONS(data.begin(), data.end(), relevant_data.begin(), relevant_data.end());
  BOOST_REQUIRE_EQUAL(f_str  , relevant_f_str);
  BOOST_REQUIRE_EQUAL(f_dummy, relevant_f_dummy);
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrString)
{
  // Параметры для проверки
  const std::string relevant_str = "Text for test!";
  cBool relevant_f_str   = true;
  cBool relevant_f_dummy = false;
  DataClass test_class(relevant_str);
  // Вытаскиваем с объекта значения полей
  std::string str = test_class.GetDataStr();
  bool      f_str = test_class.GetFlagStr();
  bool    f_dummy = test_class.IsDummy();
  // Проверяем соот. полей
  BOOST_REQUIRE_EQUAL_COLLECTIONS(str.begin(), str.end(), relevant_str.begin(), relevant_str.end());
  BOOST_REQUIRE_EQUAL(f_str  , relevant_f_str);
  BOOST_REQUIRE_EQUAL(f_dummy, relevant_f_dummy);
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrVector)
{
  // Параметры для проверки
  const std::vector<uint8_t> relevant_data = {0xFF, 0x1F, 0x10, 0x00, 0xF5, 0xAA};
  cBool relevant_f_str   = false;
  cBool relevant_f_dummy = false;
  DataClass test_class(relevant_data);
  // Вытаскиваем с объекта значения полей
  std::vector<uint8_t> data = test_class.GetDataVec();
  bool                f_str = test_class.GetFlagStr();
  bool              f_dummy = test_class.IsDummy();
  // Проверяем соот. полей
  BOOST_REQUIRE_EQUAL_COLLECTIONS(data.begin(), data.end(), relevant_data.begin(), relevant_data.end());
  BOOST_REQUIRE_EQUAL(f_str  , relevant_f_str);
  BOOST_REQUIRE_EQUAL(f_dummy, relevant_f_dummy);
}

BOOST_AUTO_TEST_CASE(CunstructorCopy)
{
  // Объекты для тестирования
  cDataClass obj("Test!");
  cDataClass obj_copy(obj);
  /* Поля объектов для сравнения */
  // 1
  std::vector<uint8_t> data = obj.GetDataVec();
  std::string           str = obj.GetDataStr();
  bool                f_str = obj.GetFlagStr();
  bool              f_dummy = obj.IsDummy();
  // 2
  std::vector<uint8_t> data_copy = obj_copy.GetDataVec();
  std::string           str_copy = obj_copy.GetDataStr();
  bool                f_str_copy = obj_copy.GetFlagStr();
  bool              f_dummy_copy = obj_copy.IsDummy();
  // Проверка соот. объектов
  BOOST_CHECK(obj     == obj_copy    );
  BOOST_CHECK(data    == data_copy   );
  BOOST_CHECK(str     == str_copy    );
  BOOST_CHECK(f_str   == f_str_copy  );
  BOOST_CHECK(f_dummy == f_dummy_copy);

  bool f_result = (data  == data_copy ) && (str     == str_copy     ) &&
                  (f_str == f_str_copy) && (f_dummy == f_dummy_copy);
  BOOST_REQUIRE_EQUAL((obj == obj_copy), f_result);
}

BOOST_AUTO_TEST_CASE(OperatorAssignment)
{
  // Объекты для тестирования
  DataClass  obj;
  cDataClass obj_assig("Test!");
  const std::vector<uint8_t> relevant_data;
  cBool relevant_f_str   = false;
  cBool relevant_f_dummy = true;
  // Поля объекта для сравнения
  std::vector<uint8_t> data = obj.GetDataVec();
  bool                f_str = obj.GetFlagStr();
  bool              f_dummy = obj.IsDummy();
  // Проверка до присваивания
  BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(), data.end(), relevant_data.begin(), relevant_data.end());
  BOOST_CHECK(f_str   == relevant_f_str    );
  BOOST_CHECK(f_dummy == relevant_f_dummy  );
  // Присваиваем значения и вытаскиваем поля с объектов
  obj = obj_assig;
  data = obj.GetDataVec();
  f_str = obj.GetFlagStr();
  f_dummy = obj.IsDummy();
  std::string str = obj.GetDataStr();
  std::vector<uint8_t> data_assig = obj_assig.GetDataVec();
  bool                f_str_assig = obj_assig.GetFlagStr();
  bool              f_dummy_assig = obj_assig.IsDummy();
  std::string           str_assig = obj_assig.GetDataStr();
  // Проверяем соот. полей и объектов
  BOOST_REQUIRE(obj == obj_assig);
  BOOST_REQUIRE_EQUAL_COLLECTIONS(data.begin(), data.end(), data_assig.begin(), data_assig.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(str.begin(), str.end(), str_assig.begin(), str_assig.end());
  BOOST_REQUIRE(f_str   == f_str_assig);
  BOOST_REQUIRE(f_dummy == f_dummy_assig);
}

BOOST_AUTO_TEST_CASE(OperatorsComparsion)
{
  // Объекты для сравнения
  cDataClass obj_dummy;
  cDataClass obj_str_1("Test!");
  cDataClass obj_str_2("Test!");
  cDataClass obj_vec(std::vector<uint8_t>{0x01, 0x02, 0x03});
  /* Поля объектов для сравнения */
  // 1
  std::vector<uint8_t> data_dummy = obj_dummy.GetDataVec();
  std::string           str_dummy = obj_dummy.GetDataStr();
  bool                f_str_dummy = obj_dummy.GetFlagStr();
  bool              f_dummy_dummy = obj_dummy.IsDummy();
  // 2
  std::vector<uint8_t> data_str_1 = obj_str_1.GetDataVec();
  std::string           str_str_1 = obj_str_1.GetDataStr();
  bool                f_str_str_1 = obj_str_1.GetFlagStr();
  bool              f_dummy_str_1 = obj_str_1.IsDummy();
  // 3
  std::vector<uint8_t> data_str_2 = obj_str_2.GetDataVec();
  std::string           str_str_2 = obj_str_2.GetDataStr();
  bool                f_str_str_2 = obj_str_2.GetFlagStr();
  bool              f_dummy_str_2 = obj_str_2.IsDummy();
  // 4
  std::vector<uint8_t> data_vec = obj_vec.GetDataVec();
  std::string           str_vec = obj_vec.GetDataStr();
  bool                f_str_vec = obj_vec.GetFlagStr();
  bool              f_dummy_vec = obj_vec.IsDummy();
  /* Проверки */
  // 1
  BOOST_CHECK(obj_dummy     != obj_str_1    );
  BOOST_CHECK(data_dummy    != data_str_1   );
  BOOST_CHECK(str_dummy     != str_str_1    );
  BOOST_CHECK(f_str_dummy   != f_str_str_1  );
  BOOST_CHECK(f_dummy_dummy != f_dummy_str_1);

  bool f_result = (data_dummy  != data_str_1 ) && (str_dummy    != str_str_1     ) &&
                  (f_str_dummy != f_str_str_1) && (f_dummy_dummy != f_dummy_str_1);
  BOOST_REQUIRE_EQUAL((obj_dummy != obj_str_1), f_result);
  // 2
  BOOST_CHECK(obj_str_1     == obj_str_2    );
  BOOST_CHECK(data_str_1    == data_str_2   );
  BOOST_CHECK(str_str_1     == str_str_2    );
  BOOST_CHECK(f_str_str_1   == f_str_str_2  );
  BOOST_CHECK(f_dummy_str_1 == f_dummy_str_2);

  f_result = (data_str_1  == data_str_2 ) && (str_str_1     == str_str_2    ) &&
             (f_str_str_1 == f_str_str_2) && (f_dummy_str_1 == f_dummy_str_2);
  BOOST_REQUIRE_EQUAL((obj_dummy != obj_str_2), f_result);
  // 3
  BOOST_CHECK(obj_vec     != obj_str_1    );
  BOOST_CHECK(data_vec    != data_str_1   );
  BOOST_CHECK(str_vec     != str_str_1    );
  BOOST_CHECK(f_str_vec   != f_str_str_1  );
  BOOST_CHECK(f_dummy_vec == f_dummy_str_1);

  f_result = (data_vec  != data_str_1 ) && (str_vec     != str_str_1    ) &&
             (f_str_vec != f_str_str_1) && (f_dummy_vec == f_dummy_str_1);
  BOOST_REQUIRE_EQUAL((obj_vec != obj_str_1), f_result);
}

BOOST_AUTO_TEST_CASE(SetDataFromVecAndStrWithNotError)
{
  // Объекты для тестирования
  DataClass test_obj;
  const std::string str = "Test!";
  const std::vector<uint8_t> vec = {0x01, 0x02, 0x03};
  // Вытаскиваем необходмые поля с объекта и проверяем, что они не соот. входным значениям
  std::string str_obj          = test_obj.GetDataStr();
  std::vector<uint8_t> vec_obj = test_obj.GetDataVec();
  BOOST_CHECK(str_obj != str);
  BOOST_CHECK(vec_obj != vec);
  // Присваиваем объекту строку и проверяем соот.
  auto error = test_obj.SetDataStr(str);
  str_obj = test_obj.GetDataStr();
  vec_obj = test_obj.GetDataVec();
  BOOST_REQUIRE(error == g_error_free);
  BOOST_REQUIRE(str_obj == str);
  BOOST_REQUIRE(vec_obj != vec);
  // Присваиваем объекту вектор с данными и проверяем соот.
  error = test_obj.SetDataVec(vec);
  str_obj = test_obj.GetDataStr();
  vec_obj = test_obj.GetDataVec();
  BOOST_REQUIRE(error == g_error_free);
  BOOST_REQUIRE(str_obj != str);
  BOOST_REQUIRE(vec_obj == vec);
}

BOOST_AUTO_TEST_CASE(SetDataFromVecAndStrWithError)
{
  // Объекты для тестирования
  DataClass test_obj;
  const std::string str;
  const std::vector<uint8_t> vec;
  // Проверяем
  auto error = test_obj.SetDataStr(str);
  BOOST_REQUIRE(error == g_data_class_error_lack_data);
  error = test_obj.SetDataVec(vec);
  BOOST_REQUIRE(error == g_data_class_error_lack_data);
}

BOOST_AUTO_TEST_CASE(WriteDataToFileWithNoError)
{
  // Объекты для тестирования
  const std::vector<uint8_t> data_vec = {0x01, 0x02, 0x03, 0x04};
  const std::string data_str = "Test!";
  const std::string path_files = "./";
  const std::string name_file_1 = "data_vec.bin";
  const std::string name_file_2 = "data_str.txt";
  DataClass test_obj_vec(data_vec);
  DataClass test_obj_str(data_str);
  // Проверяем наличие файлов для тестирования, если они имеются, то удаляем их
  bool presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_1));
  if (presence_file)
    boost::filesystem::remove(boost::filesystem::path(path_files+name_file_1));
  presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_2));
  if (presence_file)
    boost::filesystem::remove(boost::filesystem::path(path_files+name_file_2));
  // Записываем данные в файл
  auto error = test_obj_vec.WriteDataToFile(path_files, name_file_1);
  BOOST_CHECK(error == g_error_free);
  error = test_obj_str.WriteDataToFile(path_files, name_file_2);
  BOOST_CHECK(error == g_error_free);
  // Проверяем наличие файлов
  presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_1));
  BOOST_REQUIRE(presence_file);
  presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_2));
  BOOST_REQUIRE(presence_file);
  // Проверяем содержание файла 1
  boost::interprocess::file_mapping file_1((path_files+name_file_1).c_str(), boost::interprocess::read_only); // Открываем файл
  boost::interprocess::mapped_region region_1(file_1, boost::interprocess::read_only, 0, 0); // Выгружаем содержание файла в память
  uint8_t* data_begin = reinterpret_cast<uint8_t*>(region_1.get_address()); // Получем указатель на данные в памяти
  // Проверяем соот. данных
  BOOST_REQUIRE_EQUAL_COLLECTIONS(data_begin, data_begin+region_1.get_size(), data_vec.begin(), data_vec.end());
  // Проверяем содержание файла 2
  boost::interprocess::file_mapping file_2((path_files+name_file_2).c_str(), boost::interprocess::read_only); // Открываем файл
  boost::interprocess::mapped_region region_2(file_2, boost::interprocess::read_only, 0, 0); // Выгружаем содержание файла в память
   data_begin = reinterpret_cast<uint8_t*>(region_2.get_address()); // Получем указатель на данные в памяти
  // Проверяем соот. данных
  BOOST_REQUIRE_EQUAL_COLLECTIONS(data_begin, data_begin+region_2.get_size(), data_str.begin(), data_str.end());

  // Удаляем созданные файлы
  file_1.remove((path_files+name_file_1).c_str());
  file_2.remove((path_files+name_file_2).c_str());
}

BOOST_AUTO_TEST_CASE(WriteDataToFileWithError)
{
  DataClass test_class;
  auto error = test_class.WriteDataToFile("./");
  BOOST_REQUIRE(error == g_data_class_error_lack_data);
}

BOOST_AUTO_TEST_CASE(ReadDataFromFileWithNoError)
{
  // Объекты для тестирования
  const std::vector<uint8_t> data_vec = {0x01, 0x02, 0x03, 0x04};
  const std::string data_str = "Test!";
  const std::string path_files = "./";
  const std::string name_file_1 = "data_vec.bin";
  const std::string name_file_2 = "data_str.txt";
  // Записываем данные в файлы
  std::ofstream file(path_files+name_file_1, std::fstream::ios_base::out | std::fstream::ios_base::binary);
  // Проверяем открытие файла
  BOOST_CHECK(file.is_open());
  if (file.is_open())
  {
    for (auto byte : data_vec)
      file << byte;
  }
  file.close();
  // Считываем с файла значение в объект
  DataClass test_obj;
  auto error = test_obj.ReadDataFromFile(path_files+name_file_1, false);
  BOOST_REQUIRE(error == g_error_free);
  // Вытаскиваем данные с объекта и сравниваем с исходными
  auto test_vec = test_obj.GetDataVec();
  BOOST_REQUIRE_EQUAL_COLLECTIONS(test_vec.begin(), test_vec.end(), data_vec.begin(), data_vec.end());
  // Записываем в файл строку
  file.open(path_files+name_file_2, std::fstream::ios_base::out);
  // Проверяем открытие файла
  BOOST_CHECK(file.is_open());
  if (file.is_open())
  {
    file << data_str;
  }
  file.close();
  // Считываем данные с файла в объект
  error = test_obj.ReadDataFromFile(path_files+name_file_1, true);
  BOOST_REQUIRE(error == g_error_free);
  // Вытаскиваем данные с объекта и сравниваем с исходными
  auto test_str = test_obj.GetDataStr();
  BOOST_REQUIRE_EQUAL_COLLECTIONS(test_str.begin(), test_str.end(), data_vec.begin(), data_vec.end());

  // Удаляем файлы, если они имеются
  bool presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_1));
  if (presence_file)
    boost::filesystem::remove(boost::filesystem::path(path_files+name_file_1));
  presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_file_2));
  if (presence_file)
    boost::filesystem::remove(boost::filesystem::path(path_files+name_file_2));
}

BOOST_AUTO_TEST_CASE(ReadDataFromFileWithError)
{
  const std::string path_files = "./";
  const std::string name_empty_file = "test.txt";
  DataClass test_obj;
  auto error = test_obj.ReadDataFromFile(path_files, true);
  BOOST_REQUIRE(error == g_data_class_error_file_not_open);
  // Создаем пустой файл и считываем его
  std::ofstream file(path_files+name_empty_file, std::fstream::ios_base::out);
  file.close();
  error = test_obj.ReadDataFromFile(path_files+name_empty_file, true);
  BOOST_REQUIRE(error == g_data_class_error_empty_file);

  // Удаляем созданный файл
  bool presence_file = boost::filesystem::exists(boost::filesystem::path(path_files+name_empty_file));
  if (presence_file)
    boost::filesystem::remove(boost::filesystem::path(path_files+name_empty_file));
}

BOOST_AUTO_TEST_SUITE_END()
