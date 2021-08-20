#include "../../include/CipherCaesar/Alphabet.hpp"
#include "../../include/MyStdTypedef.hpp"

/* Реализация конструкторов класса Alphabet */

Alphabet::Alphabet()
{
  /* 
   * Так как при создании объекта через конструктор без аргументов создается пустышка, 
   * то все поля устанавливается в неизвестное значение, кроме соот. флага
   */
  this->size_alphabet       = UNDEFINED_VALUE_SIZE_T;
  this->ind_start_lowercase = UNDEFINED_VALUE_SIZE_T;
  this->ind_end_lowercase   = UNDEFINED_VALUE_SIZE_T;   
  this->ind_start_uppercase = UNDEFINED_VALUE_SIZE_T; 
  this->ind_end_uppercase   = UNDEFINED_VALUE_SIZE_T;

  this->f_dummy = true;
}

Alphabet::Alphabet(const std::map<size_t, std::string>& input_map)
{
  this->size_alphabet       = UNDEFINED_VALUE_SIZE_T;
  this->ind_start_lowercase = UNDEFINED_VALUE_SIZE_T;
  this->ind_end_lowercase   = UNDEFINED_VALUE_SIZE_T;   
  this->ind_start_uppercase = UNDEFINED_VALUE_SIZE_T; 
  this->ind_end_uppercase   = UNDEFINED_VALUE_SIZE_T;
  
  if (input_map.size() != 0)
  {
    this->ind_start_uppercase = input_map.begin()->first;
    for (auto& el : input_map)
    {
      this->alph_ind_symb[el.first]  = el.second;
      this->alph_symb_ind[el.second] = el.first;
      // Если выполняется условие, то значит начались строчные буквы
      if (el.first >= (this->ind_start_uppercase+100))
      {
        // Если индекс прописных букв не установлен, значит это первая итерация с ними
        if (this->ind_start_lowercase == UNDEFINED_VALUE_SIZE_T)
          this->ind_start_lowercase = el.first;
        else // Если индекс начала прописных букв установлен, то устнавливаем индекс конца. Перезапись происходит до конца цикла
          this->ind_end_lowercase = el.first;
      }
      else
        this->ind_end_uppercase = el.first;
    }
  }

  // Устанавливаем размер алфавита и флаг заглушки убираем
  this->size_alphabet = input_map.size()/2;
  this->f_dummy = false;
}

Alphabet::Alphabet(const Alphabet& other)
{
  this->alph_ind_symb       = other.alph_ind_symb;
  this->alph_symb_ind       = other.alph_symb_ind; 
  this->size_alphabet       = other.size_alphabet;       
  this->ind_start_lowercase = other.ind_start_lowercase;  
  this->ind_end_lowercase   = other.ind_end_lowercase;   
  this->ind_start_uppercase = other.ind_start_uppercase;  
  this->ind_end_uppercase   = other.ind_end_uppercase;   
  this->f_dummy             = other.f_dummy; 
}

/* Перегрузка операторов класса Alphabet */

Alphabet& Alphabet::operator= (const Alphabet& other)
{
  this->Clear();

  this->alph_ind_symb       = other.alph_ind_symb;
  this->alph_symb_ind       = other.alph_symb_ind; 
  this->size_alphabet       = other.size_alphabet;       
  this->ind_start_lowercase = other.ind_start_lowercase;  
  this->ind_end_lowercase   = other.ind_end_lowercase;   
  this->ind_start_uppercase = other.ind_start_uppercase;  
  this->ind_end_uppercase   = other.ind_end_uppercase;   
  this->f_dummy             = other.f_dummy; 

  return *this;
}

std::string Alphabet::operator[] (const size_t& ind) const
{
  std::string output;
  
  if (!this->f_dummy && (this->size_alphabet != 0))
  {
    // Ищем данный элемент во внутреннем мапе
    auto it = this->alph_ind_symb.find(ind);
    // Если данный элемент имеется во внутреннем мапе, то берем его от туда
    if (it != this->alph_ind_symb.end())
      output = it->second;
  }
  return output;
}

std::size_t Alphabet::operator[] (const std::string& symb) const
{
  std::size_t output = UNDEFINED_VALUE_SIZE_T;
  
  if (!this->f_dummy && (this->size_alphabet != 0))
  {
    // Ищем данный элемент во внутреннем мапе
    auto it = this->alph_symb_ind.find(symb);
    // Если данный элемент имеется во внутреннем мапе, то берем его от туда
    if (it != this->alph_symb_ind.end())
      output = it->second;
  }
  return output;
}

bool Alphabet::operator== (const Alphabet& other) const
{
  return (
          (this->alph_ind_symb       == other.alph_ind_symb      ) &&
          (this->alph_symb_ind       == other.alph_symb_ind      ) &&
          (this->size_alphabet       == other.size_alphabet      ) &&
          (this->ind_start_lowercase == other.ind_start_lowercase) &&
          (this->ind_end_lowercase   == other.ind_end_lowercase  ) &&
          (this->ind_start_uppercase == other.ind_start_uppercase) &&
          (this->ind_end_uppercase   == other.ind_end_uppercase  ) &&
          (this->f_dummy             == other.f_dummy            )
         );
}

/* Методы класса Alphabet */

// Метод отсчитски алфавита
void Alphabet::Clear()
{
  this->alph_ind_symb.clear();
  this->alph_symb_ind.clear();
   
  this->size_alphabet       = UNDEFINED_VALUE_SIZE_T;       
  this->ind_start_lowercase = UNDEFINED_VALUE_SIZE_T;  
  this->ind_end_lowercase   = UNDEFINED_VALUE_SIZE_T;   
  this->ind_start_uppercase = UNDEFINED_VALUE_SIZE_T;  
  this->ind_end_uppercase   = UNDEFINED_VALUE_SIZE_T;   
  this->f_dummy             = true; 
}
