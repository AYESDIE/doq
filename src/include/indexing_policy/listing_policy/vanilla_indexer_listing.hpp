//
// Created by ayesdie on 12/10/19.
//

#include "doq.hpp"
#include <vector>
#include <cstddef>
#include <string>

#ifndef DOQ_VANILLA_INDEXER_LISTING_HPP
#define DOQ_VANILLA_INDEXER_LISTING_HPP

namespace doq
{
class VanillaIndexerListing
{
public:
  inline VanillaIndexerListing();
  inline VanillaIndexerListing(const size_t& docId);

  inline size_t getDocId() const;
  inline void setDocId(size_t docId);
  inline const std::vector<size_t>& getPositions() const;
  inline void setPositions(const std::vector<size_t> &positions);

  inline void addPosition(const size_t& pos);

  template <typename... T>
  inline void addPosition(const size_t& pos, const T... Ts);

  inline auto operator[](const size_t& index);

private:
  size_t docId;

  std::vector<size_t> positions;
};

VanillaIndexerListing::VanillaIndexerListing()
{ /* does nothing */ }

VanillaIndexerListing::VanillaIndexerListing(const size_t &docId) :
  docId(docId)
{ /* does nothing */ }

size_t VanillaIndexerListing::getDocId() const
{
  return docId;
}

void VanillaIndexerListing::setDocId(size_t docId)
{
  VanillaIndexerListing::docId = docId;
}

const std::vector<size_t> &VanillaIndexerListing::getPositions() const
{
  return positions;
}

void VanillaIndexerListing::setPositions(const std::vector<size_t> &positions)
{
  VanillaIndexerListing::positions = positions;
}

void VanillaIndexerListing::addPosition(const size_t& pos)
{
  positions.push_back(pos);
}

template<typename... T>
void VanillaIndexerListing::addPosition(const size_t& pos, const T... Ts)
{
  positions.push_back(pos);
  addPosition(Ts...);
}

auto VanillaIndexerListing::operator[](const size_t &index)
{
  return positions[index];
}
}

#endif //DOQ_VANILLA_INDEXER_LISTING_HPP
