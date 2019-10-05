//
// Created by ayesdie on 05/10/19.
//

#include "catch.hpp"
#include <doq.hpp>

TEST_CASE("SoundexTestBasis", "[SoundexTest]")
{
  std::string h = "Hermann";
  doq::Soundex::apply(h);
  REQUIRE(h == "H655");

  h = "H";
  doq::Soundex::apply(h);
  REQUIRE(h == "H000");

  std::string A = "Africa";
  std::string B = "Afrika";
  std::string C = "Afreqa";

  doq::Soundex::apply(A);
  doq::Soundex::apply(B);
  doq::Soundex::apply(C);

  REQUIRE(A == B);
  REQUIRE(B == C);
}