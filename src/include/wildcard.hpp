//
// Created by ayesdie on 18/10/19.
//

#ifndef DOQ_WILDCARD_HPP
#define DOQ_WILDCARD_HPP

namespace doq
{
class Wildcard
{
public:
  inline Wildcard(const std::string& term);

  inline const std::string &getTerm() const;
  inline const std::string &getWildcardTerm() const;

  inline bool check(const std::string& query) const;

private:
  std::string term;
  std::string wildcardTerm;
  size_t stars;

  inline void modulate();
};

Wildcard::Wildcard(const std::string& term) :
    term(term)
{
  stars = 0;
  modulate();
}

const std::string &Wildcard::getTerm() const
{
  return term;
}

const std::string &Wildcard::getWildcardTerm() const
{
  return wildcardTerm;
}

bool Wildcard::check(const std::string& query) const
{
  std::string Q = query + "$";

  while (Q[0] != '$')
  {
    std::string::size_type n;
    n = Q.find(wildcardTerm);

    if (n != std::string::npos)
      return true;

    char t = Q[0];
    Q.erase(0, 1);
    Q.push_back(t);
  }

  return false;
}

void Wildcard::modulate()
{
  wildcardTerm = term + '$';

  for (const auto &item : wildcardTerm)
  {
    if (item == '*')
      stars++;
  }

  if (stars > 1)
    throw std::logic_error("More than one * not allowed yet!");

  if (stars == 1)
  {
    while (wildcardTerm[0] != '*')
    {
      char t = wildcardTerm[0];
      wildcardTerm.erase(0, 1);
      wildcardTerm.push_back(t);
    }

    wildcardTerm.erase(0, 1);
  }
}
}

#endif //DOQ_WILDCARD_HPP
