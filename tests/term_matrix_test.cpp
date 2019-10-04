//
// Created by ayesdie on 30/09/19.
//

#include "catch.hpp"
#include <doq.hpp>


TEST_CASE("TermMatrixTest", "[TermMatrixTest]")
{
  doq::Document D1("data/a_midsummer_nights_dream.txt"),
                D2("data/hamlet.txt"),
                D3("data/macbeth.txt"),
                D4("data/othello.txt"),
                D5("data/romeo_and_juliet.txt"),
                D6("data/the_tempest.txt");

  doq::TermMatrix<doq::VanillaTokenizer, 6> TM(doq::VanillaTokenizer(),
                                                 D1, D2, D3, D4, D5, D6);


  auto U = TM["Denmark"] || TM["Africa"];

  REQUIRE(U[0] == false);
  REQUIRE(U[1] == true);
  REQUIRE(U[2] == false);
  REQUIRE(U[3] == true);
  REQUIRE(U[4] == false);
  REQUIRE(U[5] == false);

  U = TM["Pewdiepie"];

  REQUIRE(U[0] == false);
  REQUIRE(U[1] == false);
  REQUIRE(U[2] == false);
  REQUIRE(U[3] == false);
  REQUIRE(U[4] == false);
  REQUIRE(U[5] == false);
}