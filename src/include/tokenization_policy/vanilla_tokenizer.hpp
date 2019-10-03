//
// Created by ayesdie on 03/10/19.
//

#include "../document.hpp"

#ifndef DOQ_VANILLA_TOKENIZER_HPP
#define DOQ_VANILLA_TOKENIZER_HPP

namespace doq
{
class vanilla_tokenizer
{
public:
  inline vanilla_tokenizer();

  inline void setDocument(const document& D);

  inline const std::string nextToken();

private:
  document D;

  size_t seek;
};

vanilla_tokenizer::vanilla_tokenizer()
{
  seek = 0;
}

void vanilla_tokenizer::setDocument(const document &Doc)
{
  this->D = Doc;
  seek = 0;
}


const std::string vanilla_tokenizer::nextToken()
{
  if (seek >= D.size())
    return std::string("\0");

  std::string result;
  
  while (!((D[seek] == ' ') ||
         (D[seek] == '.') ||
         (D[seek] == ',') ||
         (D[seek] == ';') ||
         (D[seek] == '\'') ||
         (D[seek] == '"') ||
         (D[seek] == '(') ||
         (D[seek] == ')') ||
         (D[seek] == '!') ||
         (D[seek] == '-') ||
         (D[seek] == ':') ||
         (D[seek] == '0') ||
         (D[seek] == '\n') ||
         (D[seek] == '\t') ||
         (D[seek] == '\0')))
  {
    result += D[seek];
    seek++;
  }

  seek++;
  return (result.empty() ? nextToken() : result);
}
}

#endif //DOQ_VANILLA_TOKENIZER_HPP
