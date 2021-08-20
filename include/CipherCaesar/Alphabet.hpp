#ifndef ALPHABET_HPP
#define ALPHABET_HPP

#include <map>
#include <string>

/*
 * Данный класс содержит в себе алфавит. Для разделения прописных и строчных букв необходимо
 * при создании класса разделить их в map, хотябы на 100 (между первым прописным и строчным символом).
 * Также необходим следующий порядок: сначала идут прописные буквы, затем строчные
*/

class Alphabet
{
private:

  std::map<size_t, std::string> alph_ind_symb; // Алфавит в котором в качестве ключа индекса, а данными сам символ
  std::map<std::string, size_t> alph_symb_ind; // Алфавит в котором в качестве ключа символ, а данными сам индекс

  size_t size_alphabet;       // Размер алфавита
  size_t ind_start_lowercase; // Индекс начала строчных букв 
  size_t ind_end_lowercase;   // Индекс конца строчных букв
  size_t ind_start_uppercase; // Индекс начала прописных букв 
  size_t ind_end_uppercase;   // Индекс конца прописных букв

  bool f_dummy; // Флаг пустышки (заглушки)

  /* Метод отчистки всех данных */
  void Clear();

public:

  /* Конструкторы */
  
  Alphabet();
  Alphabet(const std::map<size_t, std::string>& input_map);
  Alphabet(const Alphabet& other);

  /* Перегрузка операторов */

  Alphabet&   operator=  (const Alphabet& other);
  std::string operator[] (const size_t& ind)       const;
  size_t      operator[] (const std::string& symb) const;
  bool        operator== (const Alphabet& other)   const;

  /* Методы */

  size_t GetSize() const { return this->size_alphabet; }
  // Метод получения индекса начала (first) и конца (second) строчных букв в алфавите
  std::pair<size_t, size_t> GetIndLowercase() const { return std::pair<size_t, size_t>(this->ind_start_lowercase, this->ind_end_lowercase); } 
  // Метод получения индекса начала (first) и конца (second) прописных букв в алфавите
  std::pair<size_t, size_t> GetIndUppercase() const { return std::pair<size_t, size_t>(this->ind_start_uppercase, this->ind_end_uppercase); }


  // Метод определения заглушки
  bool IsDummy() const { return this->f_dummy; }

};

typedef       Alphabet* pAlphabet;
typedef       Alphabet& rAlphabet;
typedef const Alphabet  cAlphabet;
typedef const Alphabet* cpAlphabet;
typedef Alphabet* const pcAlphabet;
typedef const Alphabet* const cpcAlphabet;
typedef const Alphabet& crAlphabet;

#endif // ALPHABET_HPP
