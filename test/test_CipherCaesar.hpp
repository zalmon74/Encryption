#define BOOST_TEST_MODULE Test module Encryption
#include <boost/test/included/unit_test.hpp>

#include "../include/CipherCaesar/CipherCaesar.hpp"
#include "../include/MyStdTypedef.hpp"
#include "../include/GlobalConstants.hpp"

BOOST_AUTO_TEST_SUITE(CipherCaesar_Tests)

BOOST_AUTO_TEST_CASE(CunstructorWithNoParametrs)
{
  // Объекты для тестирования
  cDataClass relevant_data_class;
  cAlphabet  relevant_alphabet;
  cInt16_t   relevant_shift_alphabet = UNDEFINED_VALUE_INT16_T;
  CaesarEncryption test_obj;

  // Проверка соот.
  BOOST_REQUIRE(relevant_data_class     == test_obj.GetData());
  BOOST_REQUIRE(relevant_alphabet       == test_obj.GetAlphabet());
  BOOST_REQUIRE(relevant_shift_alphabet == test_obj.GetShiftAlphabet());
}

BOOST_AUTO_TEST_CASE(CunstructorWithParametrs)
{
  // Объекты для тестирования
  cDataClass relevant_data_class("Test!");
  cAlphabet  relevant_alphabet = g_english_alphabet;
  cInt16_t   relevant_shift_alphabet = 2;
  CaesarEncryption test_obj(relevant_data_class, relevant_alphabet, relevant_shift_alphabet);

  // проверка соот.
  BOOST_REQUIRE(relevant_data_class     == test_obj.GetData());
  BOOST_REQUIRE(relevant_alphabet       == test_obj.GetAlphabet());
  BOOST_REQUIRE(relevant_shift_alphabet == test_obj.GetShiftAlphabet());
}

BOOST_AUTO_TEST_CASE(OperatorFunctorWitchNotError)
{
  // Объекты для тестирования
  cDataClass relevant_data_class("Test!");
  cDataClass relevant_rus_data_class("Цчпилщ!");
  cAlphabet  relevant_alphabet = g_english_alphabet;
  cAlphabet  relevant_rus_alphabet = g_russian_alphabet;
  cInt16_t   relevant_shift_alphabet = 2;
  cInt16_t   relevant_rus_shift_alphabet = -7;
  cDataClass relevant_output_data_class("Vguv!");
  cDataClass relevant_rus_output_data_class("Привет!");
  CaesarEncryption test_obj(relevant_data_class, relevant_alphabet, relevant_shift_alphabet);

  // Вызываем оператор () для шифрования данных
  DataClass output_data;
  auto error = test_obj(output_data);

  // Проверяем соот.
  BOOST_REQUIRE(error == g_error_free);
  BOOST_REQUIRE(output_data == relevant_output_data_class);

  // Вызываем оператор () для шифрования (дешифровки) данных
  error = test_obj(relevant_rus_data_class, relevant_rus_alphabet, relevant_rus_shift_alphabet, output_data);
  BOOST_REQUIRE(error == g_error_free);
  BOOST_REQUIRE(output_data == relevant_rus_output_data_class);
}

