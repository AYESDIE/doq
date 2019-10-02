//
// Created by ayesdie on 30/09/19.
//

#include "catch.hpp"
#include "../src/doq.hpp"


TEST_CASE("TermMatrixTest", "[TermMatrixTest]")
{
  doq::document D1("data/a_midsummer_nights_dream.txt"),
                D2("data/hamlet.txt"),
                D3("data/macbeth.txt"),
                D4("data/othello.txt"),
                D5("data/romeo_and_juliet.txt"),
                D6("data/the_tempest.txt");

  doq::term_matrix<6> TM;
  TM.addDocument(D1, D2, D3, D4, D5, D6);


  TM.stat(TM["Denmark"] | TM["Africa"]);
  TM.showMatrix();
}