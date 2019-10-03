//
// Created by ayesdie on 03/10/19.
//

#include "catch.hpp"
#include <doq.hpp>

TEST_CASE("VanillaPostingBasicTest", "[VanillaPostingTest]")
{
  doq::vanilla_posting VP1("Apple"), VP2("bowl");

  REQUIRE(VP1.getTerm() == std::string("Apple"));
  REQUIRE(VP2.getTerm() == std::string("bowl"));

  REQUIRE(VP1.getDocumentId().empty());
  REQUIRE(VP2.getDocumentId().empty());

  REQUIRE(VP1.getFrequency() == 0);
  REQUIRE(VP2.getFrequency() == 0);
}

TEST_CASE("VanillaPostingAddDocumentTest", "[VanillaPostingTest]")
{
  doq::vanilla_posting VP1("Apple"), VP2("bowl");

  VP1.addDocumentId(1);
  REQUIRE(!VP1.getDocumentId().empty());

  VP1.addDocumentId(4, 5, 9, 7);
  REQUIRE(VP1.getFrequency() == 4);
  REQUIRE(*(VP1.getDocumentId().end() - 1) == 9);

  VP2.addDocumentId(2, 4, 5);
  REQUIRE(VP2.getDocumentId().size() == 3);
  REQUIRE(VP2.getDocumentId()[2] == 5);
}

TEST_CASE("VanillaPostingAndOperationsTest", "[VanillaPostingTest]")
{
  doq::vanilla_posting VP1("Apple"), VP2("bowl");

  VP1.addDocumentId(1, 2, 3);
  VP2.addDocumentId(1, 2, 3, 4);

  auto U1 = VP1 && VP2;

  REQUIRE(U1.size() == 3);
  REQUIRE(U1[0] == 1);
  REQUIRE(U1[2] == 3);
}

TEST_CASE("VanillaPostingOrOperationsTest", "[VanillaPostingTest]")
{
  doq::vanilla_posting VP1("Apple"), VP2("bowl");

  VP1.addDocumentId(1, 2);
  VP2.addDocumentId(3);

  auto U2 = VP1 || VP2;

  REQUIRE(U2.size() == 3);
  REQUIRE(U2[0] == 1);
  REQUIRE(U2[1] == 2);
  REQUIRE(U2[2] == 3);
}