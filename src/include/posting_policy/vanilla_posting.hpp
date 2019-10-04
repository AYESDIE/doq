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
class VanillaPosting
{
public:
  inline VanillaPosting(const std::string& term);

  inline void addDocumentId();

  template <typename... T>
  inline void addDocumentId(const size_t& Id, const T... Ts);

  inline bool operator<(const VanillaPosting &rhs) const;
  inline bool operator>(const VanillaPosting &rhs) const;
  inline bool operator<=(const VanillaPosting &rhs) const;
  inline bool operator>=(const VanillaPosting &rhs) const;

  inline VanillaPosting operator&&(const VanillaPosting& rhs);
  inline VanillaPosting operator||(const VanillaPosting& rhs);
  inline VanillaPosting operator!();

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

VanillaPosting::VanillaPosting(const std::string &term) :
  term(term)
{
  frequency = 0;
  document_id.clear();
}

void VanillaPosting::addDocumentId()
{ /* does nothing */ }

template <typename... T>
void VanillaPosting::addDocumentId(const size_t &Id, const T... Ts)
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

VanillaPosting VanillaPosting::operator&&(const VanillaPosting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  VanillaPosting result("(" + this->getTerm() + " AND " + rhs.getTerm() + ")");

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

VanillaPosting VanillaPosting::operator||(const VanillaPosting& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  VanillaPosting result("(" + this->getTerm() + " OR " + rhs.getTerm() + ")");

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

VanillaPosting VanillaPosting::operator!()
{
  VanillaPosting result("(NOT " + this->getTerm() + ")");

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

  auto VanillaPosting::operator[](const size_t &index)
{
  return document_id[index];
}

auto VanillaPosting::size()
{
  return document_id.size();
}

const std::string& VanillaPosting::getTerm() const
{
  return term;
}

size_t VanillaPosting::getFrequency() const
{
  return frequency;
}

const std::vector<size_t>& VanillaPosting::getDocumentId() const
{
  return document_id;
}

void VanillaPosting::setMaxSize(size_t maxSize)
{
  MAX_SIZE = maxSize;
}

bool VanillaPosting::operator<(const VanillaPosting &rhs) const {
  return term < rhs.term;
}

bool VanillaPosting::operator>(const VanillaPosting &rhs) const {
  return rhs < *this;
}

bool VanillaPosting::operator<=(const VanillaPosting &rhs) const {
  return !(rhs < *this);
}

bool VanillaPosting::operator>=(const VanillaPosting &rhs) const {
  return !(*this < rhs);
}
}

#endif //DOQ_VANILLA_POSTING_HPP
