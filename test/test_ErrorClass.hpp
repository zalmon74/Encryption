#define BOOST_TEST_MODULE Test module Encryption
#include <boost/test/included/unit_test.hpp>

#include "../include/ErrorClass.hpp"

BOOST_AUTO_TEST_SUITE(ErrorClass_Tests)

BOOST_AUTO_TEST_CASE(CunstructorWithNoParametrs)
{
  // Параметры для проверки
  cInt32_t relevant_error = 0;
  ErrorClass test_class;
  // Вытаскиваем от туда значение ошибки
  int32_t error_test = test_class.GetError();
  // Проверяем соот. ошибок
  BOOST_REQUIRE_EQUAL(error_test, relevant_error);
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrsNoException)
{
  // Параметры для проверки
  cUInt16_t relevant_type_obj   = 0x0010;
  const std::vector<uint8_t> relevant_type_bit = {1, 4, 6, 8, 1};
  // Формируем значение с установленными битами соот. вектору relevant_type_bit
  int16_t relevant_type_error = 0;
  for (auto num_bit : relevant_type_bit)
    relevant_type_error |= (1 << num_bit);
  cInt32_t relevant_error = -22085648;
  ErrorClass test_class(relevant_type_obj, relevant_type_bit);
  // Вытаскиваем от туда значение ошибкиa
  int32_t error_test = test_class.GetError();
  // Проверяем соот. ошибок
  BOOST_REQUIRE_EQUAL(error_test, relevant_error);
  // Выделяем из ошибки тип объекта
  uint16_t type_obj = error_test & 0x0000FFFF;
  type_obj = -type_obj; // Изменянем знак, так как при конструировании объекта меняем знак у полей
  BOOST_CHECK_EQUAL(type_obj, relevant_type_obj);
  // Выделяем тип ошибки
  int16_t type_error = (error_test & 0XFFFF0000) >> 16;
  type_error = -type_error; // Изменянем знак, так как при конструировании объекта меняем знак у полей
  BOOST_CHECK_EQUAL(type_error, relevant_type_error);
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrsWithException)
{
  const std::vector<uint8_t> vec_ex_size = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  const std::vector<uint8_t> vec_ex_value = {16};
  BOOST_CHECK_THROW(ErrorClass(0, vec_ex_size) , std::length_error);
  BOOST_CHECK_THROW(ErrorClass(0, vec_ex_value), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(OperatorsComparsion)
{
  // Объекты для сравнения
  const ErrorClass obj_1(1, std::vector<uint8_t>{2});
  const ErrorClass obj_2(1, std::vector<uint8_t>{2});
  const ErrorClass obj_3(2, std::vector<uint8_t>{2});
  const ErrorClass obj_4(1, std::vector<uint8_t>{1});
  const int32_t error_1 = obj_1.GetError();
  const int32_t error_2 = obj_2.GetError();
  const int32_t error_3 = obj_3.GetError();
  const int32_t error_4 = obj_4.GetError();

  // Проверки
  BOOST_CHECK(obj_1   == obj_2  );
  BOOST_CHECK(error_1 == error_2);
  BOOST_REQUIRE_EQUAL((obj_1 == obj_2), (error_1 == error_2));
  BOOST_CHECK(obj_1   != obj_3  );
  BOOST_CHECK(error_1 != error_3);
  BOOST_REQUIRE_EQUAL((obj_1 != obj_3), (error_1 != error_3));
  BOOST_CHECK(obj_1   != obj_4  );
  BOOST_CHECK(error_1 != error_4);
  BOOST_REQUIRE_EQUAL((obj_1 != obj_4), (error_1 != error_4));
}

BOOST_AUTO_TEST_CASE(OperatorOrNoException)
{
  // Объекты для тестирования
  const ErrorClass obj_1(1, std::vector<uint8_t>{1});
  const ErrorClass obj_2(1, std::vector<uint8_t>{2});
  const ErrorClass relevant_obj(1, std::vector<uint8_t>{1, 2});
  const int32_t relevant_error = relevant_obj.GetError();
  ErrorClass test_obj = obj_1;
  test_obj |= obj_2;
  int32_t test_error = test_obj.GetError();
  // Проверка
  BOOST_CHECK(test_obj   == relevant_obj  );
  BOOST_CHECK(test_error == relevant_error);
  BOOST_REQUIRE_EQUAL((test_obj != relevant_obj), (test_error != relevant_error));
}

BOOST_AUTO_TEST_CASE(OperatorOrWithException)
{
  // Объекты для тестирования
  ErrorClass obj_1 (1, std::vector<uint8_t>{0});
  ErrorClass obj_2 (2, std::vector<uint8_t>{3});
  BOOST_CHECK_THROW( (obj_1 |= obj_2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
