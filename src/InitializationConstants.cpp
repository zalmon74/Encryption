#include "../include/GlobalConstants.hpp"

extern cErrorClass g_error_free = ErrorClass(); // Нет ошибок

/* Константы ошибок для класса с данными */
// В источнике данных отсутствуют данные (бит = 0)
extern cErrorClass g_data_class_error_lack_data = ErrorClass(TYPE_DATA_CLASS, std::vector<uint8_t>{0}); 
// Запрашиваются данные в виде строки, но сами данные не является строчными (не установлен флаг строки) (бит = 1)
extern cErrorClass g_data_class_error_not_string = ErrorClass(TYPE_DATA_CLASS, std::vector<uint8_t>{1});

/* Константы ошибок для класса CaesarEncryption */
// Отсутствуют данные (бит = 0) 
extern cErrorClass g_caesar_encr_error_lack_data = ErrorClass(TYPE_CAESAR_ENCRYPTION_CLASS, std::vector<uint8_t>{0});      
// Отсутствуeт алфавит (бит = 1)     
extern cErrorClass g_caesar_encr_error_lack_alphabet = ErrorClass(TYPE_CAESAR_ENCRYPTION_CLASS, std::vector<uint8_t>{1});       
// Отсутствуeт смещение алфавита (бит = 2)
extern cErrorClass g_caesar_encr_error_lack_shift_alphabet = ErrorClass(TYPE_CAESAR_ENCRYPTION_CLASS, std::vector<uint8_t>{2});
// Размер алфавита меньше значения шифра (бит = 3)
extern cErrorClass g_caesar_encr_error_size_less_shift_alph = ErrorClass(TYPE_CAESAR_ENCRYPTION_CLASS, std::vector<uint8_t>{3});
// Отсутствует опред. символ в алфавите
extern cErrorClass g_caesar_encr_error_miss_symb_in_alph = ErrorClass(TYPE_CAESAR_ENCRYPTION_CLASS, std::vector<uint8_t>{4});    

/* Различные алфавиты */

// Алфавит английского языка
extern cAlphabet g_english_alphabet(
                                    std::map<size_t, std::string>{
                                                                  {0 , "A"}, {1 , "B"}, {2 , "C"}, {3 , "D"}, {4 , "E"}
                                                                 ,{5 , "F"}, {6 , "G"}, {7 , "H"}, {8 , "I"}, {9 , "J"}
                                                                 ,{10, "K"}, {11, "L"}, {12, "M"}, {13, "N"}, {14, "O"}
                                                                 ,{15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}
                                                                 ,{20, "U"}, {21, "V"}, {22, "W"}, {23, "X"}, {24, "Y"}
                                                                 ,{25, "Z"}

                                                                 ,{100, "a"}, {101, "b"}, {102, "c"}, {103, "d"}, {104, "e"}
                                                                 ,{105, "f"}, {106, "g"}, {107, "h"}, {108, "i"}, {109, "j"}
                                                                 ,{110, "k"}, {111, "l"}, {112, "m"}, {113, "n"}, {114, "o"}
                                                                 ,{115, "p"}, {116, "q"}, {117, "r"}, {118, "s"}, {119, "t"}
                                                                 ,{120, "u"}, {121, "v"}, {122, "w"}, {123, "x"}, {124, "y"}
                                                                 ,{125, "z"}
                                                                }
                                   );

// Алфавит русского языка
extern cAlphabet g_russian_alphabet(
                                    std::map<size_t, std::string>{
                                                                  {0 , "А"}, {1 , "Б"}, {2 , "В"}, {3 , "Г"}, {4 , "Д"}
                                                                 ,{5 , "Е"}, {6 , "Ё"}, {7 , "Ж"}, {8 , "З"}, {9 , "И"}
                                                                 ,{10, "Й"}, {11, "К"}, {12, "Л"}, {13, "М"}, {14, "Н"}
                                                                 ,{15, "О"}, {16, "П"}, {17, "Р"}, {18, "С"}, {19, "Т"}
                                                                 ,{20, "У"}, {21, "Ф"}, {22, "Х"}, {23, "Ц"}, {24, "Ч"}
                                                                 ,{25, "Ш"}, {26, "Щ"}, {27, "Ъ"}, {28, "Ы"}, {29, "Ь"}
                                                                 ,{30, "Э"}, {31, "Ю"}, {32, "Я"}

                                                                 ,{100, "а"}, {101, "б"}, {102, "в"}, {103, "г"}, {104, "д"}
                                                                 ,{105, "е"}, {106, "ё"}, {107, "ж"}, {108, "з"}, {109, "и"}
                                                                 ,{110, "й"}, {111, "к"}, {112, "л"}, {113, "м"}, {114, "н"}
                                                                 ,{115, "о"}, {116, "п"}, {117, "р"}, {118, "с"}, {119, "т"}
                                                                 ,{120, "у"}, {121, "ф"}, {122, "х"}, {123, "ц"}, {124, "ч"}
                                                                 ,{125, "ш"}, {126, "щ"}, {127, "ъ"}, {128, "ы"}, {129, "ь"}
                                                                 ,{130, "э"}, {131, "ю"}, {132, "я"}
                                                                }
                                   ); 

// Алфавит со знаками препинания и символами
extern cAlphabet g_punctuation_alphabet(
                                        std::map<size_t, std::string>{
                                                                      {0 , "!"}, {1 , "\""}, {2 , "#"}, {3 , "$"}, {4 , "%"}
                                                                     ,{5 , "&"}, {6 , "\'"}, {7 , "("}, {8 , ")"}, {9 , "*"}
                                                                     ,{10, "+"}, {11, ","}, {12, "-"}, {13, "."}, {14, "/"}
                                                                     ,{15, ":"}, {16, ";"}, {17, "<"}, {18, "="}, {19, ">"}
                                                                     ,{20, "?"}, {21, "@"}, {22, "["}, {23, "]"}, {24, "^"}
                                                                     ,{25, "_"}, {26, "`"}, {27, "{"}, {28, "}"}, {29, "|"}
                                                                     ,{30, "~"}, {31, " "}, {32, "\\"}, {33, " "}
                                                                     }
                                       );
