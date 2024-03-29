//
// Created by ayesdie on 03/10/19.
//

#include "catch.hpp"
#include <doq.hpp>

TEST_CASE("VanillaTokenizationBasicTest", "[VanillaTokenizationTest]")
{
  doq::Document D1("data/macbeth.txt"),
      D2("data/othello.txt");

  doq::VanillaTokenizer VT;
  VT.setDocument(D1);

  REQUIRE(VT.nextToken() == "When");
  REQUIRE(VT.nextToken() == "Duncan");

  VT.setDocument(D2);
  REQUIRE(VT.nextToken() == "Brabantio");
  REQUIRE(VT.nextToken() == "the");
}