//
// Created by ayesdie on 02/10/19.
//

#include <vector>
#include <string>
#include <iostream>

#ifndef DOQ_VANILLA_POSTER_HPP
#define DOQ_VANILLA_POSTER_HPP

namespace doq
{
class VanillaPoster
{
public:
  inline VanillaPoster(const std::string& term);

  inline void addDocumentId();

  template <typename... T>
  inline void addDocumentId(const size_t& Id, const T... Ts);

  inline bool operator<(const VanillaPoster &rhs) const;
  inline bool operator>(const VanillaPoster &rhs) const;
  inline bool operator<=(const VanillaPoster &rhs) const;
  inline bool operator>=(const VanillaPoster &rhs) const;

  inline VanillaPoster operator&&(const VanillaPoster& rhs);
  inline VanillaPoster operator||(const VanillaPoster& rhs);
  inline VanillaPoster operator!();

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

VanillaPoster::VanillaPoster(const std::string &term) :
  term(term)
{
  frequency = 0;
  document_id.clear();
}

void VanillaPoster::addDocumentId()
{ /* does nothing */ }

template <typename... T>
void VanillaPoster::addDocumentId(const size_t &Id, const T... Ts)
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

VanillaPoster VanillaPoster::operator&&(const VanillaPoster& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  VanillaPoster result("(" + this->getTerm() + " AND " + rhs.getTerm() + ")");

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

VanillaPoster VanillaPoster::operator||(const VanillaPoster& rhs)
{
  auto lhsiter = this->document_id.begin();
  auto rhsiter = rhs.document_id.begin();

  VanillaPoster result("(" + this->getTerm() + " OR " + rhs.getTerm() + ")");

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

VanillaPoster VanillaPoster::operator!()
{
  VanillaPoster result("(NOT " + this->getTerm() + ")");

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

  auto VanillaPoster::operator[](const size_t &index)
{
  return document_id[index];
}

auto VanillaPoster::size()
{
  return document_id.size();
}

const std::string& VanillaPoster::getTerm() const
{
  return term;
}

size_t VanillaPoster::getFrequency() const
{
  return frequency;
}

const std::vector<size_t>& VanillaPoster::getDocumentId() const
{
  return document_id;
}

void VanillaPoster::setMaxSize(size_t maxSize)
{
  MAX_SIZE = maxSize;
}

bool VanillaPoster::operator<(const VanillaPoster &rhs) const
{
  return term < rhs.term;
}

bool VanillaPoster::operator>(const VanillaPoster &rhs) const
{
  return rhs < *this;
}

bool VanillaPoster::operator<=(const VanillaPoster &rhs) const
{
  return !(rhs < *this);
}

bool VanillaPoster::operator>=(const VanillaPoster &rhs) const
{
  return !(*this < rhs);
}
}

#endif //DOQ_VANILLA_POSTER_HPP
