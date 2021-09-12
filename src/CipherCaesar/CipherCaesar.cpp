#include "../../include/CipherCaesar/CipherCaesar.hpp"
#include "../../include/MyStdTypedef.hpp"
#include "../../include/GlobalConstants.hpp"

#include <iostream>

/* Реализация конструкторов для класса CaesarEncryption */

/* Вх. данные:
  * data - данные, которые необходимо зашифровать. Т. к. данный метод шифрования шифрует только текст
  *       , то данные должны быть в виде текста 
  * alphabet_data  - алфавит для распознавания (шифрования) текста
  * shift_alphabet - ключ шифрования (смещение для алфавита) 
*/
CaesarEncryption::CaesarEncryption(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet)
{
  this->data_encryption     = data;
  this->alphabet_encryption = alphabet_data;
  this->shift_alphabet      = shift_alphabet; 
}

/* Реализация перегрузки операторов класса CaesarEncryption */

// output_data - Зашифрованные данные (выходные данные)
ErrorClass CaesarEncryption::operator() (rDataClass output_data)
{
  ErrorClass output_error = g_error_free;
  // Проверяем входные данные на ошибки
  output_error = this->CheckingForErrors(this->data_encryption, this->alphabet_encryption, this->shift_alphabet);
  // Выбираем функцию шифрования
  if (output_error == g_error_free)
  {
    if (this->alphabet_encryption == g_english_alphabet)
      output_error = this->MainEncryptionEng(this->data_encryption, this->alphabet_encryption, this->shift_alphabet, output_data);
    else
      output_error = this->MainEncryptionOther(this->data_encryption, this->alphabet_encryption, this->shift_alphabet, output_data);
  }

  return output_error;
}

/* Вх. данные:
 * data - данные, которые необходимо зашифровать. Т. к. данный метод шифрования шифрует только текст
 *       , то данные должны быть в виде текста 
 * alphabet_data  - алфавит для распознавания (шифрования) текста
 * shift_alphabet - ключ шифрования (смещение для алфавита) 
 */
// encryption_data - Зашифрованные данные (выходные данные)
  
ErrorClass CaesarEncryption::operator()(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                                       ,rDataClass output_data) const
{
  ErrorClass output_error = g_error_free;
  // Проверяем входные данные на ошибки
  output_error = this->CheckingForErrors(data, alphabet_data, shift_alphabet);
  // Выбираем функцию шифрования
  if (output_error == g_error_free)
  {
    if (alphabet_data == g_english_alphabet)
      output_error = MainEncryptionEng(data, alphabet_data, shift_alphabet, output_data);
    else
      output_error = MainEncryptionOther(data, alphabet_data, shift_alphabet, output_data);
  }

  return output_error;
}

/* Реализация методов класса CaesarEncryption */
ErrorClass CaesarEncryption::CheckingForErrors(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet) const
{
  ErrorClass output_error = g_error_free;

  // Проверка на данные, что они не заглушка
  if (data.IsDummy())
    output_error = g_caesar_encr_error_lack_data;
  if ((alphabet_data.GetSize() == 0) || (alphabet_data.IsDummy()))
    output_error |= g_caesar_encr_error_lack_alphabet;
  if (shift_alphabet == UNDEFINED_VALUE_INT16_T)
    output_error |= g_caesar_encr_error_lack_shift_alphabet;
  if (shift_alphabet > static_cast<int16_t>(alphabet_data.GetSize()))
    output_error |= g_caesar_encr_error_size_less_shift_alph;

  return output_error;
}

ErrorClass CaesarEncryption::MainEncryptionEng(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                                              ,rDataClass output_data) const
{
  ErrorClass output_error = g_error_free;

  std::string str_output;
  std::string str_in = data.GetDataStr();
  // Цикл перебора данных, которые необходимо зашифровать
  for (size_t ind = 0; ind < str_in.size(); ind++)
  {
    // Определяем порядковый номер символа в алфавите и проверяем, что он есть в алфавите
    size_t ind_symb = alphabet_data[str_in.substr(ind,1)];
    // Если данного символа нет в заданном алфавите, то проверяем в алфавите с пунктуацией
    if (ind_symb == UNDEFINED_VALUE_SIZE_T)
    {
      ind_symb = g_punctuation_alphabet[str_in.substr(ind,1)];
      // Если данного символа нет в заданном алфавите и алфавите с пунктуацией, то выводим соот. ошибку и заканчиваем шифрование
      if (ind_symb == UNDEFINED_VALUE_SIZE_T)
      {
        output_error = g_caesar_encr_error_miss_symb_in_alph;
        break;
      }
      else
        str_output += str_in.substr(ind,1);
    }
    else
    {
      // Определяем смещенный символ
      size_t ind_symb_next = UNDEFINED_VALUE_SIZE_T;
      // Определяем смещенный символ и добавляем в выходную строку
      if (ind_symb >= NUM_DIVISION_SYMBOLS)
      {
        ind_symb_next = (ind_symb-NUM_DIVISION_SYMBOLS+shift_alphabet) % alphabet_data.GetSize();
        ind_symb_next += NUM_DIVISION_SYMBOLS;
      }
      else
        ind_symb_next = (ind_symb+shift_alphabet)%alphabet_data.GetSize();
      std::string symb_shift = alphabet_data[ind_symb_next];
      str_output += symb_shift;
    }
  }
  output_data.SetDataStr(str_output);
  return output_error;
}

