//
// Created by ayesdie on 05/10/19.
//

#ifndef DOQ_SOUNDEX_HPP
#define DOQ_SOUNDEX_HPP

namespace doq
{
class Soundex
{
public:
  inline Soundex(const std::string& S);

  inline const std::string &getTerm() const;

  inline static void apply(std::string& S);


private:
  std::string term;

  inline static char soundexIndexer(const char& s);
};

Soundex::Soundex(const std::string &S) :
  term(S)
{
  apply(term);
}

const std::string &Soundex::getTerm() const
{
  return term;
}

void Soundex::apply(std::string &S)
{
  if (S.empty())
    throw std::logic_error("Empty string used for Soundex.");

  std::string temp;

  for (auto s : S)
  {
    temp += soundexIndexer(s);
  }

  temp[0] = S[0];


  for (size_t i = 0; i < temp.size() - 1; ++i)
  {
    if (temp[i] == temp[i + 1])
      temp.erase(i + 1, 1);
  }

  for (size_t i = 0; i < temp.size(); ++i)
  {
    if ((temp[i] == '0') || (temp[i] == '7'))
      temp.erase(i, 1);
  }

  for (size_t i = temp.size(); i < 4; ++i)
  {
    temp += '0';
  }

  S = temp;
}

char Soundex::soundexIndexer(const char &s)
{
  if ((s == 'a') ||
      (s == 'e') ||
      (s == 'i') ||
      (s == 'o') ||
      (s == 'u') ||
      (s == 'h') ||
      (s == 'w') ||
      (s == 'y') ||
      (s == 'A') ||
      (s == 'E') ||
      (s == 'I') ||
      (s == 'O') ||
      (s == 'U') ||
      (s == 'H') ||
      (s == 'W') ||
      (s == 'Y'))
  {
    return '0';
  }

  else if ((s == 'b') ||
      (s == 'f') ||
      (s == 'p') ||
      (s == 'v') ||
      (s == 'B') ||
      (s == 'F') ||
      (s == 'P') ||
(s == 'V'))
  {
    return '1';
  }

  else if((s == 'c') ||
      (s == 'g') ||
      (s == 'j') ||
      (s == 'k') ||
      (s == 'q') ||
      (s == 's') ||
      (s == 'x') ||
      (s == 'z') ||
      (s == 'C') ||
      (s == 'G') ||
      (s == 'J') ||
      (s == 'K') ||
      (s == 'Q') ||
      (s == 'S') ||
      (s == 'X') ||
      (s == 'Z'))
  {
    return '2';
  }

  else if ((s == 'd') ||
      (s == 't') ||
      (s == 'D') ||
      (s == 'T'))
  {
    return '3';
  }

  else if ((s == 'l') ||
      (s == 'L'))
  {
    return '4';
  }

  else if ((s == 'm') ||
      (s == 'n') ||
      (s == 'M') ||
      (s == 'N'))
  {
    return '5';
  }

  else if ((s == 'r') ||
      (s == 'R'))
  {
    return '6';
  }

  return '7';
}
}

#endif //DOQ_SOUNDEX_HPP
