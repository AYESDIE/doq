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

  inline bool operator<(const vanilla_posting &rhs) const;
  inline bool operator>(const vanilla_posting &rhs) const;
  inline bool operator<=(const vanilla_posting &rhs) const;
  inline bool operator>=(const vanilla_posting &rhs) const;

  inline vanilla_posting operator&&(const vanilla_posting& rhs);
  inline vanilla_posting operator||(const vanilla_posting& rhs);
  inline vanilla_posting operator!();

  inline auto operator[](const size_t& index);
  inline auto size();

  inline const std::string& getTerm() const;
  inline size_t getFrequency() const;
  inline const std::vector<size_t>& getDocumentId() const;

  inline void setMaxSize(size_t maxSize);

private:
  std::string term;
  size_t frequency;
  std::vector<size_t> document_id;

  size_t MAX_SIZE;
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
  MAX_SIZE = *(document_id.end() - 1);
}

vanilla_posting vanilla_posting::operator&&(const vanilla_posting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  vanilla_posting result("(" + this->getTerm() + " AND " + rhs.getTerm() + ")");

  while ((lhsiter != this->document_id.end()) && (rhsiter != rhs.document_id.end()))
  {
    if (*lhsiter == *rhsiter)
    {
      result.addDocumentId(*lhsiter);
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

vanilla_posting vanilla_posting::operator||(const vanilla_posting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  vanilla_posting result("(" + this->getTerm() + " OR " + rhs.getTerm() + ")");

  while ((lhsiter != this->document_id.end()) && (rhsiter != rhs.document_id.end()))
  {
    if (*lhsiter == *rhsiter)
    {
      result.addDocumentId(*lhsiter);
      lhsiter++;
      rhsiter++;
    }
    else if (*lhsiter < *rhsiter)
    {
      result.addDocumentId(*lhsiter);
      lhsiter++;
    }
    else if (*lhsiter > *rhsiter)
    {
      result.addDocumentId(*rhsiter);
      rhsiter++;
    }
  }

  if (*(result.getDocumentId().end() - 1) == *(this->document_id.end() - 1))
  {
    while (rhsiter != rhs.document_id.end())
    {
      result.addDocumentId(*rhsiter);
      rhsiter++;
    }
  }
  else
  {
    while (lhsiter != this->document_id.end())
    {
      result.addDocumentId(*lhsiter);
      lhsiter++;
    }
  }

  return result;
}

vanilla_posting vanilla_posting::operator!()
{
  vanilla_posting result("(NOT " + this->getTerm() + ")");

  auto iter = this->getDocumentId().begin();

  for (size_t i = 0; i <= MAX_SIZE; ++i)
  {
    if (i == *iter)
    {
      iter++;
    }
    else
    {
      result.addDocumentId(i);
    }
  }

  return result;
}

  auto vanilla_posting::operator[](const size_t &index)
{
  return document_id[index];
}

auto vanilla_posting::size()
{
  return document_id.size();
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

void vanilla_posting::setMaxSize(size_t maxSize)
{
  MAX_SIZE = maxSize;
}

bool vanilla_posting::operator<(const vanilla_posting &rhs) const {
  return term < rhs.term;
}

bool vanilla_posting::operator>(const vanilla_posting &rhs) const {
  return rhs < *this;
}

bool vanilla_posting::operator<=(const vanilla_posting &rhs) const {
  return !(rhs < *this);
}

bool vanilla_posting::operator>=(const vanilla_posting &rhs) const {
  return !(*this < rhs);
}
}

#endif //DOQ_VANILLA_POSTING_HPP