BOOST_AUTO_TEST_CASE(OperatorFunctorWitchError)
{
  // Объекты для тестирования
  cDataClass empty_data;
  cDataClass data("Test!");
  cAlphabet  empty_alphabet;
  cInt16_t   undef_shift_alphabet = UNDEFINED_VALUE_INT16_T;
  DataClass output_data;
  CaesarEncryption test_obj;

  /* Проверяем соот. */
  // Проверка на отсутствие данных
  auto error = test_obj(empty_data, g_english_alphabet, 2, output_data);
  BOOST_REQUIRE(error == g_caesar_encr_error_lack_data);
  BOOST_REQUIRE(output_data == empty_data);
  // Проверка на отсутствие алфавита
  error = test_obj(data, empty_alphabet, 0, output_data);
  BOOST_REQUIRE(error == g_caesar_encr_error_lack_alphabet);
  BOOST_REQUIRE(output_data == empty_data);
  // Проверка на отсутствие смещения алфавита
  ErrorClass more_error;
  more_error |= g_caesar_encr_error_lack_shift_alphabet;
  more_error |= g_caesar_encr_error_size_less_shift_alph;
  error = test_obj(data, g_english_alphabet, undef_shift_alphabet, output_data);
  BOOST_REQUIRE(error == more_error);
  BOOST_REQUIRE(output_data == empty_data);
  // Проверка на различие размера алфавита и его смещение
  error = test_obj(data, g_english_alphabet, 999, output_data);
  BOOST_REQUIRE(error == g_caesar_encr_error_size_less_shift_alph);
  BOOST_REQUIRE(output_data == empty_data);
  // Проверка на отсутствие определенного символа в алфавите
  error = test_obj(data, g_russian_alphabet, 1, output_data);
  BOOST_REQUIRE(error == g_caesar_encr_error_miss_symb_in_alph);
  BOOST_REQUIRE(output_data == empty_data);
  // Проверка на совокупность отсутствующих данных
  more_error = g_error_free;
  more_error |= g_caesar_encr_error_lack_data;
  more_error |= g_caesar_encr_error_lack_alphabet;
  more_error |= g_caesar_encr_error_lack_shift_alphabet;
  more_error |= g_caesar_encr_error_size_less_shift_alph;
  error = test_obj(empty_data, empty_alphabet, undef_shift_alphabet, output_data);
  BOOST_REQUIRE(error == more_error);
  BOOST_REQUIRE(output_data == empty_data);
}

BOOST_AUTO_TEST_CASE(SetDataWithNotError)
{
  // Объекты для тестирования
  cDataClass relevant_data("Test!");
  cAlphabet  relevant_alphabet = g_english_alphabet;
  cInt16_t   relevant_shift = 2;
  CaesarEncryption test_obj;

  // Проверка соот.
  auto error = test_obj.SetData(relevant_data);
  BOOST_REQUIRE(error == g_error_free);

  error = test_obj.SetAlphabet(relevant_alphabet);
  BOOST_REQUIRE(error == g_error_free);

  error = test_obj.SetAlphabetShift(relevant_shift);
  BOOST_REQUIRE(error == g_error_free);

  BOOST_REQUIRE(test_obj.GetData()          == relevant_data);
  BOOST_REQUIRE(test_obj.GetAlphabet()      == relevant_alphabet);
  BOOST_REQUIRE(test_obj.GetShiftAlphabet() == relevant_shift);
}

BOOST_AUTO_TEST_CASE(SetDataWithError)
{
  // Объекты для тестирования
  cDataClass relevant_data;
  cAlphabet  relevant_alphabet;
  cInt16_t   relevant_shift = UNDEFINED_VALUE_INT16_T;
  CaesarEncryption test_obj;

  // Проверка соот.
  auto error = test_obj.SetData(relevant_data);
  BOOST_REQUIRE(error == g_caesar_encr_error_lack_data);

  error = test_obj.SetAlphabet(relevant_alphabet);
  BOOST_REQUIRE(error == g_caesar_encr_error_lack_alphabet);

  error = test_obj.SetAlphabetShift(relevant_shift);
  ErrorClass more_errors;
  more_errors |= g_caesar_encr_error_lack_shift_alphabet;
  more_errors |= g_caesar_encr_error_size_less_shift_alph;
  BOOST_REQUIRE(error == more_errors);
}

// В данном тесте ошибки проверяться не будут, так как ошибки формируются в отдельном методе.
// А данный метод для всех способов шифрования (использовать класс как функтор или данный метод) вызывается аналогично
BOOST_AUTO_TEST_CASE(EncryptMethod)
{
  // Объекты для тестирования
  cDataClass relevant_data("Test!");
  cAlphabet  relevant_alphabet = g_english_alphabet;
  cInt16_t   relevant_shift = 21;
  cDataClass relevant_output_data("Ozno!");
  CaesarEncryption test_obj(relevant_data, relevant_alphabet, relevant_shift);

  // Проверка соот.
  BOOST_CHECK(test_obj.GetData()          == relevant_data);
  BOOST_CHECK(test_obj.GetAlphabet()      == relevant_alphabet);
  BOOST_CHECK(test_obj.GetShiftAlphabet() == relevant_shift);

  DataClass output_data;
  auto error = test_obj.Encrypt(output_data);
  BOOST_REQUIRE(error == g_error_free);
  std::cout << output_data.GetDataStr() << "\n";
  BOOST_REQUIRE(output_data == relevant_output_data);
}

BOOST_AUTO_TEST_SUITE_END()
