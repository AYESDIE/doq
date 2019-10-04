//
// Created by ayesdie on 02/10/19.
//

#include <bitset>
#include <string>
#include <cctype>
#include <ostream>

#ifndef DOQ_TERM_MATRIX_UNIT_HPP
#define DOQ_TERM_MATRIX_UNIT_HPP

namespace doq {
template<size_t N>
class TermMatrixUnit {
public:
  /**
   * Unit for term_matrix
   * @param term - Term to be stored.
   */
  inline TermMatrixUnit(const std::string &term);

  /**
   * Returns TermMatrixUnit.bitset.
   * @return - TermMatrixUnit.bitset
   */
  inline const std::bitset<N>& getBitset() const;

  /**
   * Returns TermMatrixUnit.term.
   * @return - TermMatrixUnit.term
   */
  inline const std::string& getTerm() const;

  inline bool operator<(const TermMatrixUnit &rhs) const;
  inline bool operator>(const TermMatrixUnit &rhs) const;
  inline bool operator<=(const TermMatrixUnit &rhs) const;
  inline bool operator>=(const TermMatrixUnit &rhs) const;
  inline auto operator[](size_t i);

  inline TermMatrixUnit<N> operator&&(const TermMatrixUnit& rhs);
  inline TermMatrixUnit<N> operator||(const TermMatrixUnit& rhs);
  inline TermMatrixUnit<N> operator!();

private:
  std::bitset<N> bitset;
  std::string term;
};

template<size_t N>
TermMatrixUnit<N>::TermMatrixUnit(const std::string &term)
{
  this->term = term;
  bitset.reset();
}

template<size_t N>
const std::bitset <N> &TermMatrixUnit<N>::getBitset() const
{
  return bitset;
}

template<size_t N>
const std::string &TermMatrixUnit<N>::getTerm() const
{
  return term;
}

template<size_t N>
bool TermMatrixUnit<N>::operator<(const TermMatrixUnit &rhs) const
{
  return term < rhs.term;
}

template<size_t N>
bool TermMatrixUnit<N>::operator>(const TermMatrixUnit &rhs) const
{
  return rhs < *this;
}

template<size_t N>
bool TermMatrixUnit<N>::operator<=(const TermMatrixUnit &rhs) const
{
  return !(rhs < *this);
}

template<size_t N>
bool TermMatrixUnit<N>::operator>=(const TermMatrixUnit &rhs) const
{
  return !(*this < rhs);
}

template<size_t N>
auto TermMatrixUnit<N>::operator[](size_t i)
{
  return bitset[i];
}

template<size_t N>
TermMatrixUnit<N> TermMatrixUnit<N>::operator&&(const TermMatrixUnit &rhs)
{
  TermMatrixUnit<N> result("(" + this->getTerm() + " AND " + rhs.getTerm() + ")");
  result.bitset = this->bitset & rhs.bitset;
  return result;
}

template<size_t N>
TermMatrixUnit<N> TermMatrixUnit<N>::operator||(const TermMatrixUnit &rhs)
{
  TermMatrixUnit<N> result("(" + this->getTerm() + " OR " + rhs.getTerm() + ")");
  result.bitset = this->bitset | rhs.bitset;
  return result;
}

template<size_t N>
TermMatrixUnit<N> TermMatrixUnit<N>::operator!()
{
  TermMatrixUnit<N> result("( NOT " + this->getTerm() + ")");
  result.bitset = ~this->bitset;
  return result;
}
}

#endif //DOQ_TERM_MATRIX_UNIT_HPP
