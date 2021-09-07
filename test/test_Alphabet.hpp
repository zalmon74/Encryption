#define BOOST_TEST_MODULE Test module Encryption
#include <boost/test/included/unit_test.hpp>

#include "../include/CipherCaesar/Alphabet.hpp"
#include "../include/MyStdTypedef.hpp"
#include "../include/GlobalConstants.hpp"

BOOST_AUTO_TEST_SUITE(Alphabet_Tests)

BOOST_AUTO_TEST_CASE(CunstructorWithNoParametrs)
{
  // Объекты для тестирования
  const size_t relevant_ind  = UNDEFINED_VALUE_SIZE_T;
  const size_t relevant_size = UNDEFINED_VALUE_SIZE_T;
  const bool  relevant_dummy = true;
  Alphabet test_obj;
  // Тестирование
  size_t test_size = test_obj.GetSize();
  std::pair<size_t, size_t> test_ind_lower_case = test_obj.GetIndLowercase();
  std::pair<size_t, size_t> test_ind_upper_case = test_obj.GetIndUppercase();
  bool test_dummy = test_obj.IsDummy();

  // Проверка соот.
  BOOST_REQUIRE_EQUAL(test_dummy, relevant_dummy);
  BOOST_REQUIRE_EQUAL(test_size , relevant_size);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.first , relevant_ind);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.second, relevant_ind);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.first , relevant_ind);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.second, relevant_ind);
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrs)
{
  // Данные для тестирования
  // По договаренности расположение заглавных и прописных букв располагается на разницу в NUM_DIVISION_SYMBOLS
  const bool             relevant_dummy = false;
  const size_t relevant_ind_uppercase_1 = 24;
  const size_t relevant_ind_uppercase_2 = 0;
  const size_t relevant_ind_lowercase_1 = NUM_DIVISION_SYMBOLS;
  const size_t relevant_ind_lowercase_2 = NUM_DIVISION_SYMBOLS+2;
  const size_t   relevant_upercase_size = 1;
  const size_t  relevant_lowercase_size = 1;
  const size_t            relevant_size = 1;
  const std::string relevant_symbol_uppercase_1 = "F";
  const std::string relevant_symbol_uppercase_2 = "A";
  const std::string relevant_symbol_lowercase_1 = "q";
  const std::string relevant_symbol_lowercase_2 = "t";
  const std::map<size_t, std::string> input_alphabet_1 = {{relevant_ind_uppercase_1, relevant_symbol_uppercase_1}};
  const std::map<size_t, std::string> input_alphabet_2 = {{relevant_ind_lowercase_1, relevant_symbol_lowercase_1}};
  const std::map<size_t, std::string> input_alphabet_3 = {
                                                          {relevant_ind_uppercase_2, relevant_symbol_uppercase_2}
                                                         ,{relevant_ind_lowercase_2, relevant_symbol_lowercase_2}
                                                         };
  Alphabet test_obj(input_alphabet_1);
  // Вытаскиваем данные с объекта и проверяем их содержание
  size_t test_size = test_obj.GetSize();
  std::pair<size_t, size_t> test_ind_lower_case = test_obj.GetIndLowercase();
  std::pair<size_t, size_t> test_ind_upper_case = test_obj.GetIndUppercase();
  bool test_dummy = test_obj.IsDummy();
  BOOST_REQUIRE_EQUAL(test_size, relevant_upercase_size);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.first , UNDEFINED_VALUE_SIZE_T);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.second, UNDEFINED_VALUE_SIZE_T);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.first , relevant_ind_uppercase_1);
  // Так как элемент в алфавите всего один, то он является началом, и он является концом алфавита
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.second, relevant_ind_uppercase_1);
  BOOST_REQUIRE_EQUAL(test_dummy, relevant_dummy);

  // Формируем новый тестируемый объект
  test_obj = Alphabet(input_alphabet_2);
  // Вытаскиваем данные с объекта и проверяем их содержание
  test_size = test_obj.GetSize();
  test_ind_lower_case = test_obj.GetIndLowercase();
  test_ind_upper_case = test_obj.GetIndUppercase();
  test_dummy = test_obj.IsDummy();
  BOOST_REQUIRE_EQUAL(test_size, relevant_lowercase_size);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.first, relevant_ind_lowercase_1);
  // Так как элемент в алфавите всего один, то он является началом, и он является концом алфавита
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.second, relevant_ind_lowercase_1);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.first , UNDEFINED_VALUE_SIZE_T);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.second, UNDEFINED_VALUE_SIZE_T);
  BOOST_REQUIRE_EQUAL(test_dummy, relevant_dummy);

  // Формируем новый тестируемый объект
  test_obj = Alphabet(input_alphabet_3);
  // Вытаскиваем данные с объекта и проверяем их содержание
  test_size = test_obj.GetSize();
  test_ind_lower_case = test_obj.GetIndLowercase();
  test_ind_upper_case = test_obj.GetIndUppercase();
  test_dummy = test_obj.IsDummy();
  BOOST_REQUIRE_EQUAL(test_size, relevant_size);
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.first, relevant_ind_lowercase_2);
  // Так как элемент в алфавите всего один, то он является началом, и он является концом алфавита
  BOOST_REQUIRE_EQUAL(test_ind_lower_case.second, relevant_ind_lowercase_2);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.first , relevant_ind_uppercase_2);
  BOOST_REQUIRE_EQUAL(test_ind_upper_case.second, relevant_ind_uppercase_2);
  BOOST_REQUIRE_EQUAL(test_dummy, relevant_dummy);
}

BOOST_AUTO_TEST_CASE(OperatorAccessingAnItem)
{
  // Объекты для тестирования
  const size_t test_ind_1 = 0;
  const size_t test_ind_2 = 120;
  const size_t test_ind_3 = 160;
  const std::string test_str_ind_1 = "A";
  const std::string test_str_ind_2 = "u";
  const std::string test_str_ind_3 = "";
  const Alphabet test_obj = g_english_alphabet;

  // Проверка соот.
  BOOST_REQUIRE_EQUAL(test_obj[test_ind_1], test_str_ind_1);
  BOOST_REQUIRE_EQUAL(test_obj[test_ind_2], test_str_ind_2);
  BOOST_REQUIRE_EQUAL(test_obj[test_ind_3], test_str_ind_3);
  BOOST_REQUIRE_EQUAL(test_obj[test_str_ind_1], test_ind_1);
  BOOST_REQUIRE_EQUAL(test_obj[test_str_ind_2], test_ind_2);
  BOOST_REQUIRE_EQUAL(test_obj[test_str_ind_3], UNDEFINED_VALUE_SIZE_T);
}

BOOST_AUTO_TEST_SUITE_END()

