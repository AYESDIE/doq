//
// Created by ayesdie on 03/10/19.
//

#include "../document.hpp"

#ifndef DOQ_VANILLA_TOKENIZER_HPP
#define DOQ_VANILLA_TOKENIZER_HPP

namespace doq
{
class VanillaTokenizer
{
public:
  inline VanillaTokenizer();

  inline void setDocument(const Document& D);

  inline const std::string nextToken();

private:
  Document D;

  size_t seek;
};

VanillaTokenizer::VanillaTokenizer()
{
  seek = 0;
}

void VanillaTokenizer::setDocument(const Document &Doc)
{
  this->D = Doc;
  seek = 0;
}


const std::string VanillaTokenizer::nextToken()
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
