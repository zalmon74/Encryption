#ifndef GLOBAL_CONSTANTS_HPP
#define GLOBAL_CONSTANTS_HPP

#include "ErrorClass.hpp"
#include "CipherCaesar/Alphabet.hpp"

extern cErrorClass g_error_free; // Нет ошибок

/* Константы ошибок для класса с данными */
extern cErrorClass g_data_class_error_lack_data; // В источнике данных отсутствуют данные
// Запрашиваются данные в виде строки, но сами данные не является строчными (не установлен флаг строки) (бит = 1)
extern cErrorClass g_data_class_error_not_string;

/* Константы ошибок для класса CaesarEncryption */
extern cErrorClass g_caesar_encr_error_lack_data;            // Отсутствуют данные
extern cErrorClass g_caesar_encr_error_lack_alphabet;        // Отсутствуeт алфавит
extern cErrorClass g_caesar_encr_error_lack_shift_alphabet;  // Отсутствуeт смещение алфавита
extern cErrorClass g_caesar_encr_error_size_less_shift_alph; // Размер алфавита меньше значения шифра
extern cErrorClass g_caesar_encr_error_miss_symb_in_alph;    // Отсутствует опред. символ в алфавите

/* Различные алфавиты */
extern cAlphabet g_english_alphabet;     // Алфавит английского языка
extern cAlphabet g_russian_alphabet;     // Алфавит русского языка
extern cAlphabet g_punctuation_alphabet; // Алфавит со знаками препинания и символами


#endif // GLOBAL_CONSTANTS_HPP
