//
// Created by ayesdie on 30/09/19.
//

#include "catch.hpp"
#include "../src/include/document.hpp"
#include <iostream>

TEST_CASE("DocumentTest", "[DocumentTest]")
{
  doq::document D1("data/document_test.txt");
  REQUIRE(D1[0] == 't');
  REQUIRE(D1[1] == 'e');
  REQUIRE(D1[2] == 's');
  REQUIRE(D1[3] == 't');
  REQUIRE(D1[4] == ' ');
  REQUIRE(D1[5] == 'A');
  REQUIRE(D1[6] == ' ');
  REQUIRE(D1[7] == 'B');
  REQUIRE(D1[8] == ' ');
  REQUIRE(D1[9] == 'C');
  REQUIRE(D1[10] == ' ');
  REQUIRE(D1[11] == 'Q');
  REQUIRE(D1[12] == '.');
  REQUIRE(D1[13] == 'a');
  REQUIRE(D1[14] == 's');
  REQUIRE(D1[15] == 'd');
  REQUIRE(D1[16] == ' ');
  REQUIRE(D1[17] == '@');
  REQUIRE(D1[18] == '3');
  REQUIRE(D1[19] == '\0');


}