//
// Created by ayesdie on 28/09/19.
//

#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include "term_matrix_unit.hpp"
#include "document.hpp"
#include "wildcard.hpp"

#ifndef DOQ_TERM_MATRIX_HPP
#define DOQ_TERM_MATRIX_HPP

namespace doq
{
template <typename TokenizationPolicy,
          size_t N>
class TermMatrix
{
public:
  inline TermMatrix();

  /**
   * Parameterized constructor for TermMatrix.
   *
   * @param D - doq::document
   * @param Ds - variadic doq::document
   */
  template <typename... I>
  inline TermMatrix(TokenizationPolicy tokenizer, const Document& D, const I... Ds);

  /**
   * Adds document to TermMatrix.
   *
   * @param D - doq::document
   * @param Ds - variadic doq::document
   */
  template <typename... T>
  inline void addDocument(const Document& D, const T... Ds);

  /**
   * Display stats for TermMatrix.
   */
  inline void stat();

  /**
   * Display stat for given bitset.
   * @param bitset - Query
   */
  inline void stat(const TermMatrixUnit<N>& bitset);

  /**
   * Display TermMatrix.
   */
  inline void showMatrix();

  inline TermMatrixUnit<N> operator[](const std::string& S);
  inline TermMatrixUnit<N> operator[](const Soundex& S);
  inline TermMatrixUnit<N> operator[](const Wildcard& W);

private:
  TokenizationPolicy tokenizer;
  std::vector<doq::TermMatrixUnit<N>> matrix;
  std::vector<std::string> document_list;

  size_t MAX_SIZE;
  size_t SIZE;

  inline void addDocument();

  inline void addTerm(const std::string& S, const size_t& index);

  inline size_t documentIndex(const std::string& documentName);
};

template <typename TokenizationPolicy,
          size_t N>
TermMatrix<TokenizationPolicy, N>::TermMatrix()
{
  MAX_SIZE = N;
  SIZE = 0;
}

template <typename TokenizationPolicy,
          size_t N>
template<typename... I>
TermMatrix<TokenizationPolicy, N>::TermMatrix(TokenizationPolicy tokenizer,
    const Document& D,
    const I... Ds)
{
  MAX_SIZE = N;
  SIZE = 0;

  this->tokenizer = tokenizer;

  addDocument(D, Ds...);
}

template <typename TokenizationPolicy,
          size_t N>
void TermMatrix<TokenizationPolicy, N>::addDocument()
{
  std::sort(matrix.begin(), matrix.end());
}

template <typename TokenizationPolicy,
          size_t N>
template<typename... T>
void TermMatrix<TokenizationPolicy, N>::addDocument(const Document& D, const T... Ds)
{
  if (SIZE == MAX_SIZE)
    return;

  document_list.push_back(D.getFileName());
  tokenizer.setDocument(D);

  std::string term = tokenizer.nextToken();
  while (term != "\0")
  {
    addTerm(term, SIZE);
    term = tokenizer.nextToken();
  }

  SIZE++;
  addDocument(Ds...);
}

template <typename TokenizationPolicy,
          size_t N>
void TermMatrix<TokenizationPolicy, N>::addTerm(const std::string& S, const size_t& index)
{
  for (int i = 0; i < matrix.size(); ++i)
  {
    if(matrix[i].getTerm() == S)
    {
      matrix[i][index] = true;
      return;
    }
  }

  matrix.push_back(doq::TermMatrixUnit<N>(S));
  matrix[matrix.size() - 1][index] = true;
}

template <typename TokenizationPolicy,
          size_t N>
size_t TermMatrix<TokenizationPolicy, N>::documentIndex(const std::string &documentName)
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

template <typename TokenizationPolicy,
          size_t N>
void TermMatrix<TokenizationPolicy, N>::stat()
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

template <typename TokenizationPolicy,
          size_t N>
TermMatrixUnit<N> TermMatrix<TokenizationPolicy, N>::operator[](const std::string &S)
{
  for (auto unit : matrix)
  {
    if (unit.getTerm() == S)
      return unit;
  }

  return TermMatrixUnit<N>("");
}

template<typename TokenizationPolicy, size_t N>
TermMatrixUnit<N> TermMatrix<TokenizationPolicy, N>::operator[](const Soundex &S)
{
  TermMatrixUnit<N> result("SOUNDEX(" + S.getTerm() +")");
  auto term = S.getSoundexTerm();

  for (auto unit : matrix)
  {
    auto query = unit.getTerm();
    Soundex::apply(query);

    if (query == term)
    {
      for (size_t i = 0; i < N; ++i)
      {
        result[i] = unit[i];
      }
      return result;
    }
  }

  return result;
}

template<typename TokenizationPolicy, size_t N>
TermMatrixUnit<N> TermMatrix<TokenizationPolicy, N>::operator[](const Wildcard &W)
{
  TermMatrixUnit<N> result("WILDCARD(" + W.getTerm() + ")");

  for (auto unit : matrix)
  {
    auto term = unit.getTerm();

    if (W.check(term))
    {
      for (size_t i = 0; i < N; ++i)
      {
        result[i] = unit[i];
      }
      return result;
    }
  }

  return result;
}

template <typename TokenizationPolicy, size_t N>
void TermMatrix<TokenizationPolicy, N>::showMatrix()
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

template <typename TokenizationPolicy,
          size_t N>
void TermMatrix<TokenizationPolicy, N>::stat(const TermMatrixUnit<N>& unit)
{
  std::cout << std::endl << "TERM: " << unit.getTerm();
  std::cout << std::endl << "DOCUMENT:";
  for (size_t i = 0; i < unit.getBitset().size(); ++i)
  {
    if (unit.getBitset()[i])
      std::cout << std::endl << " - " + document_list[i];
  }
}
}

#endif //DOQ_TERM_MATRIX_HPP
