//
// Created by ayesdie on 02/10/19.
//

#include <vector>
#include <string>
#include <iostream>

#ifndef DOQ_VANILLA_POSTING_HPP
#define DOQ_VANILLA_POSTING_HPP

namespace doq
{
class vanilla_posting
{
public:
  inline vanilla_posting(const std::string& term);

  inline void addDocumentId();

  template <typename... T>
  inline void addDocumentId(const size_t& Id, const T... Ts);

  inline std::vector<size_t> operator&&(const vanilla_posting& rhs);
  inline std::vector<size_t> operator||(const vanilla_posting& rhs);

  inline const std::string& getTerm() const;
  inline size_t getFrequency() const;
  inline const std::vector<size_t>& getDocumentId() const;

private:
  std::string term;
  size_t frequency;
  std::vector<size_t> document_id;
};

vanilla_posting::vanilla_posting(const std::string &term) :
  term(term)
{
  frequency = 0;
  document_id.clear();
}

void vanilla_posting::addDocumentId()
{ /* does nothing */ }

template <typename... T>
void vanilla_posting::addDocumentId(const size_t &Id, const T... Ts)
{
  if (document_id.empty())
  {
    frequency++;
    document_id.push_back(Id);
  }
  else if (*(document_id.end() - 1) < Id)
  {
    frequency++;
    document_id.push_back(Id);
  }

  addDocumentId(Ts...);
}

std::vector<size_t> vanilla_posting::operator&&(const vanilla_posting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  std::vector<size_t> result;

  while ((lhsiter != this->document_id.end()) && (rhsiter != rhs.document_id.end()))
  {
    if (*lhsiter == *rhsiter)
    {
      result.push_back(*lhsiter);
      lhsiter++;
      rhsiter++;
    }
    else if (*lhsiter < *rhsiter)
    {
      lhsiter++;
    }
    else if (*lhsiter > *rhsiter)
    {
      rhsiter++;
    }
  }


  return result;
}

std::vector<size_t> vanilla_posting::operator||(const vanilla_posting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  std::vector<size_t> result;

  while ((lhsiter != this->document_id.end()) && (rhsiter != rhs.document_id.end()))
  {
    if (*lhsiter == *rhsiter)
    {
      result.push_back(*lhsiter);
      lhsiter++;
      rhsiter++;
    }
    else if (*lhsiter < *rhsiter)
    {
      result.push_back(*lhsiter);
      lhsiter++;
    }
    else if (*lhsiter > *rhsiter)
    {
      result.push_back(*rhsiter);
      rhsiter++;
    }
  }

  if (*(result.end() - 1) == *(this->document_id.end() - 1))
  {
    while (rhsiter != rhs.document_id.end())
    {
      result.push_back(*rhsiter);
      rhsiter++;
    }
  }
  else
  {
    while (lhsiter != this->document_id.end())
    {
      result.push_back(*lhsiter);
      lhsiter++;
    }
  }

  return result;
}

const std::string& vanilla_posting::getTerm() const
{
  return term;
}

size_t vanilla_posting::getFrequency() const
{
  return frequency;
}

const std::vector<size_t>& vanilla_posting::getDocumentId() const
{
  return document_id;
}
}

#endif //DOQ_VANILLA_POSTING_HPP
