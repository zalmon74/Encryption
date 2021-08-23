#ifndef CIPHER_CAESAR_HPP
#define CIPHER_CAESAR_HPP

#include "Alphabet.hpp"
#include "../DataClass.hpp"
#include "../ErrorClass.hpp"

class CaesarEncryption
{
private:

  DataClass data_encryption;     // Данные, которые необходимо зашифровать
  Alphabet  alphabet_encryption; // Алфавит данных, которые необходимо зашифровать
  int16_t   shift_alphabet;      // Смещения алфавита для шифрования данных

  /* Методы */
  /* Метод порверки данных на ошибки */
  /* Вх. данные:
   * data - данные, которые необходимо зашифровать. Т. к. данный метод шифрования шифрует только текст
   *       , то данные должны быть в виде текста
   * alphabet_data  - алфавит для распознавания (шифрования) текста
   * shift_alphabet - ключ шифрования (смещение для алфавита)
  */
  // output_data - Зашифрованные данные (выходные данные)
  ErrorClass CheckingForErrors  (crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet) const;
  ErrorClass MainEncryptionEng  (crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                                ,rDataClass output_data) const;
  ErrorClass MainEncryptionOther(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                                ,rDataClass output_data) const;

public:

  static cUInt16_t TYPE_CLASS = TYPE_CAESAR_ENCRYPTION_CLASS;

  /* Конструкторы */
  
  CaesarEncryption() { this->shift_alphabet = UNDEFINED_VALUE_INT16_T; };
  /* Вх. данные:
   * data - данные, которые необходимо зашифровать. Т. к. данный метод шифрования шифрует только текст
   *       , то данные должны быть в виде текста 
   * alphabet_data  - алфавит для распознавания (шифрования) текста
   * shift_alphabet - ключ шифрования (смещение для алфавита) 
  */
  CaesarEncryption(crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet);

  /* Операторы */

  // output_data - Зашифрованные данные (выходные данные)
  ErrorClass operator() (rDataClass output_data);
  /* Вх. данные:
   * data - данные, которые необходимо зашифровать. Т. к. данный метод шифрования шифрует только текст
   *       , то данные должны быть в виде текста 
   * alphabet_data  - алфавит для распознавания (шифрования) текста
   * shift_alphabet - ключ шифрования (смещение для алфавита) 
  */
  // output_data - Зашифрованные данные (выходные данные)
  ErrorClass operator() (crDataClass data, crAlphabet alphabet_data, int16_t shift_alphabet
                        ,rDataClass output_data) const;

  /* Методы */

  ErrorClass SetData(crDataClass data);
  ErrorClass SetAlphabet(crAlphabet alphabet);
  ErrorClass SetAlphabetShift(int16_t shift);

  DataClass GetData()                { return this->data_encryption;   }
  Alphabet  GetAlphabet()      const { return this->alphabet_encryption; }
  int16_t   GetShiftAlphabet() const { return this->shift_alphabet;      }

  ErrorClass Encrypt(rDataClass output_data);

};

typedef       CaesarEncryption* pCaesarEncryption;
typedef       CaesarEncryption& rCaesarEncryption;
typedef const CaesarEncryption  cCaesarEncryption;
typedef const CaesarEncryption* cpCaesarEncryption;
typedef CaesarEncryption* const pcCaesarEncryption;
typedef const CaesarEncryption* const cpcCaesarEncryption;
typedef const CaesarEncryption& crCaesarEncryption;

#endif // CIPHER_CAESAR_HPP
