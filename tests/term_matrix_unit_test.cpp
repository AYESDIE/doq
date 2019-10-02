//
// Created by ayesdie on 02/10/19.
//

#include "catch.hpp"
#include "../src/include/term_matrix_unit.hpp"

TEST_CASE("TermMatrixUnitTermTest", "[TermMatrixUnitTest]")
{
  doq::term_matrix_unit<5> TMU1("Apple"), TMU2("Bowl");
  REQUIRE(TMU1.getTerm() == "apple");
  REQUIRE(TMU2.getTerm() == "bowl");
}

TEST_CASE("TermMatrixUnitUnitTest", "[TermMatrixUnitTest]")
{
  doq::term_matrix_unit<5> TMU1("Apple"), TMU2("Bowl");

  TMU1[1] = true;
  TMU1[3] = true;
  TMU2[1] = true;
  TMU2[3] = true;

  auto U = TMU1.getUnit() & TMU2.getUnit();
  REQUIRE(U[0] == false);
  REQUIRE(U[1] == true);
  REQUIRE(U[2] == false);
  REQUIRE(U[3] == true);
  REQUIRE(U[4] == false);

  U = TMU1.getUnit() ^ (~TMU1.getUnit());
  REQUIRE(U[0] == true);
  REQUIRE(U[1] == true);
  REQUIRE(U[2] == true);
  REQUIRE(U[3] == true);
  REQUIRE(U[4] == true);
}