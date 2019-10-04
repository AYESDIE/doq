//
// Created by ayesdie on 03/10/19.
//

#include <doq.hpp>
#include "catch.hpp"

TEST_CASE("PostingListBasicTest", "[PostingListTest]")
{
  doq::Document D1("data/document_test.txt");

  doq::PostingList<doq::VanillaTokenizer, doq::VanillaPosting>
    PL(doq::VanillaTokenizer(), D1);
}

TEST_CASE("PostingListAdvancedTest", "[PostingListTest]")
{
  doq::Document D1("data/a_midsummer_nights_dream.txt"),
    D2("data/hamlet.txt"),
    D3("data/macbeth.txt"),
    D4("data/othello.txt"),
    D5("data/romeo_and_juliet.txt"),
    D6("data/the_tempest.txt");

  doq::PostingList<doq::VanillaTokenizer, doq::VanillaPosting>
    PL(doq::VanillaTokenizer(), D1, D2, D3, D4, D5, D6);

  auto U = PL["Denmark"] || PL["Africa"];
  REQUIRE(U.size() == 2);
  REQUIRE(U[0] == 1);
  REQUIRE(U[1] == 3);
}