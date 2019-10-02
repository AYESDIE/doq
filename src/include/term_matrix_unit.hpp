//
// Created by ayesdie on 02/10/19.
//

#ifndef DOQ_TERM_MATRIX_UNIT_HPP
#define DOQ_TERM_MATRIX_UNIT_HPP

#include <bitset>
#include <string>
#include <cctype>

namespace doq {
template<size_t N>
class term_matrix_unit {
public:
  term_matrix_unit(const std::string &term);

  const std::bitset <N> &getUnit() const;

  const std::string &getTerm() const;

  bool operator<(const term_matrix_unit &rhs) const;

  bool operator>(const term_matrix_unit &rhs) const;

  bool operator<=(const term_matrix_unit &rhs) const;

  bool operator>=(const term_matrix_unit &rhs) const;

  auto operator[](size_t i);

private:
  std::bitset <N> unit;
  std::string term;
};

template<size_t N>
term_matrix_unit<N>::term_matrix_unit(const std::string &term)
{
  this->term = term;
  std::transform(this->term.begin(), this->term.end(), this->term.begin(),
    [](unsigned char c){ return std::tolower(c); });

  unit.reset();
}

template<size_t N>
const std::bitset <N> &term_matrix_unit<N>::getUnit() const
{
  return unit;
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
  return unit[i];
}
}

#endif //DOQ_TERM_MATRIX_UNIT_HPP
