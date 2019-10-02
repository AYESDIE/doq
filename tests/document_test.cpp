//
// Created by ayesdie on 30/09/19.
//

#include "catch.hpp"
#include "../src/doq.hpp"
#include <iostream>

TEST_CASE("DocumentNameTest", "[DocumentTest]")
{
  std::string file_location = "data/document_test.txt";
  doq::document D1(file_location);
  REQUIRE(D1.getFileName() == std::string("document_test.txt"));
}

TEST_CASE("DocumentContentTest", "[DocumentTest]")
{
  std::string file_location = "data/document_test.txt";
  doq::document D1(file_location);

  std::string doc;
  std::ifstream fin(file_location);

  if(fin)
  {
    doc = std::string((std::istreambuf_iterator<char>(fin)),
                      std::istreambuf_iterator<char>());

    fin.close();
  }

  for (size_t i = 0; D1[i] != '\0'; i++)
  {
    REQUIRE(D1[i] == doc[i]);
  }

  REQUIRE(D1[D1.size() - 1] == doc[doc.size() - 1]);
}