//
// Created by ayesdie on 18/10/19.
//

#include "catch.hpp"
#include <doq.hpp>

TEST_CASE("WildcardExceptionTest", "[WildcardTest]")
{
  doq::Wildcard W = doq::Wildcard("");

  REQUIRE_NOTHROW(W = doq::Wildcard("test"));
  REQUIRE_NOTHROW(W = doq::Wildcard("t*st"));
  REQUIRE_THROWS(W = doq::Wildcard("t*s*"));
}

TEST_CASE("WildcardBasicTest", "[WildcardTest]")
{
  doq::Wildcard W = doq::Wildcard("test");
  REQUIRE(W.getTerm() == std::string("test"));
  REQUIRE(W.getWildcardTerm() == std::string("test$"));

  W = doq::Wildcard("*est");
  REQUIRE(W.getTerm() == std::string("*est"));
  REQUIRE(W.getWildcardTerm() == std::string("est$"));

  W = doq::Wildcard("t*st");
  REQUIRE(W.getTerm() == std::string("t*st"));
  REQUIRE(W.getWildcardTerm() == std::string("st$t"));

  W = doq::Wildcard("tes*");
  REQUIRE(W.getTerm() == std::string("tes*"));
  REQUIRE(W.getWildcardTerm() == std::string("$tes"));
}

TEST_CASE("WildcardTest", "[WildcardTest]")
{
  doq::Wildcard W("Cal*");
  REQUIRE(W.check(std::string("Calpurnia")));

  W = doq::Wildcard("nia");
  REQUIRE(W.check(std::string("Calpurnia")));

  W = doq::Wildcard("Cal*ia");
  REQUIRE(W.check(std::string("Calpurnia")));
}