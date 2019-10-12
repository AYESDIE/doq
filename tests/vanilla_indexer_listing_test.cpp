//
// Created by ayesdie on 12/10/19.
//

#include "catch.hpp"
#include <doq.hpp>

TEST_CASE("VanillaIndexerListing", "[VanillaIndexerListing]")
{
  doq::VanillaIndexerListing VIL(0);

  VIL.addPosition(2, 4, 5, 10, 4);

  REQUIRE(VIL.getDocId() == 0);
  REQUIRE(VIL.getPositions().size() == 5);

  VIL.addPosition(7);
  REQUIRE(VIL.getPositions().size() == 6);
  REQUIRE(VIL[2] == 5);
}