ErrorClass CaesarEncryption::MainEncryptionOther(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                                                ,rDataClass output_data) const
{
  ErrorClass output_error = g_error_free;

  std::string str_output;
  std::string str_in = data.GetDataStr();
  // Цикл перебора данных, которые необходимо зашифровать
  for (size_t ind = 0; ind < str_in.size();)
  {
    // Определяем подстроку (т.к. для алфавита отличных от английского один символ занимает 2 байта), поэтому
    // необходимо выделить 2 элемента из строки. Но пунктуационные символы занимают 1 байт, поэтому сначада проверяем
    // является ли выделенный символ пунктуационным.
    std::string substr = str_in.substr(ind, 1);
    size_t ind_symb = g_punctuation_alphabet[substr];
    if (ind_symb == UNDEFINED_VALUE_SIZE_T)
    {
      // Если выделенный символ не является пунктуационным, то выделяем два элемента из строки и проверяем
      // наличие выделенного символа в алфавите
      substr = str_in.substr(ind, 2);
      ind_symb = alphabet_data[substr];
      if (ind_symb == UNDEFINED_VALUE_SIZE_T)
      {
        output_error = g_caesar_encr_error_miss_symb_in_alph;
        break;
      }
      else
      {
        size_t ind_symb_next = UNDEFINED_VALUE_SIZE_T;
        // Определяем смещенный символ и добавляем в выходную строку
        if (ind_symb >= NUM_DIVISION_SYMBOLS)
        {
          ind_symb_next = (ind_symb-NUM_DIVISION_SYMBOLS+shift_alphabet) % alphabet_data.GetSize();
          ind_symb_next += NUM_DIVISION_SYMBOLS;
        }
        else
          ind_symb_next = (ind_symb+shift_alphabet)%alphabet_data.GetSize();
        std::string symb_shift = alphabet_data[ind_symb_next];
        str_output += symb_shift;
        ind += 2;
      }
    }
    else
    {
      str_output += substr;
      ind++;
    }
  }
  output_data.SetDataStr(str_output);
  return output_error;
}

ErrorClass CaesarEncryption::SetData(crDataClass data)
{
  ErrorClass output_error = g_error_free;

  // Проверка на данные, что они не заглушка
  if (data.IsDummy())
    output_error = g_caesar_encr_error_lack_data;
  else
    this->data_encryption = data;

  return output_error;
}

ErrorClass CaesarEncryption::SetAlphabet(crAlphabet alphabet)
{
  ErrorClass output_error = g_error_free;

  if ((alphabet.GetSize() == 0) || (alphabet.IsDummy()))
    output_error |= g_caesar_encr_error_lack_alphabet;
  else
    this->alphabet_encryption = alphabet;

  return output_error;
}

ErrorClass CaesarEncryption::SetAlphabetShift(int16_t shift)
{
  ErrorClass error_output = g_error_free;

  if (shift == UNDEFINED_VALUE_INT16_T)
    error_output |= g_caesar_encr_error_lack_shift_alphabet;
  if (shift > static_cast<int16_t>(this->alphabet_encryption.GetSize()))
    error_output |= g_caesar_encr_error_size_less_shift_alph;
  else
    this->shift_alphabet = shift;

  return error_output;
}

ErrorClass CaesarEncryption::Encrypt(rDataClass output_data)
{
  ErrorClass output_error = g_error_free;
  // Проверяем входные данные на ошибки
  output_error = this->CheckingForErrors(this->data_encryption, this->alphabet_encryption, this->shift_alphabet);
  // Выбираем функцию шифрования
  if (output_error == g_error_free)
  {
    if (this->alphabet_encryption == g_english_alphabet)
      output_error = this->MainEncryptionEng(this->data_encryption, this->alphabet_encryption, this->shift_alphabet, output_data);
    else
      output_error = this->MainEncryptionOther(this->data_encryption, this->alphabet_encryption, this->shift_alphabet, output_data);
  }

  return output_error;
}























