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

TEST_CASE("TermMatrixSoundexTest", "[TermMatrixTest]")
{
  doq::Document D1("data/a_midsummer_nights_dream.txt"),
      D2("data/hamlet.txt"),
      D3("data/macbeth.txt"),
      D4("data/othello.txt"),
      D5("data/romeo_and_juliet.txt"),
      D6("data/the_tempest.txt");

  doq::TermMatrix<doq::VanillaTokenizer, 6> TM(doq::VanillaTokenizer(),
      D1, D2, D3, D4, D5, D6);


  auto U1 = TM["Denmark"] || TM["Africa"];
  auto U2 = TM[doq::Soundex("Denmarq")] || TM[doq::Soundex("Afriqa")];

  REQUIRE(U1[0] == false);
  REQUIRE(U1[1] == true);
  REQUIRE(U1[2] == false);
  REQUIRE(U1[3] == true);
  REQUIRE(U1[4] == false);
  REQUIRE(U1[5] == false);

  REQUIRE(U1[0] == U2[0]);
  REQUIRE(U1[1] == U2[1]);
  REQUIRE(U1[2] == U2[2]);
  REQUIRE(U1[3] == U2[3]);
  REQUIRE(U1[4] == U2[4]);
  REQUIRE(U1[5] == U2[5]);
}