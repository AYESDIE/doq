//
// Created by ayesdie on 28/09/19.
//

#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include "term_matrix_unit.hpp"
#include "document.hpp"

#ifndef DOQ_TERM_MATRIX_HPP
#define DOQ_TERM_MATRIX_HPP

namespace doq
{
template <size_t N>
class term_matrix
{
public:
  term_matrix();

  template <typename... I>
  term_matrix(const doq::document& D, const I... Ds);

  template <typename... T>
  void addDocument(const doq::document& D, const T... Ds);

  void stat();
  void stat(std::bitset<N> bitset);
  void showMatrix();

  auto operator[](const std::string& S);

private:
  std::vector<doq::term_matrix_unit<N>> matrix;
  std::vector<std::string> document_list;

  size_t MAX_SIZE;
  size_t SIZE;

  void addDocument();

  void addTerm(const std::string& S, const size_t& index);

  size_t documentIndex(const std::string& documentName);
};

template<size_t N>
term_matrix<N>::term_matrix()
{
  MAX_SIZE = N;
  SIZE = 0;
}

template<size_t N>
template<typename... I>
term_matrix<N>::term_matrix(const doq::document& D, const I... Ds)
{
  MAX_SIZE = N;
  SIZE = 0;

  addDocument(D, Ds...);
}

template<size_t N>
void term_matrix<N>::addDocument()
{
  std::sort(matrix.begin(), matrix.end());
}

template<size_t N>
template<typename... T>
void term_matrix<N>::addDocument(const doq::document& D, const T... Ds)
{
  if (SIZE == MAX_SIZE)
    return;

  document_list.push_back(D.getFileName());

  std::string term;
  term.clear();

  for (auto ch : D)
  {
    if ((ch == ' ') ||
        (ch == '.') ||
        (ch == ',') ||
        (ch == ';') ||
        (ch == '\'') ||
        (ch == '"') ||
        (ch == '(') ||
        (ch == ')') ||
        (ch == '!') ||
        (ch == '-') ||
        (ch == ':') ||
        (ch == '0') ||
        (ch == '\n') ||
        (ch == '\t') ||
        (ch == '\0'))
    {
      if (!term.empty())
      {
        addTerm(term, SIZE);
        term.clear();
      }
    }
    else
    {
      term += ch;
    }
  }
  addTerm(term, SIZE);

  SIZE++;
  addDocument(Ds...);
}

template<size_t N>
void term_matrix<N>::addTerm(const std::string& S, const size_t& index)
{
  for (int i = 0; i < matrix.size(); ++i)
  {
    if(matrix[i].getTerm() == S)
    {
      matrix[i][index] = true;
      return;
    }
  }

  matrix.push_back(doq::term_matrix_unit<N>(S));
  matrix[matrix.size() - 1][index] = true;
}

template<size_t N>
size_t term_matrix<N>::documentIndex(const std::string &documentName)
{
  size_t index = 0;
  for (auto docName : document_list)
  {
    if (docName == documentName)
      return index;

    index++;
  }

  return -1;
}

template<size_t N>
void term_matrix<N>::stat()
{
  std::cout << std::endl << "MAX_SIZE: " << MAX_SIZE;
  std::cout << std::endl << "SIZE: " << SIZE;
  std::cout << std::endl << "DOCUMENTS: " << SIZE;

  for (auto document : document_list)
  {
    std::cout << std::endl << "  - " << document;
  }

  std::cout << std::endl << "DISTINCT TERMS: " << matrix.size();
}

template<size_t N>
auto term_matrix<N>::operator[](const std::string &S)
{
  for (auto unit : matrix)
  {
    if (unit.getTerm() == S)
      return unit.getBitset();
  }

  std::bitset<N> temp;
  temp.reset();
  return temp;
}

template<size_t N>
void term_matrix<N>::showMatrix()
{
  std::cout << std::endl;
  for (auto unit : matrix)
  {
    for (int i = 0; i < unit.getBitset().size(); ++i)
    {
      std::cout << unit[i] << " ";
    }
    std::cout << unit.getTerm() << std::endl;
  }
}

template<size_t N>
void term_matrix<N>::stat(std::bitset<N> bitset)
{
  std::cout << std::endl << "DOCUMENT:";
  for (size_t i = 0; i < bitset.size(); ++i)
  {
    if (bitset[i])
      std::cout << std::endl << " - " + document_list[i];
  }
}
}

#endif //DOQ_TERM_MATRIX_HPP
