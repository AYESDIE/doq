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
class term_matrix_unit {
public:
  /**
   * Unit for term_matrix
   * @param term - Term to be stored.
   */
  inline term_matrix_unit(const std::string &term);

  /**
   * Returns term_matrix_unit.bitset.
   * @return - term_matrix_unit.bitset
   */
  inline const std::bitset<N>& getBitset() const;

  /**
   * Returns term_matrix_unit.term.
   * @return - term_matrix_unit.term
   */
  inline const std::string& getTerm() const;

  inline bool operator<(const term_matrix_unit &rhs) const;
  inline bool operator>(const term_matrix_unit &rhs) const;
  inline bool operator<=(const term_matrix_unit &rhs) const;
  inline bool operator>=(const term_matrix_unit &rhs) const;
  inline auto operator[](size_t i);

  inline term_matrix_unit<N> operator&&(const term_matrix_unit& rhs);
  inline term_matrix_unit<N> operator||(const term_matrix_unit& rhs);
  inline term_matrix_unit<N> operator!();

private:
  std::bitset<N> bitset;
  std::string term;
};

template<size_t N>
term_matrix_unit<N>::term_matrix_unit(const std::string &term)
{
  this->term = term;
  bitset.reset();
}

template<size_t N>
const std::bitset <N> &term_matrix_unit<N>::getBitset() const
{
  return bitset;
}

template<size_t N>
const std::string &term_matrix_unit<N>::getTerm() const
{
  return term;
}

template<size_t N>
bool term_matrix_unit<N>::operator<(const term_matrix_unit &rhs) const
{
  return term < rhs.term;
}

template<size_t N>
bool term_matrix_unit<N>::operator>(const term_matrix_unit &rhs) const
{
  return rhs < *this;
}

template<size_t N>
bool term_matrix_unit<N>::operator<=(const term_matrix_unit &rhs) const
{
  return !(rhs < *this);
}

template<size_t N>
bool term_matrix_unit<N>::operator>=(const term_matrix_unit &rhs) const
{
  return !(*this < rhs);
}

template<size_t N>
auto term_matrix_unit<N>::operator[](size_t i)
{
  return bitset[i];
}

template<size_t N>
term_matrix_unit<N> term_matrix_unit<N>::operator&&(const term_matrix_unit &rhs)
{
  term_matrix_unit<N> result("(" + this->getTerm() + " AND " + rhs.getTerm() + ")");
  result.bitset = this->bitset & rhs.bitset;
  return result;
}

template<size_t N>
term_matrix_unit<N> term_matrix_unit<N>::operator||(const term_matrix_unit &rhs)
{
  term_matrix_unit<N> result("(" + this->getTerm() + " OR " + rhs.getTerm() + ")");
  result.bitset = this->bitset | rhs.bitset;
  return result;
}

template<size_t N>
term_matrix_unit<N> term_matrix_unit<N>::operator!()
{
  term_matrix_unit<N> result("( NOT " + this->getTerm() + ")");
  result.bitset = ~this->bitset;
  return result;
}
}

#endif //DOQ_TERM_MATRIX_UNIT_HPP
