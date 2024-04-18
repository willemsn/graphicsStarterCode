#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "glm/glm.hpp"

TEST_CASE( "Test LinAlg GLM" )
{
  glm::vec3 v1(1.0, 0.0, 0.0);
  glm::vec3 v2(0.0, 0.0, 1.0);

  float dotProd = glm::dot(v1, v2);

  REQUIRE_THAT(dotProd, Catch::Matchers::WithinRel(0.0, 0.001));
}

