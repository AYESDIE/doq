//
// Created by ayesdie on 03/10/19.
//

#include <vector>
#include <string>
#include <algorithm>
#include "document.hpp"
#include "soundex.hpp"

#ifndef DOQ_POSTING_LIST_HPP
#define DOQ_POSTING_LIST_HPP

namespace doq
{
template <typename TokenizationPolicy,
          typename PostingPolicy>
class PostingList
{
public:

  inline PostingList();

  template <typename... T>
  inline PostingList(const TokenizationPolicy& tokenizer, const Document& D, const T... Ds);

  inline void addDocument();

  template <typename... T>
  inline void addDocument(const Document& D, const T... Ds);

  inline void stat();
  inline void stat(const PostingPolicy& posting);
  inline void print();

  inline PostingPolicy operator[](const std::string& S);
  inline PostingPolicy operator[](const doq::Soundex& S);

private:
  TokenizationPolicy tokenizer;
  std::vector<PostingPolicy> list;
  std::vector<std::string> document_list;

  size_t SIZE;

  inline void addTerm(const std::string& S, const size_t& index);
};

template<typename TokenizationPolicy, typename PostingPolicy>
PostingList<TokenizationPolicy, PostingPolicy>::PostingList()
{
  SIZE = 0;
}

template<typename TokenizationPolicy, typename PostingPolicy>
template<typename... T>
PostingList<TokenizationPolicy, PostingPolicy>::PostingList(const TokenizationPolicy& tokenizer,
    const Document& D,
    const T... Ds)
{
  SIZE = 0;
  this->tokenizer = tokenizer;

  addDocument(D, Ds...);
}

template<typename TokenizationPolicy, typename PostingPolicy>
void PostingList<TokenizationPolicy, PostingPolicy>::addDocument()
{
  std::sort(list.begin(), list.end());

  for (int i = 0; i < list.size(); ++i)
  {
    list[i].setMaxSize(SIZE - 1);
  }
}

template<typename TokenizationPolicy, typename PostingPolicy>
template<typename... T>
void PostingList<TokenizationPolicy, PostingPolicy>::addDocument(const Document& D,
    const T... Ds)
{
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

template<typename TokenizationPolicy, typename PostingPolicy>
void PostingList<TokenizationPolicy, PostingPolicy>::addTerm(const std::string &S,
    const size_t &index)
{
  for (int i = 0; i < list.size(); ++i)
  {
    if (list[i].getTerm() == S)
    {
      list[i].addDocumentId(index);
      return;
    }
  }

  list.push_back(PostingPolicy(S));
  list[list.size() - 1].addDocumentId(index);
}

template<typename TokenizationPolicy, typename PostingPolicy>
void PostingList<TokenizationPolicy, PostingPolicy>::stat()
{
  std::cout << std::endl << "DOCUMENTS: ";
  for (auto q : document_list)
  {
    std::cout << std::endl << " - " + q;
  }
  std::cout << std::endl << "SIZE: " << SIZE;
}

template<typename TokenizationPolicy, typename PostingPolicy>
void PostingList<TokenizationPolicy, PostingPolicy>::print()
{
  for (auto u : list)
  {
    std::cout << std::endl << u.getTerm() << " - ";

    for (auto q : u.getDocumentId())
    {
      std::cout << q << " ";
    }
  }
}

template<typename TokenizationPolicy, typename PostingPolicy>
PostingPolicy PostingList<TokenizationPolicy, PostingPolicy>::operator[](const std::string& S)
{
  for (auto u : list)
  {
    if (u.getTerm() == S)
      return u;
  }

  PostingPolicy temp(S);
  temp.setMaxSize(SIZE - 1);
  return temp;
}

template<typename TokenizationPolicy, typename PostingPolicy>
PostingPolicy PostingList<TokenizationPolicy, PostingPolicy>::operator[](const doq::Soundex &S)
{
  PostingPolicy temp("SOUNDEX(" + S.getTerm() + ")");
  auto term = S.getSoundexTerm();

  for (auto u : list)
  {
    auto query = u.getTerm();
    Soundex::apply(query);

    if (query == term)
    {
      auto docId = u.getDocumentId();
      for (const auto &item : docId)
      {
        temp.addDocumentId(item);
      }

      return temp;
    }
  }

  temp.setMaxSize(SIZE - 1);
  return temp;
}

template<typename TokenizationPolicy, typename PostingPolicy>
void PostingList<TokenizationPolicy, PostingPolicy>::stat(const PostingPolicy &posting)
{
  std::cout << std::endl << "TERM: " << posting.getTerm();
  std::cout << std::endl << "DOCUMENT:" ;
  for (auto q : posting.getDocumentId())
  {
    std::cout << std::endl << " - " << document_list[q] ;
  }
}
}

#endif //DOQ_POSTING_LIST_HPP
